import cozmo
from cozmo.util import degrees, distance_mm, speed_mmps


def cozmo_program(robot: cozmo.robot.Robot):
    # Attempt to stack 2 cubes

    # Lookaround until Cozmo knows where at least 2 cubes are:
    lookaround = robot.start_behavior(cozmo.behavior.BehaviorTypes.LookAroundInPlace)
    cubes = robot.world.wait_until_observe_num_objects(num=1, object_type=cozmo.objects.LightCube, timeout=60)
    lookaround.stop()

    if len(cubes) < 2:
        print("Error: need 2 Cubes but only found", len(cubes), "Cube(s)")
    else:
        # Try and pickup the 1st cube
        current_action = robot.pickup_object(cubes[0], num_retries=3)
        current_action.wait_for_completed()
        if current_action.has_failed:
            code, reason = current_action.failure_reason
            result = current_action.result
            print("Pickup Cube failed: code=%s reason='%s' result=%s" % (code, reason, result))
            return

        # Now try to place that cube on the 2nd one
        current_action = robot.place_on_object(cubes[1], num_retries=3)
        current_action.wait_for_completed()
        if current_action.has_failed:
            code, reason = current_action.failure_reason
            result = current_action.result
            print("Place On Cube failed: code=%s reason='%s' result=%s" % (code, reason, result))
            return

        print("Cozmo successfully stacked 2 blocks!")


SPEED_MMPS = 50


def send_one_cube(robot: cozmo.robot.Robot):
    pass
    # robot.world.delete_all_custom_objects()

def deliverer(robot: cozmo.robot.Robot):
    # robot.set_head_angle(cozmo.robot.MIN_HEAD_ANGLE).wait_for_completed()
    # robot.set_lift_height(cozmo.robot.MIN_LIFT_HEIGHT).wait_for_completed()
    # Look around
    robot.drive_straight(distance_mm(120), speed_mmps(350)).wait_for_completed()
    lookaround = robot.start_behavior(cozmo.behavior.BehaviorTypes.LookAroundInPlace)
    cubes = robot.world.wait_until_observe_num_objects(num=3, object_type=cozmo.objects.LightCube, timeout=60)
    lookaround.stop()
    cubes = [cubes[1], cubes[2], cubes[0]]
    for i in range(3):
        print("Looking for cube {}".format(i))
        lookaround.stop()
        cube:cozmo.objects.LightCube = cubes[i]
        cube.set_lights(cozmo.lights.blue_light)
        robot.pickup_object(cube, num_retries=5).wait_for_completed()
        # For the first two cubes
        if i < 2:
            robot.drive_straight(distance_mm(-350), speed_mmps(360)).wait_for_completed()
            robot.turn_in_place(degrees(90), speed=cozmo.util.Angle(360)).wait_for_completed()
            robot.place_object_on_ground_here(cube).wait_for_completed()
            robot.turn_in_place(degrees(-90), speed=cozmo.util.Angle(360)).wait_for_completed()
        else:
            robot.drive_straight(distance_mm(-380), speed_mmps(350)).wait_for_completed()
            robot.place_object_on_ground_here(cube).wait_for_completed()
        cube.set_lights_off()
        print("Cube {} finished".format(i))


def deliverer_stack(robot: cozmo.robot.Robot):
    # robot.set_head_angle(cozmo.robot.MIN_HEAD_ANGLE).wait_for_completed()
    # robot.set_lift_height(cozmo.robot.MIN_LIFT_HEIGHT).wait_for_completed()
    # Look around
    lookaround = robot.start_behavior(cozmo.behavior.BehaviorTypes.LookAroundInPlace)
    cubes = robot.world.wait_until_observe_num_objects(num=3, object_type=cozmo.objects.LightCube, timeout=60)
    lookaround.stop()

    robot.pickup_object(cubes[0], num_retries=5).wait_for_completed()
    robot.place_on_object(cubes[1], num_retries=3).wait_for_completed()
    robot.pickup_object(cubes[1], num_retries=5).wait_for_completed()
    robot.drive_straight(distance_mm(-335), speed_mmps(300)).wait_for_completed()
    robot.turn_in_place(degrees(90), speed=cozmo.util.Angle(360)).wait_for_completed()
    robot.place_object_on_ground_here(cubes[1]).wait_for_completed()
    robot.turn_in_place(degrees(-90), speed=cozmo.util.Angle(360)).wait_for_completed()
    robot.pickup_object(cubes[2], num_retries=5).wait_for_completed()
    robot.drive_straight(distance_mm(-340), speed_mmps(300)).wait_for_completed()
    robot.place_object_on_ground_here(cubes[2]).wait_for_completed()



cozmo.run_program(deliverer, use_viewer=True, use_3d_viewer=True)
