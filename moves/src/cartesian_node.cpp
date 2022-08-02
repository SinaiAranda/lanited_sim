#include <moveit/move_group_interface/move_group_interface.h>


// The circle constant tau = 2*pi. One tau is one rotation in radians.
const double tau = 2 * M_PI;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "cartesian_node");
  ros::NodeHandle node_handle;  
  ros::AsyncSpinner spinner(1);
  spinner.start();

  static const std::string PLANNING_GROUP = "arm";
  
  moveit::planning_interface::MoveGroupInterface arm_move(PLANNING_GROUP);
 
  geometry_msgs::PoseStamped current_pose; 
  geometry_msgs::Pose start_pose2, target_pose3;
  std::vector<geometry_msgs::Pose> waypoints;
  moveit_msgs::RobotTrajectory trajectory;


  current_pose = arm_move.getCurrentPose();
  ROS_INFO("Position %f %f %f %f %f %f  %f", current_pose.pose.position.x, current_pose.pose.position.y, current_pose.pose.position.z, current_pose.pose.orientation.x, current_pose.pose.orientation.y, current_pose.pose.orientation.z, current_pose.pose.orientation.w);
 

// Cartesian Paths
  target_pose3 = start_pose2 = current_pose.pose ;
    
  waypoints.push_back(start_pose2);


  target_pose3.position.z -= 0.2;
  waypoints.push_back(target_pose3);  // down

  target_pose3.position.y -= 0.3;
  waypoints.push_back(target_pose3);  // right

  target_pose3.position.z += 0.1;
  target_pose3.position.y += 0.3;
  target_pose3.position.x += 0.3;
  waypoints.push_back(target_pose3);  // up and left

 
  const double jump_threshold = 0.0;
  const double eef_step = 0.01;
  double fraction = arm_move.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
  ROS_INFO_NAMED("tutorial", "Visualizing plan 4 (Cartesian path) (%.2f%% achieved)", fraction * 100.0);

  arm_move.execute(trajectory);


  ros::shutdown();
  return 0;
}
