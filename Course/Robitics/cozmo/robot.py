import asyncio
import cozmo
import cv2
import getopt
import logging
import numpy as np
import sys
import threading
import time

from cozmo.util import degrees, distance_mm, speed_mmps
from matplotlib import pyplot as plt

""" A simple line follow logic, which guides Cozmo along a line.
	For best results, use a white paper and a line that is 5-10mm
	thick. Make sure that no other marks are on the paper, as it is
	currently assumed that only one contour is found in the zone
	used for line position analysis.
	Potential improvements:
	(1) Master sharp turns
	(2) Master crossings
	(3) In case of multiple contours, select best contour 
	    (heuristics could be: in the middle, nearest the last
		contour, ...)
	Further work: Would be interesting to replace this complex
	logic by just a neural network as done here:
	https://github.com/benjafire/CozmoSelfDriveToyUsingCNN
"""


# A class for rects
class rect:
    def __init__(self, x=0, y=0, w=0, h=0, name=''):
        self.x = x
        self.y = y
        self.w = w
        self.h = h
        self.name = name

    def move(self, delta_x, delta_y):
        self.x = self.x + delta_x
        self.y = self.y + delta_y

    def h_center(self):
        return int(round(self.x + self.w / 2))

    def v_center(self):
        return int(round(self.y + self.h / 2))

    def perimeter(self):
        return (self.w + self.h) * 2

    def str(self):
        return self.name + '(x=' + str(self.x) + ',y=' + str(self.y) + ',w=' + str(self.w) + ',h=' + str(self.h) + ')'


# Zones where path contour is search in
ZONE_BOTTOM = 'bottom zone'
b_zn = rect(30, 180, 260, 20, ZONE_BOTTOM)
ZONE_LEFT = 'left zone'
l_zn = rect(0, 80, 30, 100, ZONE_LEFT)
ZONE_RIGHT = 'right zone'
r_zn = rect(290, 80, 30, 100, ZONE_RIGHT)

# Constants for corrections
gap_s = 20
gap_m = 60
gap_l = 120
turn_s = 5
turn_m = 15
turn_l = 30
move_s = 5
move_m = 10
move_l = 15
proposed_s = 10
proposed_m = 15
proposed_l = 25
proposed_xl = 40
sharp_forward = 40
sharp_turn = 90
cam_center = 160
step_l = 20
speed = 20
min_perimeter = 40
min_center = 80

# Camera settings
cam_threshold = 240

# Modes
MODE_STEP = 1
MODE_DRIVE = 2

# Show/hide images
show_img = True
show_inv_img = False
show_cnt_img = False

# Globvars for keeping track of sharp turns
l_rect = None
r_rect = None

# Logger
log = logging.getLogger('ok.linefollow')


def apply_heuristics_on_cnt_rects(cnt_rects, th, zn):
    log.info('Apply heuristics on cnt rects on ' + zn.name + '...')
    large_rects = []
    has_removed_small_rects = False
    # Remove small contours
    for cnt_rect in cnt_rects:
        if cnt_rect.perimeter() < min_perimeter:
            log.warning('Ignoring rect with small perimeter: ' + cnt_rect.str())
            has_removed_small_rects = True
        else:
            large_rects.append(cnt_rect)
    log.info('Got ' + str(len(cnt_rects)) + ' cnt rects and kept ' + str(len(large_rects)) + ' large ones')
    # Remove high contours (caused by low light at the edges)
    if zn.name == ZONE_LEFT or zn.name == ZONE_RIGHT:
        tmp_large_rects = large_rects
        large_rects = []
        for tmp_large_rect in tmp_large_rects:
            if tmp_large_rect.h < zn.h / 2 and tmp_large_rect.w > zn.w / 2:
                large_rects.append(tmp_large_rect)
        log.info('Got ' + str(len(tmp_large_rects)) + ' large rects and kept ' + str(
            len(large_rects)) + ' not too high ones')
    if len(large_rects) == 1:
        log.info('Heuristic 1: Single rect => take the one we have')
        return large_rects[0]
    if len(large_rects) > 1 and th < cam_threshold:
        log.info('Heuristic 2: Multiple rects / low threshold => take most center')
        center_rect = large_rects[0]
        for large_rect in large_rects:
            if abs(large_rect.h_center() - cam_center) < abs(center_rect.h_center() - cam_center):
                center_rect = large_rect
        return center_rect
    if len(large_rects) == 1 and th >= cam_threshold and has_removed_small_rects:
        log.info('Heuristic 3: Single rect / high threshold => probably white')
        return None
    if len(large_rects) > 1 and th >= cam_threshold:
        log.info('Heuristic 4: Multiple rects / high threshold => probably white')
        return None
    if len(large_rects) == 0:
        log.info('Heuristic 5: No rect at all')
        return None

    log.info('Unknown condition')
    return None


def get_cnt_rects(img, zn):
    """ Finds the bounding rects of the contours of the image. For this
        image is denoised and converted in black and white and inverted.
        Also returns the threshold which was used to identify the path.
    """
    log.info('Get cnt rects...')
    # Prepare image
    raw_img = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
    crp_img = raw_img[zn.y:zn.y + zn.h, zn.x:zn.x + zn.w]
    blr_img = cv2.GaussianBlur(crp_img, (10, 10), 0)
    th, thr_img = cv2.threshold(blr_img, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
    log.info('Threshold value in ' + zn.name + ': ' + str(th))
    inv_img = cv2.bitwise_not(thr_img)
    # Find contour of path
    cnt_img, cnts, h = cv2.findContours(inv_img, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    # Find bound rect of path
    cnt_rects = []
    for cnt in cnts:
        cnt_rect = rect()
        cnt_rect.x, cnt_rect.y, cnt_rect.w, cnt_rect.h = cv2.boundingRect(cnt)
        cnt_rect.move(zn.x, zn.y)
        cnt_rects.append(cnt_rect)
    return th, cnt_rects


def get_path_rect(img, zn):
    """ Finds the bounding rect of the contour of the path. For this
        image is denoised and converted in black and white and inverted.
    """
    log.info('Get path rect...')
    th, cnt_rects = get_cnt_rects(img, zn)
    return apply_heuristics_on_cnt_rects(cnt_rects, th, zn)


def draw_path_rect(img, pth_rect, c):
    """ Draw the path rectangle including a vertical line indicating
        the center of the path
    """
    log.info('Draw path rect...')
    if pth_rect == None:
        log.warning('No rect to draw')
        return img
    ret_img = cv2.rectangle(img, (pth_rect.x, pth_rect.y), (pth_rect.x + pth_rect.w, pth_rect.y + pth_rect.h), c, 1)
    ret_img = cv2.line(ret_img, (pth_rect.h_center(), pth_rect.y), (pth_rect.h_center(), pth_rect.y + pth_rect.h), c, 1)
    log.info('Absolute gap:' + str(cam_center - pth_rect.h_center()))
    return ret_img


def draw_cnt_rects(img, cnt_rects, c):
    """ Draw the contour rectangles
    """
    log.info('Draw cnt rects...')
    ret_img = img.copy()
    for cnt_rect in cnt_rects:
        ret_img = cv2.rectangle(ret_img, (cnt_rect.x, cnt_rect.y), (cnt_rect.x + cnt_rect.w, cnt_rect.y + cnt_rect.h),
                                c, 1)
    return ret_img


def draw_grid(img):
    """ Draws a grid on the image showing zones and center
    """
    log.info('Draw grid...')
    # Bottom zone
    ret_img = cv2.rectangle(img, (b_zn.x - 2, b_zn.y - 2), (b_zn.x - 2 + b_zn.w + 4, b_zn.y + b_zn.h + 4),
                            (255, 255, 0), 1)
    height, width = img.shape[:2]
    center = int(round(width / 2))
    ret_img = cv2.line(img, (center, 0), (center, height), (255, 255, 0), 1)
    # Left zone
    ret_img = cv2.rectangle(ret_img, (l_zn.x, l_zn.y - 2), (l_zn.x + l_zn.w + 2, l_zn.y + l_zn.h + 4), (255, 255, 0), 1)
    # right zone
    ret_img = cv2.rectangle(ret_img, (r_zn.x - 2, r_zn.y - 2), (r_zn.x + r_zn.w + 2, r_zn.y + r_zn.h + 4),
                            (255, 255, 0), 1)
    return ret_img


def drive(robot: cozmo.robot.Robot):
    """ Start driving
    """
    log.info('Drive...')
    robot.drive_wheel_motors(speed, speed)


def drive_left(robot: cozmo.robot.Robot):
    """ Drive to left
    """
    log.info('Drive left...')
    robot.drive_wheel_motors(speed - 15, speed)


def drive_right(robot: cozmo.robot.Robot):
    """ Drive to right
    """
    log.info('Drive right...')
    robot.drive_wheel_motors(speed, speed - 20)


def move_right(robot: cozmo.robot.Robot, move):
    """ Moves the robot to the right, in case the path is too far on the right
    """
    log.info('Move right...')
    robot.turn_in_place(degrees(-45)).wait_for_completed()
    robot.drive_straight(distance_mm(move), speed_mmps(speed)).wait_for_completed()
    robot.turn_in_place(degrees(45)).wait_for_completed()


def move_left(robot: cozmo.robot.Robot, move):
    """ Moves the robot to the left, in case the path is too far on the right
    """
    log.info('Move left...')
    robot.turn_in_place(degrees(45)).wait_for_completed()
    robot.drive_straight(distance_mm(move), speed_mmps(speed)).wait_for_completed()
    robot.turn_in_place(degrees(-45)).wait_for_completed()


def correct_turn(robot: cozmo.robot.Robot, turn, mode):
    """ Performs the turn for the correction. In case of
        'drive' mode, wheels are stopped and started again,
        in case of 'step' mode, only turn is performed
    """
    log.info('Turn for correction...')
    if mode == MODE_DRIVE:
        robot.stop_all_motors()
    robot.turn_in_place(degrees(turn)).wait_for_completed()
    if mode == MODE_DRIVE:
        robot.drive_wheel_motors(speed, speed)


def correct_position(robot: cozmo.robot.Robot, cur_center, mode):
    """ Corrects the position of the robot. Currently, the following corrections
        are implemented (see top of file for constant definitions):
        1) Current path center is >gap_s / >gap_m / >gap_l pixels to the right,
           this requires a turn_s / turn_m / turn_l to the left (positive degree)
        2) Current path center is >gap_s / >gap_m / >gap_l pixels to the left,
           this requires a turn_s / turn_m / turn_l to the right (positive degree)
    """
    log.info('Correcting position...')
    gap_abs = cam_center - cur_center
    log.info('Current center  : ' + str(cur_center))
    log.info('Absolute gap    : ' + str(gap_abs))
    if gap_abs < -gap_l:
        log.info('Current center is gap_l to right, needs right turn_l')
        correct_turn(robot, -turn_l, mode)
        return proposed_s
    elif gap_abs < -gap_m:
        log.info('Current center is gap_m to right, needs right turn_m')
        correct_turn(robot, -turn_m, mode)
        return proposed_m
    elif gap_abs < -gap_s:
        log.info('Current center is gap_s to right, needs right turn_s')
        correct_turn(robot, -turn_s, mode)
        return proposed_l
    elif gap_abs > gap_l:
        log.info('Current center is gap_l to left, needs left turn_l')
        correct_turn(robot, turn_l, mode)
        return proposed_s
    elif gap_abs > gap_m:
        log.info('Current center is gap_m to left, needs left turn_m')
        correct_turn(robot, turn_m, mode)
        return proposed_m
    elif gap_abs > gap_s:
        log.info('Current center is gap_s to left, needs left turn_s')
        correct_turn(robot, turn_s, mode)
        return proposed_l
    else:
        return proposed_xl


def step_forward(robot: cozmo.robot.Robot):
    """ Implements the main forward step. The robot takes a step forward and then
        compares the bounding rects of the contour of the path and adjusts direction
        accordingly. First implementation works with small / medium / large adjustments
        only.
    """
    global l_rect, r_rect
    log.info('Stepping forward...')
    robot.set_head_angle(cozmo.robot.MIN_HEAD_ANGLE).wait_for_completed()
    pth_img = np.array(robot.world.latest_image.raw_image)
    b_rect = get_path_rect(pth_img, b_zn)
    pth_img = draw_path_rect(pth_img, b_rect, (0, 255, 0))
    tmp_l_rect = get_path_rect(pth_img, l_zn)
    pth_img = draw_path_rect(pth_img, tmp_l_rect, (0, 255, 0))
    tmp_r_rect = get_path_rect(pth_img, r_zn)
    pth_img = draw_path_rect(pth_img, tmp_r_rect, (0, 255, 0))
    pth_img = draw_grid(pth_img)
    if b_rect != None:
        proposed_step = correct_position(robot, b_rect.h_center(), MODE_STEP)
        log.info('Moving forward ' + str(proposed_step) + 'mm')
        robot.drive_straight(distance_mm(proposed_step), speed_mmps(speed), False).wait_for_completed()
        l_rect = tmp_l_rect
        r_rect = tmp_r_rect
    elif l_rect != None:
        log.info('Preparing sharp turn to left')
        robot.drive_straight(distance_mm(sharp_forward), speed_mmps(speed), False).wait_for_completed()
        robot.turn_in_place(degrees(sharp_turn)).wait_for_completed()
        l_rect = None
        r_rect = None
    elif r_rect != None:
        log.info('Preparing sharp turn to right')
        robot.drive_straight(distance_mm(sharp_forward), speed_mmps(speed), False).wait_for_completed()
        robot.turn_in_place(degrees(-sharp_turn)).wait_for_completed()
        l_rect = None
        r_rect = None
    else:
        log.warning('Path was lost')
        return False
    if show_img:
        cv2.imshow('step_forward', pth_img)
        capture(robot)
    return True


def drive_forward(robot: cozmo.robot.Robot):
    """ Implements the main forward step. The robot takes a step forward and then
        compares the bounding rects of the contour of the path and adjusts direction
        accordingly. First implementation works with small / medium / large adjustments
        only.
    """
    log.info('Stepping forward...')
    robot.set_head_angle(cozmo.robot.MIN_HEAD_ANGLE).wait_for_completed()
    pth_img = np.array(robot.world.latest_image.raw_image)
    b_rect = get_path_rect(pth_img, b_zn)
    pth_img = draw_grid(pth_img)
    if b_rect != None:
        pth_img = draw_path_rect(pth_img, b_rect, (0, 255, 0))
        proposed_step = correct_position(robot, b_rect.h_center(), MODE_DRIVE)
        log.info('Driving on for ' + str(proposed_step / speed) + ' seconds')
        time.sleep(proposed_step / speed)
    else:
        log.warning('Path was lost')
        return False
    if show_img:
        cv2.imshow('step_forward', pth_img)
    return True


def capture(robot: cozmo.robot.Robot):
    """ Capture an image of the path and show bounding rect of the
        contour of the path.
    """
    log.info('Capture image...')
    robot.set_head_angle(cozmo.robot.MIN_HEAD_ANGLE).wait_for_completed()
    img = np.array(robot.world.latest_image.raw_image)
    rect_img = draw_grid(img)
    th, b_cnt_rects = get_cnt_rects(rect_img, b_zn)
    rect_img = draw_cnt_rects(rect_img, b_cnt_rects, (0, 255, 255))
    rect_img = draw_path_rect(rect_img, get_path_rect(rect_img, b_zn), (0, 255, 0))
    th, l_cnt_rects = get_cnt_rects(rect_img, l_zn)
    rect_img = draw_cnt_rects(rect_img, l_cnt_rects, (0, 255, 255))
    rect_img = draw_path_rect(rect_img, get_path_rect(rect_img, l_zn), (0, 255, 0))
    th, r_cnt_rects = get_cnt_rects(rect_img, r_zn)
    rect_img = draw_cnt_rects(rect_img, r_cnt_rects, (0, 255, 255))
    rect_img = draw_path_rect(rect_img, get_path_rect(rect_img, r_zn), (0, 255, 0))
    cv2.imshow('rect_img', rect_img)


def battery_level(robot: cozmo.robot.Robot):
    """ Logs the battery level
    """
    log.info('Battery level...')
    level = robot.battery_voltage
    log.info('Level is ' + str(level) + 'V')
    if level <= 3.5:
        log.warning('Level is low. Please place Cozmo on charger.')


def camera_info(robot: cozmo.robot.Robot):
    """ Logs the camera info
    """
    log.info('Camera info...')
    log.info('Auto     : ' + str(robot.camera.is_auto_exposure_enabled))
    log.info('Gain     : ' + str(round(robot.camera.gain, 2)))
    log.info('         : (' + str(round(robot.camera.config.min_gain, 2)) + '...' + str(
        round(robot.camera.config.max_gain, 2)) + ')')
    log.info('Exposure : ' + str(robot.camera.exposure_ms))
    log.info('         : (' + str(robot.camera.config.min_exposure_time_ms) + '...' + str(
        robot.camera.config.max_exposure_time_ms) + ')')


def camera_manual(robot: cozmo.robot.Robot):
    """ Set camera to manual exposure to brighten up the image
    """
    log.info('Camera manual...')
    robot.camera.set_manual_exposure(40, 3.9)


def camera_auto(robot: cozmo.robot.Robot):
    """ Set camera to auto exposure
    """
    log.info('Camera auto...')
    robot.camera.enable_auto_exposure()


def cozmo_cli(robot: cozmo.robot.Robot):
    """ Main loop implementing simplistic CLI
    """
    log.info('Entering Cozmo program')
    robot.stop_all_motors()
    robot.set_head_light(True)
    robot.camera.image_stream_enabled = True
    robot.set_lift_height(1.0).wait_for_completed()
    while True:
        run_cmd = input('C>')
        if run_cmd == 's':
            step_forward(robot)
        if run_cmd == 'd':
            drive(robot)
        if run_cmd == 'r':
            drive_right(robot)
        if run_cmd == 'l':
            drive_left(robot)
        if run_cmd == 'c':
            capture(robot)
        if run_cmd == 'b':
            battery_level(robot)
        if run_cmd == 'i':
            camera_info(robot)
        if run_cmd == 'm':
            camera_manual(robot)
        if run_cmd == 'a':
            camera_auto(robot)
        if run_cmd == 'n':
            time.sleep(1)
        if run_cmd == 'e':
            robot.stop_all_motors()
            cv2.destroyAllWindows()
            print('Bye.')
            break


def cozmo_step_forward(robot: cozmo.robot.Robot):
    """ Follows line forever (step-by-step)
    """
    global show_img
    log.info('Entering Cozmo step_forward...')
    show_img = False
    robot.set_head_light(True)
    robot.camera.image_stream_enabled = True
    robot.set_lift_height(1.0).wait_for_completed()
    while True:
        if step_forward(robot):
            continue
        else:
            break


def cozmo_drive_forward(robot: cozmo.robot.Robot):
    """ Follows line forever (continuously)
    """
    global show_img
    log.info('Entering Cozmo drive_forward...')
    show_img = False
    robot.set_head_light(True)
    robot.camera.image_stream_enabled = True
    robot.set_lift_height(1.0).wait_for_completed()
    robot.drive_wheel_motors(speed, speed)
    while True:
        if drive_forward(robot):
            continue
        else:
            break


def cozmo_battery_level(robot: cozmo.robot.Robot):
    """ Output battery level
    """
    log.info('Entering Cozmo battery_level...')
    battery_level(robot)


def main(argv):
    # Set-up logging
    formatter = logging.Formatter('%(asctime)s %(name)s %(levelname)-8s %(message)s')
    handler = logging.StreamHandler()
    handler.setLevel(logging.INFO)
    handler.setFormatter(formatter)
    log.setLevel(logging.INFO)
    log.addHandler(handler)
    # Eval command line
    usecase = 'cli'
    try:
        opts, args = getopt.getopt(argv, 'hu:', ['usecase='])
    except getopt.GetoptError:
        print('line_follow.py -u <usecase>')
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print('line_follow.py -u <usecase>')
            sys.exit()
        elif opt in ("-u", "--usecase"):
            usecase = arg
    log.info('Executing use case ' + usecase)
    if usecase == 'cli':
        cozmo.run_program(cozmo_cli)

if __name__ == '__main__':
        main(sys.argv[1:])