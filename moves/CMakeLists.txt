cmake_minimum_required(VERSION 3.0.2)
project(moves)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  moveit_ros_planning_interface

  moveit_visual_tools
  rviz_visual_tools

)


catkin_package(
  INCLUDE_DIRS include
  LIBRARIES moves
  CATKIN_DEPENDS roscpp rospy
  DEPENDS system_lib
)


include_directories(

  ${catkin_INCLUDE_DIRS}
)


 add_executable(${PROJECT_NAME}_node src/moves_node.cpp)
 add_executable(pose_move_node src/pose_move_node.cpp)
 add_executable(pose_monitor src/pose_monitor.cpp)
 add_executable(visualize_plan src/visualize_plan.cpp)
 add_executable(cartesian_node src/cartesian_node.cpp)
 add_executable(objects src/objects.cpp)


 
 target_link_libraries(${PROJECT_NAME}_node  ${catkin_LIBRARIES} )
 target_link_libraries(pose_move_node ${catkin_LIBRARIES} )
 target_link_libraries(pose_monitor ${catkin_LIBRARIES} )
 target_link_libraries(visualize_plan ${catkin_LIBRARIES} )
 target_link_libraries(cartesian_node ${catkin_LIBRARIES} )
 target_link_libraries(objects ${catkin_LIBRARIES} )


 add_executable(read_moves src/read_moves.cpp)
 target_link_libraries(read_moves ${catkin_LIBRARIES} )


 add_executable(read_and_move src/read_and_move.cpp)
 target_link_libraries(read_and_move ${catkin_LIBRARIES} )

 add_executable(moveit_api src/moveit_api.cpp)
 target_link_libraries(moveit_api ${catkin_LIBRARIES} )

 add_executable(r1_moveit_api src/r1_moveit_api.cpp)
 target_link_libraries(r1_moveit_api ${catkin_LIBRARIES} )

 add_executable(r2_moveit_api src/r2_moveit_api.cpp)
 target_link_libraries(r2_moveit_api ${catkin_LIBRARIES} )

 add_executable(robot_model src/robot_model.cpp)
 target_link_libraries(robot_model ${catkin_LIBRARIES} )
