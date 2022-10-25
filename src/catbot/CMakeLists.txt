cmake_minimum_required(VERSION 2.8.3)
project(catbot)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  std_msgs
  tf
  gazebo_ros
  visualization_msgs
  message_generation
  nav_msgs
  geometry_msgs
)

## System dependencies are found with CMake's conventions
find_package(gazebo REQUIRED)

include_directories(include ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS} ${SDFormat_INCLUDE_DIRS})

add_message_files(
  FILES
  OccupancyGridArray.msg
  PoseTwistStamped.msg
  Trajectory.msg
)
generate_messages(
  DEPENDENCIES
  std_msgs
  nav_msgs
  geometry_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)
 catkin_package(
    DEPENDS
      gazebo_ros
    CATKIN_DEPENDS
    INCLUDE_DIRS
    LIBRARIES
)



include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(goal_publisher_A_star src/goal_publisher_A_star.cpp)
target_link_libraries(goal_publisher_A_star ${catkin_LIBRARIES})

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(goal_publisher_rrt src/goal_publisher_rrt.cpp)
target_link_libraries(goal_publisher_rrt ${catkin_LIBRARIES})

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(watcher_A_star src/watcher_A_star.cpp)
target_link_libraries(watcher_A_star ${catkin_LIBRARIES})

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(watcher_rrt src/watcher_rrt.cpp)
target_link_libraries(watcher_rrt ${catkin_LIBRARIES})

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(amcl_pos_publisher src/amcl_pos_publisher.cpp)
target_link_libraries(amcl_pos_publisher ${catkin_LIBRARIES})
