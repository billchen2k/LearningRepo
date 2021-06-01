#!/usr/bin/env python3

# Copyright (c) 2016 Anki, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License in the file LICENSE.txt or at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

'''Control Cozmo using a webpage on your computer.

This example lets you control Cozmo by Remote Control, using a webpage served by Flask.
'''

import json
import sys
import cv2

sys.path.append('../lib/')
import flask_helpers
import numpy as np
import cozmo
import tensorflow as tf
from cozmo_cnn_models  import cnn_cccccfffff
import time 
from cozmo.util import degrees, distance_mm, speed_mmps 



DEBUG_ANNOTATIONS_DISABLED = 0
DEBUG_ANNOTATIONS_ENABLED_VISION = 1
DEBUG_ANNOTATIONS_ENABLED_ALL = 2



class RemoteControlCozmo:

    def __init__(self, coz):
        self.cozmo = coz
        self.sess = tf.InteractiveSession()
        self.drive_forwards = 0
        self.drive_back = 0
        self.turn_left = 0
        self.turn_right = 0
        self.model = cnn_cccccfffff()
        saver = tf.train.Saver()
        #saver.restore(self.sess, "/Users/benja/code/Cherry-Autonomous-Racecar-master/Tensorflow/cozmo_run_model.ckpt")
        saver.restore(self.sess, "") # plz fill the module you got from training 

    def go_driving(self, key_code ):
        '''Called on any key press or release
           Holding a key down may result in repeated run_cnn calls with is_key_down==True
        '''

        #speed_changed = (was_go_fast != self.go_fast) or (was_go_slow != self.go_slow)

        # Update state of driving intent from keyboard, and if anything changed then call update_driving
        drive = np.argmax(key_code,1) 

        self.drive_forwards = 0
        self.drive_back = 0
        self.turn_left = 0
        self.turn_right = 0

        if drive[0] == 3 :
            self.drive_forwards = True
            print("command forwards")
        elif drive[0] == 2:
            self.drive_back= True 
            print("command back")
        elif drive[0] == 0:
            self.turn_left = True 
            print("command left")
        elif drive[0] == 1:
            self.turn_right = True 
            print("command right")
        else:
            print(" done know the value ",drive)
            self.drive_forwards = True

        #print("drive forwards back left right", drive[0], self.drive_forwards, self.drive_back, self.turn_left, self.turn_right)
        self.update_driving()



    def drive(self):
        ''' Get the image infront and 
        '''
        latest_image = self.cozmo.world.latest_image
        screen  = np.array(latest_image.raw_image)
        screen  = cv2.resize(screen, (200, 120), interpolation=cv2.INTER_CUBIC)                                                         
        cv2.imshow('window1', screen)
        cv2.imwrite("./a.jpg", screen)

        image =  screen.astype(dtype=np.float32)/255.0

        key_code = self.model.y_out.eval(session=self.sess, feed_dict={self.model.x: [image], 
                                              self.model.keep_prob_fc1:1.0, self.model.keep_prob_fc2:1.0, 
                                              self.model.keep_prob_fc3:1.0, self.model.keep_prob_fc4:1.0})

        print ("after judgeing, key_code is", key_code )

        self.go_driving(key_code)


    def update_driving(self):
        drive_dir = (self.drive_forwards - self.drive_back)


        turn_dir = (self.turn_right - self.turn_left)  

        if drive_dir < 0:
            # It feels more natural to turn the opposite way when reversing
            turn_dir = -turn_dir

        #forward_speed = self.pick_speed(150, 75, 50)
        forward_speed = 50
        turn_speed    = 30

        l_wheel_speed = (drive_dir * forward_speed) + (turn_speed * turn_dir)
        r_wheel_speed = (drive_dir * forward_speed) - (turn_speed * turn_dir)

        print("cozmo   drive_dir dirve_forward drive_back turn_speed turn_dir "  , drive_dir,self.drive_forwards,self.drive_back, turn_speed, turn_dir) 

        #if self.turn_left == True :
        #    self.cozmo.turn_in_place(degrees(90)).wait_for_completed()
        #elif self.turn_right == True : 
        #    self.cozmo.turn_in_place(degrees(-90)).wait_for_completed()
        #else:
        self.cozmo.drive_wheels(l_wheel_speed, r_wheel_speed, l_wheel_speed*4, r_wheel_speed*4)
        #input()


def run(sdk_conn):
    robot = sdk_conn.wait_for_robot()

    global remote_control_cozmo
    robot.camera.image_stream_enabled = True
    remote_control_cozmo = RemoteControlCozmo(robot)

    # Turn on image receiving by the camera

    angle = cozmo.util.Angle ( -0.10, None)

    robot.set_head_angle(angle).wait_for_completed()

    # 87 83 65 68
    print(ord('W'),ord('S'),ord('A'), ord('D'))

    while True:
        remote_control_cozmo.drive()
        time.sleep(0.1)

if __name__ == '__main__':
    cozmo.setup_basic_logging()
    cozmo.robot.Robot.drive_off_charger_on_connect = False  # RC can drive off charger if required
    try:
        cozmo.connect(run)
    except cozmo.ConnectionError as e:
        sys.exit("A connection error occurred: %s" % e)
