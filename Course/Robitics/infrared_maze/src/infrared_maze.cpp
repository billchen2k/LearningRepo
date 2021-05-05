/***************************************************************
 Copyright(C): 2016-2020 ROS小课堂 www.corvin.cn
 Description:三轮小车进行红外避障走迷宫.根据前,左,右三个红外测距
   信息来进行移动,这里的移动策略是每次移动0.5m,然后再判断距离.
   移动时向左转优先,其次直行,最后是右转.
 Author: jally, corvin
 History:
    20200404:增加可以直接转90度,掉头的功能 by corvin.
    20200412:增加使用服务方式来获取红外测距值-corvin.
    20200424:增加每次前进时移动距离的参数,可以配置.-corvin
 **************************************************************/
#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <tf/transform_listener.h>
#include <cmath>
#include "rasp_imu_hat_6dof/GetYawData.h"
#include "ros_arduino_msgs/InfraredSensors.h"
#include "ros_arduino_msgs/GetInfraredDistance.h"


#define  GO_FORWARD   0
#define  TURN_LEFT    1
#define  TURN_RIGHT   2
#define  TURN_BACK    3
#define  HORIZ_MOVE   4
#define  INIT_POSE   5
#define  TURN_LEFT_10   6
#define  TURN_RIGHT_10   7
#define  VERTICAL_MOVE   8
#define  TURN_BIAS   9

#define  ERROR       -1

//global variable
ros::Publisher twist_pub;
ros::ServiceClient yawSrvClient;
rasp_imu_hat_6dof::GetYawData yawSrv;

//红外测距相关的服务
ros::ServiceClient distSrvClient;
ros_arduino_msgs::GetInfraredDistance distSrv;

float warn_dist = 0.25;  //warn check distance
float tolerance_dist = 0.05; //对警告距离的容忍值
float forward_dist = 0.50; //每次前进移动时走的距离

bool init_switch = false;
float circle_dist = 0.18;//圆盘直径
float wall_dist = 0.16;//小车处于中线位置时里wall的距离
float init_tolerance_dist = 0.01;//平移时左右差的容忍值
float angular_bias = 0.0;//偏离中线的弧度值
float angular_bias_symbol = 1.0;


float front_dist;
float left_dist;
float right_dist;

std::string odomFrame;
std::string baseFrame;

float linear_x_speed = 0.17;
float linear_y_speed = 0.15;
float angular_speed = 0.2;

float init_linear_x_speed = 0.17;
float init_linear_y_speed = 0.15;
float init_angular_speed = 0.2;

float start_yaw_data = 0.0;
int turnFlag = ERROR;

/*********************************************************
 * Descripition: 发布控制移动的消息,这里对于平面移动的
 *   机器人只需要控制linear_x,linear_y和angular_z即可.
 ********************************************************/
void publishTwistCmd(float linear_x, float linear_y, float angular_z)
{
    geometry_msgs::Twist twist_msg;

    twist_msg.linear.x = linear_x;
    twist_msg.linear.y = linear_y;
    twist_msg.linear.z = 0.0;

    twist_msg.angular.x = 0.0;
    twist_msg.angular.y = 0.0;
    twist_msg.angular.z = angular_z;

    twist_pub.publish(twist_msg);
}

/**********************************************************
 * Description:调用IMU板发布出来的yaw信息,可以根据该数据
 *   来修正转弯时不准确的问题.注意这里的yaw数据为弧度值.
 *   注意往右旋转为负值,左旋转为正值.右手定则.
 *   注意在ROS中IMU数据中yaw的范围,具体表示如下:
 *                0  -0
 *                -----
 *              /      \
 *         1.57|        | -1.57
 *              \      /
 *               ------
 *             3.14 -3.14
 **********************************************************/
void yawUpdate(const float start_yaw)
{
    float target = 0.0;
    float diff = 10.0;
    float angular = 0.0;
    float now_yaw = 0.0;
    float angular_update_speed = 0.0;
    angular_update_speed = angular_speed;
    //开始计算修正后的目标角度
    if((turnFlag == GO_FORWARD)||(turnFlag == HORIZ_MOVE)||(turnFlag == VERTICAL_MOVE))
    {
        target = start_yaw;
        if(turnFlag == HORIZ_MOVE||turnFlag == VERTICAL_MOVE){
            angular_update_speed = init_angular_speed;
        }
    }
    else if(turnFlag == TURN_LEFT)
    {
        target = start_yaw + M_PI/2.0;
        if(target > M_PI)
        {
            target = target - M_PI*2.0;
        }
    }
    else if(turnFlag == TURN_RIGHT)
    {
        target = start_yaw - M_PI/2.0;
        if(target < -M_PI)
        {
            target = target + M_PI*2.0;
        }
    }
    else if(turnFlag == TURN_BIAS)
    {
        if(angular_bias > 0){
            target = start_yaw + angular_bias;
            if(target > M_PI)
            {
                target = target - angular_bias;
            }
        }else{
            target = start_yaw + angular_bias;
            if(target < -M_PI)
            {
                target = target - angular_bias;
            }
        }
        angular_update_speed = init_angular_speed;
    }
    else //turn back
    {
        target = start_yaw + M_PI;
        if(target > M_PI)
        {
            target = target - M_PI*2.0;
        }
    }

    //开始不断的计算偏差,调整角度
    while(fabs(diff) > 0.01)
    {
        yawSrvClient.call(yawSrv);
        now_yaw = yawSrv.response.yaw;
        ROS_INFO("Now Yaw data:%f, Target Yaw:%f", now_yaw, target);

        diff = target - now_yaw;
        if(diff > 0)
        {
            angular = angular_update_speed;
        }
        else
        {
            angular = -angular_update_speed;
        }
        ROS_WARN("Yaw diff:%f, angular:%f", diff, angular);
        publishTwistCmd(0, 0, angular);
        ros::Duration(0.04).sleep();
    }
    publishTwistCmd(0, 0, 0); //在修正角度结束后应该立刻停止小车转动
    ROS_INFO("Correct Yaw diff over !");
    ros::Duration(0.1).sleep(); //100 ms
}

/****************************************************
 * Description:控制小车前进移动0.5m
 ***************************************************/
void goForward(const float check_dist)
{
    tf::TransformListener tf_Listener;
    tf::StampedTransform tf_Transform;
    float dist = 0.0; //每次前进移动的距离
    float front_dist = 0.0;

    try
    {
        tf_Listener.waitForTransform(odomFrame, baseFrame, ros::Time(0), ros::Duration(5.0));
    }
    catch(tf::TransformException &ex)
    {
        ROS_ERROR("tf_Listener.waitForTransform timeout error !");
        ROS_ERROR("%s", ex.what());
        ros::shutdown();
    }

    tf_Listener.lookupTransform(odomFrame, baseFrame, ros::Time(0), tf_Transform);
    float x_start = tf_Transform.getOrigin().x();
    float y_start = tf_Transform.getOrigin().y();

    distSrvClient.call(distSrv); //通过服务调用来获取测距值
    front_dist = distSrv.response.front_dist; //记录当前测距值,防止撞墙
    ROS_INFO("Front dist:%f", front_dist);
    while((dist<check_dist)&&(front_dist>tolerance_dist*4.0)&&(ros::ok()))
    {
        ROS_INFO("Go forward, dist:%f", dist);
        publishTwistCmd(linear_x_speed, 0, 0);
        ros::Duration(0.10).sleep(); //100 ms

        tf_Listener.lookupTransform(odomFrame, baseFrame, ros::Time(0),tf_Transform);
        float x = tf_Transform.getOrigin().x();
        float y = tf_Transform.getOrigin().y();
        dist = sqrt(pow((x - x_start), 2) + pow((y - y_start), 2));

        distSrvClient.call(distSrv); //通过服务调用来获取测距值
        front_dist = distSrv.response.front_dist; //记录当前测距值,防止撞墙
        ROS_INFO("Front dist:%f", front_dist);
    }
    publishTwistCmd(0, 0, 0); //stop move
    ROS_INFO("Go forward finish !!!");
}

/*************************************************************
 * Description:控制小车左右转90度,或者掉头180度.这里实现小车
 *   转弯功能是通过不断监听odom和base_link之间的tf转换完成的.
 ************************************************************/
int controlTurn(int flag)
{
    tf::TransformListener tf_Listener;
    tf::StampedTransform tf_Transform;
    float angular = 0.0;
    float check_angle = 0.0;

    switch(flag)
    {
        case TURN_LEFT: //向左转动90°
            turnFlag = TURN_LEFT;
            angular = angular_speed;
            publishTwistCmd(linear_x_speed, 0, 0);         
            check_angle = M_PI/2.0;
            break;

        case TURN_RIGHT: //向右转动90°
            turnFlag = TURN_RIGHT;
            angular = -angular_speed;
            check_angle = M_PI/2.0;
            break;

        case TURN_BACK: //小车原地掉头180度
            turnFlag = TURN_BACK;
            check_angle = M_PI;
            angular = angular_speed;
            break;

        case TURN_LEFT_10:
            turnFlag = GO_FORWARD;
            angular = init_angular_speed;
            check_angle = M_PI/18.0;
            break;

        case TURN_RIGHT_10:
            turnFlag = GO_FORWARD;
            angular = -init_angular_speed;
            check_angle = M_PI/18.0;
            break;

        case TURN_BIAS:
            turnFlag = TURN_BIAS;
            check_angle = angular_bias;
            if(angular_bias>0){
                angular = init_angular_speed;
            }else
            {
                angular = -init_angular_speed;
                check_angle = -check_angle;   
            }
            break;

        case GO_FORWARD: //小车直行50cm
            goForward(forward_dist);
            return 1;

        default:
            ROS_ERROR("Turn flag error !");
            return -1;
    }

    try
    {
        tf_Listener.waitForTransform(odomFrame, baseFrame, ros::Time(0), ros::Duration(5.0));
    }
    catch(tf::TransformException &ex)
    {
        ROS_ERROR("tf_Listener.waitForTransform timeout error !");
        ROS_ERROR("%s", ex.what());
        ros::shutdown();

        return -2;
    }

    //ROS_INFO("Check_angle:%f, angular_speed:%f",check_angle, angular);
    tf_Listener.lookupTransform(odomFrame, baseFrame, ros::Time(0), tf_Transform);
    float last_angle = fabs(tf::getYaw(tf_Transform.getRotation()));
    float turn_angle = 0.0;
    ROS_INFO("first_angle:%f", last_angle);
    while((fabs(turn_angle) < check_angle)&&(ros::ok()))
    {
        publishTwistCmd(0, 0, angular); //原地转弯,不需要linear_x,y的控制
        ros::Duration(0.10).sleep(); //100 ms

        try
        {
            tf_Listener.lookupTransform(odomFrame, baseFrame, ros::Time(0), tf_Transform);
        }
        catch(tf::TransformException &ex)
        {
            ROS_ERROR("%s", ex.what());
            continue;
        }
        float rotation = fabs(tf::getYaw(tf_Transform.getRotation()));
        float delta_angle = fabs(rotation - last_angle);

        turn_angle += delta_angle;
        last_angle = rotation;
        ROS_INFO("Turn angle:%f", turn_angle);
    }
    publishTwistCmd(0, 0, 0); //原地转弯完成后,需要立刻停止小车的旋转
    ROS_INFO("Turning finish !!!");
    ros::Duration(0.1).sleep(); //100 ms

    return 0;
}

/**********************************************************
 * Description:控制小车移动在过道中间,比较左右两边的距离后
 *   然后进行水平左右移动.使小车保持在过道中间位置.
 **********************************************************/
void horizMoveMiddle(float tolerance)
{
    float diff = 0.0; //计算左右两边距离差
    float begin_yaw = 0.0;
    float now_left  = 0.0;
    float now_right = 0.0;

    turnFlag = HORIZ_MOVE;
    yawSrvClient.call(yawSrv); //记录平移前的角度,作为标准进行修正
    begin_yaw = yawSrv.response.yaw;

    ros::Duration(0.02).sleep();//在获取两次传感器值之间需要加延迟
    distSrvClient.call(distSrv);
    now_left = distSrv.response.left_dist; //获取左边距离
    ros::Duration(0.02).sleep();//在获取两次传感器值之间需要加延迟
    distSrvClient.call(distSrv);
    now_right = distSrv.response.right_dist;//获取右边距离

    diff = now_left - now_right;
    ROS_INFO("diff:%f,left:%f,right:%f", diff, now_left, now_right);
    while((fabs(diff)>tolerance))
    {
        if(diff < 0) //move right
        {
            ROS_WARN("move Right horizontally !");
            if(tolerance == tolerance_dist){
                publishTwistCmd(0, -linear_y_speed, 0);
            }else{
                publishTwistCmd(0, -init_linear_y_speed, 0);
            }
            
        }else if(diff > 0) //move left
        {
            ROS_WARN("move Left horizontally !");
            if(tolerance == tolerance_dist){
                publishTwistCmd(0, linear_y_speed, 0);
            }else{
                publishTwistCmd(0, init_linear_y_speed, 0);
            }
        }
        

        distSrvClient.call(distSrv);
        now_left = distSrv.response.left_dist;
        ros::Duration(0.02).sleep();//在获取两次传感器值之间需要加延迟
        distSrvClient.call(distSrv);
        now_right = distSrv.response.right_dist;

        diff = now_left - now_right; //计算左右距离差值
    }
    //当平移结束后立刻停止移动
    publishTwistCmd(0, 0, 0); //stop move
    ros::Duration(0.1).sleep(); //delay 100ms
    yawUpdate(begin_yaw); //用于修正转歪的角度
}

/***************************************************************************
 * Description:检查三个传感器数据,然后控制小车移动.这里需要防止小车在原地
 *   进行连续两次旋转,在每次转弯后必须有个直行.这里需要注意的是当小车在转弯
 *   后一定要有一个可以修正转弯角度的功能,否则转弯后角度不准确小车前进方向
 *   会错.这里的走迷宫策略是左转优先,中间是直行,最后是右转.
 *   当前方,左边,右边都无法移动时,进行掉头动作,然后直行.
 **************************************************************************/
void checkInfraredDist(float infrared_f,float infrared_l,float infrared_r,
        float tolerance, float warn_distance)
{
    static int flag = 0; //记录是否转过弯的标志

    yawSrvClient.call(yawSrv); //通过服务调用来获取yaw值
    start_yaw_data = yawSrv.response.yaw; //记录当前yaw值,用于后面修正

    //判断能否左转,并且上一次动作不能是转弯
    if((infrared_l == (float)0.3)&&(flag != 1))
    {
        ROS_WARN("turn Left! yaw_data:%f", start_yaw_data);
        turnFlag = TURN_LEFT;
        flag = 1; //设置转弯标志
    }
    else if(infrared_f > warn_distance)//判断能否直行
    {
        //始终控制小车保持在过道的中间位置
        ROS_WARN("go Forward ! yaw_data: %f", start_yaw_data);
        horizMoveMiddle(tolerance);
        turnFlag = GO_FORWARD;
        flag = 0; //设置直行标志
    }
    else if((infrared_r == (float)0.3)&&(flag != 1))//判断能否右转
    {
        ROS_WARN("turn Right ! yaw_data: %f", start_yaw_data);
        turnFlag = TURN_RIGHT;
        flag = 1; //设置转弯标志
    }
    else //小车掉头
    {
        ROS_WARN("turn Back ! yaw_data: %f", start_yaw_data);
        turnFlag = TURN_BACK;
    }

    controlTurn(turnFlag); //开始执行动作
}

/*****************************************************************************
 * Description: 初始化机器人走迷宫时的方向.
 ****************************************************************************/
void init_pose_angular(){
    float begin_yaw = 0.0;
    float now_left  = 0.0;
    float next_left  = 0.0;
    float now_right = 0.0;

    yawSrvClient.call(yawSrv);
    begin_yaw = yawSrv.response.yaw;
    distSrvClient.call(distSrv);
    now_left = distSrv.response.left_dist; //获取左边距离
    
    controlTurn(TURN_LEFT_10);
    distSrvClient.call(distSrv);
    next_left = distSrv.response.left_dist; //获取左边距离
    if(next_left > now_left){
        ROS_WARN("direction is left");
        angular_bias_symbol = -1.0;
    }else{
        ROS_WARN("direction is right");
    }

    controlTurn(TURN_RIGHT_10);
    //turnFlag = HORIZ_MOVE;
    //yawUpdate(begin_yaw);
    
    distSrvClient.call(distSrv);
    now_left = distSrv.response.left_dist; //获取左边距离
    now_right = distSrv.response.right_dist;//获取右边距离
    if(fabs(now_left-now_right)>init_tolerance_dist){
            horizMoveMiddle(init_tolerance_dist);
            ROS_WARN("horiz_move_middle");
    }

    yawSrvClient.call(yawSrv);
    begin_yaw = yawSrv.response.yaw;
    distSrvClient.call(distSrv);
    now_left = distSrv.response.left_dist; //获取左边距离
    now_right = distSrv.response.right_dist;//获取右边距离
    angular_bias = angular_bias_symbol*acos(forward_dist/(now_left+circle_dist+now_right));
    ROS_INFO("angular_bias:%f", angular_bias);

    controlTurn(TURN_BIAS);
    //turnFlag = TURN_BIAS;
    yawUpdate(begin_yaw);

    distSrvClient.call(distSrv);
    now_left = distSrv.response.left_dist; //获取左边距离
    now_right = distSrv.response.right_dist;//获取右边距离
    if(fabs(now_left-now_right)>init_tolerance_dist){
            horizMoveMiddle(init_tolerance_dist);
            ROS_WARN("horiz_move_middle");
    }

    ROS_INFO("Init pose angular finished !");
}

/*****************************************************************************
 * Description: 初始化机器人走迷宫时的位置..
 ****************************************************************************/
void init_pose_position(){
    float diff = 0.0; 
    float begin_yaw = 0.0;
    float now_front  = 0.0;

    turnFlag = VERTICAL_MOVE;
    yawSrvClient.call(yawSrv); //记录垂直移动前的角度,作为标准进行修正
    begin_yaw = yawSrv.response.yaw;

    distSrvClient.call(distSrv);
    now_front = distSrv.response.front_dist; //获取前边距离

    diff = now_front - wall_dist;
    while(fabs(diff)>tolerance_dist){
        if(diff < 0) //move backward
        {
            ROS_WARN("move backward vertically !");
            publishTwistCmd(-init_linear_x_speed, 0, 0);
        }
        else //move left
        {
            ROS_WARN("move forward  vertically !");
            publishTwistCmd(init_linear_x_speed, 0, 0);
        }
        

        distSrvClient.call(distSrv);
        now_front = distSrv.response.front_dist;

        diff = now_front - wall_dist; //计算前后距离差值
    }

    //当竖直结束后立刻停止移动
    publishTwistCmd(0, 0, 0); //stop move
    
    ros::Duration(0.1).sleep(); //delay 100ms
    yawUpdate(begin_yaw); //用于修正转歪的角度

    ROS_INFO("Init pose position finished !");
}

/*****************************************************************************
 * Description: 初始化机器人走迷宫时的位姿.
 ****************************************************************************/
void init_pose(){
    float init_left_dist = 0.0;
    float init_front_dist = 0.0;
    float init_right_dist = 0.0;

    distSrvClient.call(distSrv);
    init_left_dist = distSrv.response.left_dist;
    init_right_dist = distSrv.response.right_dist;
    if(fabs(init_left_dist-init_right_dist)>init_tolerance_dist){
            horizMoveMiddle(init_tolerance_dist);
            ROS_WARN("horiz_move_middle");
    }

    init_pose_angular();
    
    distSrvClient.call(distSrv);
    init_front_dist = distSrv.response.front_dist;
    if(fabs(init_front_dist-wall_dist)>tolerance_dist){
        init_pose_position();
        ROS_WARN("init_pose_position");
    }
    
}

/*****************************************************************************
 * Description: 订阅红外测距传感器话题后的回调函数,根据三个传感器数据进行走
 *   迷宫.
 ****************************************************************************/
void infrared_callback(const ros_arduino_msgs::InfraredSensors::ConstPtr& msg)
{
    ROS_INFO("front left right distance:[%f %f %f]", msg->front_dist,
            msg->left_dist, msg->right_dist);
    front_dist = msg->front_dist;
    left_dist  = msg->left_dist;
    right_dist = msg->right_dist;




     //根据三个传感器反馈的测距值开始移动
    checkInfraredDist(front_dist, left_dist, right_dist, tolerance_dist, warn_dist);
    yawUpdate(start_yaw_data); //移动完成后开始更新yaw值
    
}

/************************************************************
 * Description:主函数初始化节点,读取配置参数,订阅和发布话题,
 *   在订阅的红外测距数据话题回调函数中进行移动,通过调用yaw
 *   服务进行转弯角度的修正.
 ************************************************************/
int main(int argc, char **argv)
{
    std::string infrared_topic;
    std::string cmd_topic;
    std::string yaw_service;
    std::string infrared_service;

    ros::init(argc, argv, "infrared_maze_node");
    ros::NodeHandle handle;

    ros::param::get("~infrared_topic", infrared_topic);
    ros::param::get("~cmd_topic", cmd_topic);
    ros::param::get("~yaw_service", yaw_service);
    ros::param::get("~infrared_service", infrared_service);
    ros::param::get("~linear_x",  linear_x_speed);
    ros::param::get("~linear_y",  linear_y_speed);
    ros::param::get("~angular_speed", angular_speed);
    ros::param::get("~warn_dist", warn_dist);
    ros::param::get("~tolerance_dist", tolerance_dist);
    ros::param::get("~odom_frame", odomFrame);
    ros::param::get("~base_frame", baseFrame);
    ros::param::get("~forward_dist", forward_dist);
    ros::param::get("~circle_dist", circle_dist);
    ros::param::get("~wall_dist", wall_dist);
    ros::param::get("~init_tolerance_dist", init_tolerance_dist);
    ros::param::get("~init_switch", init_switch);
    ros::param::get("~init_linear_x",  init_linear_x_speed);
    ros::param::get("~init_linear_y",  init_linear_y_speed);
    ros::param::get("~init_angular_speed", init_angular_speed);

    twist_pub = handle.advertise<geometry_msgs::Twist>(cmd_topic, 1);
    yawSrvClient = handle.serviceClient<rasp_imu_hat_6dof::GetYawData>(yaw_service);
    distSrvClient = handle.serviceClient<ros_arduino_msgs::GetInfraredDistance>(infrared_service);
    
    if(init_switch){
        init_pose();
    }
    
    ros::Subscriber sub_infrared = handle.subscribe(infrared_topic, 1, infrared_callback);

    ros::spin();
    return 0;
}

