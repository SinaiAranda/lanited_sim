#include <moveit/move_group_interface/move_group_interface.h>


#include <fstream>
#include <iostream>
using namespace std;

// The circle constant tau = 2*pi. One tau is one rotation in radians.
const double tau = 2 * M_PI;

int main(int argc, char** argv)
{
        ros::init(argc, argv, "read_and_move");
        ros::NodeHandle node_handle;  
        ros::AsyncSpinner spinner(1);
        spinner.start();

        static const std::string PLANNING_GROUP = "arm";

        moveit::planning_interface::MoveGroupInterface arm_move(PLANNING_GROUP);
        moveit::planning_interface::MoveGroupInterface::Plan move_plan;
        geometry_msgs::PoseStamped current_pose; 
        geometry_msgs::Pose target_point;
        std::vector<geometry_msgs::Pose> waypoints;
        bool success ;
        const double jump_threshold = 0.0;
        const double eef_step = 0.01;
        double fraction; 
        moveit_msgs::RobotTrajectory trajectory;





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

        //Reading positions file TXT

        // load data test from experiments
        ifstream in("positions.txt");
        vector<vector<float>> ex_data;

        if (in) {
            string line;

            while (getline(in, line)) {
                stringstream sep(line);
                string field;

                ex_data.push_back(vector<float>());

                while (getline(sep, field, ',')) {
                    ex_data.back().push_back(stod(field));
                }
            }
        }
        for (int i = 0; i < ex_data.size(); i++) 
            {
            target_point.position.x = ex_data[i][0];
            target_point.position.y = ex_data[i][1];
            target_point.position.z = ex_data[i][2];
            target_point.orientation.x = ex_data[i][3];
            target_point.orientation.y = ex_data[i][4];
            target_point.orientation.z = ex_data[i][5];
            target_point.orientation.w = ex_data[i][6];
            
            waypoints.push_back(target_point);

            }


      // Planning all positions Pose move and excecute
      // ^^^^^^^^^^^^^^^^^^^^^^^
        for (int j=0; j< waypoints.size();j++)
            {

             cout << j << " " << waypoints[j] << endl;

            arm_move.setPoseTarget(waypoints[j]);

            success = (arm_move.plan(move_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);

            ROS_INFO_NAMED("tutorial", "Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");

            arm_move.execute(move_plan);

            //arm_move.move();
            }

      // Planning all positions Cartesian move and excecute
      // ^^^^^^^^^^^^^^^^^^^^^^^
        fraction = arm_move.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
        ROS_INFO_NAMED("tutorial", "Visualizing plan 4 (Cartesian path) (%.2f%% achieved)", fraction * 100.0);

        arm_move.execute(trajectory);

            
      

 ros::shutdown();
  return 0;
}
