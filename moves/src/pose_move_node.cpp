#include <moveit/move_group_interface/move_group_interface.h>


// The circle constant tau = 2*pi. One tau is one rotation in radians.
const double tau = 2 * M_PI;

int main(int argc, char** argv)
{
      ros::init(argc, argv, "pose_move_node");
      ros::NodeHandle node_handle;  
      ros::AsyncSpinner spinner(1);
      spinner.start();

      static const std::string PLANNING_GROUP = "arm";

      moveit::planning_interface::MoveGroupInterface arm_move(PLANNING_GROUP);
      moveit::planning_interface::MoveGroupInterface::Plan move_plan;
      geometry_msgs::PoseStamped current_pose; 
      geometry_msgs::Pose target_pose1;
      geometry_msgs::Pose target_pose2;

      bool success ;


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

      current_pose = arm_move.getCurrentPose();
      ROS_INFO("Position %f %f %f %f %f %f  %f", current_pose.pose.position.x, current_pose.pose.position.y, current_pose.pose.position.z, current_pose.pose.orientation.x, current_pose.pose.orientation.y, current_pose.pose.orientation.z, current_pose.pose.orientation.w);

      // Planning to a Pose goal
      // ^^^^^^^^^^^^^^^^^^^^^^^
      // We can plan a motion for this group to a desired pose for the
      // end-effector.
      target_pose1.orientation.w = 0.0;
      target_pose1.orientation.x = 1.0;
      target_pose1.orientation.y = 0.0;
      target_pose1.orientation.z = 0.0;

      target_pose1.position.x = 0.28;
      target_pose1.position.y = -0.2;
      target_pose1.position.z = 0.5;

      target_pose2.orientation.w = 0.0;
      target_pose2.orientation.x = -1.0;
      target_pose2.orientation.y = 0.0;
      target_pose2.orientation.z = 0.0;

      target_pose2.position.x = 0.68;
      target_pose2.position.y = -0.14;
      target_pose2.position.z = 0.5;

      arm_move.setPoseTarget(target_pose1);

      success = (arm_move.plan(move_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);

      ROS_INFO_NAMED("tutorial", "Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");

      //arm_move.execute(move_plan);

      arm_move.move();

      arm_move.setPoseTarget(target_pose2);
      success = (arm_move.plan(move_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);

      ROS_INFO_NAMED("tutorial", "Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");

      //arm_move.execute(move_plan);

      arm_move.move();

      arm_move.setPoseTarget(target_pose1);

      success = (arm_move.plan(move_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);

      ROS_INFO_NAMED("tutorial", "Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");

      //arm_move.execute(move_plan);

      arm_move.move();


 ros::shutdown();
  return 0;
}
