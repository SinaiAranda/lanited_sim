#include <moveit/move_group_interface/move_group_interface.h>

#include <fstream>
#include <iostream>
using namespace std;


int main(int argc, char **argv)
{
  ros::init(argc, argv, "read_moves");

  ros::NodeHandle n;
  geometry_msgs::Pose target_point;
  std::vector<geometry_msgs::Pose> waypoints;


  

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
   /* 
  // modern way to access vectors'array
    for (auto row : ex_data) 
        {
        for (auto field : row) 
          {
            cout << field << ' ';
         }

        cout << '\n';
    }
   // traditional way of access the vectors' array
    for (int i = 0; i < ex_data.size(); i++) 
        {
        for (int j = 0; j < ex_data[i].size(); j++)
            cout << ex_data[i][j] << " ";

        cout << endl;
     }
  */

 for (int i = 0; i < ex_data.size(); i++) 
    {
      target_point.position.x = ex_data[i][0];
      target_point.position.y = ex_data[i][1];
      target_point.position.z = ex_data[i][2];
      target_point.orientation.x = ex_data[i][3];
      target_point.orientation.y = ex_data[i][4];
      target_point.orientation.z = ex_data[i][5];
      target_point.orientation.w = ex_data[i][6];
      /*     
      ROS_INFO(" ROW %d", i); 
              
      cout << target_point.position.x << endl;
      cout << target_point.position.y << endl;
      cout << target_point.position.z << endl;
      cout << target_point.orientation.x << endl;
      cout << target_point.orientation.y << endl;
      cout << target_point.orientation.z << endl;
      cout << target_point.orientation.w << endl;
        */    
      waypoints.push_back(target_point);

      cout << waypoints[i] << endl;
   }


  return 0;
}
