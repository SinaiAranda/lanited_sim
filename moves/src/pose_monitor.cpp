#include <moveit/move_group_interface/move_group_interface.h>

#include <iostream>
#include <ros/ros.h>
#include <fstream>



void save_pos(std::string file_name,    geometry_msgs::PoseStamped current_pose)

{
  std::ofstream myfile;
  myfile.open(file_name, std::fstream::out | std::fstream::app);

  myfile << current_pose.pose.position.x << "," << current_pose.pose.position.y << "," << current_pose.pose.position.z << "," << current_pose.pose.orientation.x << "," << current_pose.pose.orientation.y <<"," << current_pose.pose.orientation.z <<"," << current_pose.pose.orientation.w << "\n";
  
  myfile.close();
}


// The circle constant tau = 2*pi. One tau is one rotation in radians.
const double tau = 2 * M_PI;

int main(int argc, char** argv)
{

    int key_ch;
  ros::init(argc, argv, "pose_monitor");
  ros::NodeHandle node_handle;  
  ros::AsyncSpinner spinner(1);
  spinner.start();

  static const std::string PLANNING_GROUP = "arm";
  
  moveit::planning_interface::MoveGroupInterface arm_move(PLANNING_GROUP);

  

  // Getting Basic Information
  // ^^^^^^^^^^^^^^^^^^^^^^^^^
  //
  // We can print the name of the reference frame for this robot.
  ROS_INFO_NAMED("tutorial", "Planning frame: %s", arm_move.getPlanningFrame().c_str());

  // We can also print the name of the end-effector link for this group.
  ROS_INFO_NAMED("tutorial", "End effector link: %s", arm_move.getEndEffectorLink().c_str());

  // We can get a list of all the groups in the robot:
  ROS_INFO_NAMED("tutorial", "Available Planning Groups:");
  std::copy(arm_move.getJointModelGroupNames().begin(),
            arm_move.getJointModelGroupNames().end(), std::ostream_iterator<std::string>(std::cout, ", "));

 
   geometry_msgs::PoseStamped current_pose; 

   while (key_ch != 1)
   {
        current_pose = arm_move.getCurrentPose();
        ROS_INFO("Position %f %f %f %f %f %f  %f", current_pose.pose.position.x, current_pose.pose.position.y, current_pose.pose.position.z, current_pose.pose.orientation.x, current_pose.pose.orientation.y, current_pose.pose.orientation.z, current_pose.pose.orientation.w);
        std::cin >> key_ch;
        save_pos("positions.txt", current_pose);
        //ros::Duration(1.0).sleep();

   }
  
 
 ros::shutdown();
  return 0;
}
