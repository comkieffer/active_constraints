//
// Created by nima on 08/03/17.
//


#include <iostream>
#include "ActiveConstraintEnforcementMethods.hpp"

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include "ACGeometryGeneration.h"


// THIS NODE WILL PROBABLY NOT BE NEEDED ANYMORE IN NEAR FUTURE

int main(int argc, char *argv[]) {


    ros::init(argc, argv, "dvrk_ac");
    ACGeometryGeneration r(ros::this_node::getName());

    ros::Rate loop_rate(r.ros_freq);

    ros::Rate one_second_sleep(1);
    one_second_sleep.sleep();

//    r.GenerateXYCircle(KDL::Vector(0.045, 0.03, 0.0), 0.025, 200, ac_path);
//
//    r.publisher_ac_path.publish(ac_path);

    bool first_run = true;

    while(ros::ok()){

//        if(first_run){
//            r.tool_pose_desired[0] =  r.tool_pose_current[0];
//
//  //           r.tool_pose_desired[0].p[0] =  -0.148796232892;
//  //          r.tool_pose_desired[0].p[1] =  -0.0103239386941;
//  //           r.tool_pose_desired[0].p[2] =  -0.2331;
//
//            ROS_INFO_STREAM(std::string("p_desired[0] = ") << r.tool_pose_desired[0].p);
//            first_run = false;
//        }
        // publish the desired point only if we have received the ac_path recently
        if(r.ac_path_received && (ros::Time::now() - r.ac_path_time_stamp) < ros::Duration(0.5) ) {
            r.ClosestPointToACPoints(r.tool_pose_current[0].p, r.ac_path, r.tool_pose_desired[0].p);
            r.PublishDesiredPose();
        }

        r.PublishCurrentPose();

        r.PublishCurrentTwist();

        loop_rate.sleep();
        ros::spinOnce();

        //		}

    }

    ROS_INFO("Ending Session...\n");
    ros::shutdown();

    return 0;
}
