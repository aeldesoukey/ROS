---------------------------------------------------------
                   General information
---------------------------------------------------------

the package is built using ROS-kinetic & Ubuntu 
16.04.1 the following commands assume that the package 
is in your  home folder and all terminals will run in 
package folder, for any change just change 
the directory in each command.

---------------------------------------------------------
                   package description
---------------------------------------------------------

this package is used to compare between the preformance 
of the following motion planning packages:

-riskrrt
-move_base using A* as global planner
 
the comparison is done by mearsuring the following:

-run time 
-excution time
-path length
-explored nodes
-path smoothness 

---------------------------------------------------------
		Building Dependency Packages
---------------------------------------------------------

sudo apt-get install ros-kinetic-control*
sudo apt-get install ros-kinetic-velocity-controllers
sudo apt-get install ros-kinetic-joint-*
sudo apt-get install ros-kinetic-gazebo-*
sudo apt-get install ros-kinetic-rviz*
sudo apt-get install ros-kinetic-move-base*
sudo apt-get install ros-kinetic-navigation*

---------------------------------------------------------
		  Building The Package
---------------------------------------------------------

cd ~/Project
catkin_make
source devel/source.bash

---------------------------------------------------------
                   package information
---------------------------------------------------------

----------------------- nodes ---------------------------

-goal_publisher_A_star: publish goal after 10 seconds 
                  args: x(m),y (m), theta (deg)
      published topics: move_base_simple/goal 
-goal_publisher_rrt   : publish goal after 10 seconds 
                  args: x(m),y (m)
      published topics: goal 
-watcher_A_star       : measure evalution metric of A* 
     subscribed topics: move_base_simple/goal
			move_base/result
			odom
			move_base/GlobalPlanner/plan
			move_base/GlobalPlanner/potential
-watcher_rrt          : measure evalution metric of rrt
     subscribed topics: goal
			node_markers
			odom
			goal_reached
-amcl_pos_publisher   : remap from odom to amcl_pose
     subscribed topics: odom
      published topics: amcl_pose
---------------------------------------------------------

------------------------ URDF ---------------------------

-catbot               : robot description of differential
			robot included diff_drive plugin
---------------------------------------------------------

------------------------ Map ----------------------------

-map                  : 504x434 pixels with resolution of
			25 pixel/m with total size of 
			20.1x17.7 m
-zc_hall	      : 500x500 pixels with resolution of
			7.8125 pixel/m with total size of 
			64x64 m
---------------------------------------------------------

----------------------- World ---------------------------

-map                  : gazebo world file for "map"

-zc_hall              : gazebo world file for "zc_hall"

----------------------- launch --------------------------

-A_star_main          : loads "map" as map file
		        launchs move_base_A_star.launch
		        runs goal_publisher_A_star node
		        runs watcher_A_star node
		        
-A_star_zc_main       : loads "zc_hall" as map
		        launchs move_base_A_star_zc.launch
		        runs goal_publisher_A_star node
		        runs watcher_A_star node 

-rrt_main             : loads "map" as map file
	  	       	launchs rrt.launch
		       	runs goal_publisher_rrt node
		       	runs watcher_rrt node
		       	runs amcl_pos_publisher node

-rrt_zc_main          : loads "zc_hall" as map file
		       	launchs rrt.launch
		       	runs goal_publisher_rrt node
		       	runs watcher_rrt node
		       	runs amcl_pos_publisher node

-rrt                  : runs rviz node
		        loads catbot as robot_description
		        runs joint_state_publisher node
		       	runs robot_state_publisher node
		       	runs og_builder_stage node
		       	launchs gazebo_map
		       	runs urdf_spawner node
		       	runs riskrrt_planner node
		       	runs controller node

-rrt_zc               : runs rviz node
		       	loads catbot as robot_description
		       	runs joint_state_publisher node
		       	runs robot_state_publisher node
		       	runs og_builder_stage node
		       	launchs gazebo_map_zc
		       	runs urdf_spawner node
		       	runs riskrrt_planner node
		       	runs controller node

-move_base_A_star     : runs rviz node
		        loads catbot as robot_description
		        runs joint_state_publisher node
		       	runs robot_state_publisher node
		       	launchs gazebo_map
		       	runs urdf_spawner node
		       	runs move_base node

-move_base_A_star_zc  : runs rviz node
		        loads catbot as robot_description
		        runs joint_state_publisher node
		        runs robot_state_publisher node
		        launchs gazebo_map_zc
		        runs urdf_spawner node
		        runs move_base node

-gazebo_map           : launchs map world
 
-gazebo_map_zc        : launchs zc_hall world

---------------------------------------------------------
                  Launching The Package 
---------------------------------------------------------

roslaunch catbot A_star_main.launch
roslaunch catbot A_star_zc_main.launch
roslaunch catbot rrt_main.launch
roslaunch catbot rrt_zc_main.launch

---------------------------------------------------------
                  	Notes 
---------------------------------------------------------

-to change goal point please change the argument of node
goal_publisher_rrt/goal_publisher_A_star
 
-to change initial position please change the argument
of node rviz

---------------------------------------------------------
                    Acknowledgments
---------------------------------------------------------

-mastering_ros        : its URDF file has been used
 https://github.com/qboticslabs/mastering_ros.git

-riskrrt_ros          :
 https://github.com/spalanza/riskrrt_ros.git

---------------------------------------------------------
