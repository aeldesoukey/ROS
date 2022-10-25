#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <move_base_msgs/MoveBaseActionResult.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/OccupancyGrid.h>

double time3=0, time2=0, time1=0;
int new_goal_flag = 0;
int new_goal_flag1 = 0;
int new_goal_flag2 = 0;
nav_msgs::Odometry old_odom;
nav_msgs::OccupancyGrid grid;
double total_distance = 0;

void Callback1(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
  time1 = msg->header.stamp.toSec();
  new_goal_flag = 1;
  new_goal_flag1 = 1;
  new_goal_flag2 = 1;
}
void Callback2(const move_base_msgs::MoveBaseActionResult::ConstPtr& msg)
{
  if(new_goal_flag)
  {

    time2 = msg->header.stamp.toSec();
    new_goal_flag = 0;
  }

}

void Callback3(const nav_msgs::Odometry::ConstPtr& msg)
{

  total_distance += sqrt(pow((msg->pose.pose.position.x-old_odom.pose.pose.position.x),2)+pow((msg->pose.pose.position.y-old_odom.pose.pose.position.y),2));
  old_odom.pose.pose.position.x = msg->pose.pose.position.x;
  old_odom.pose.pose.position.y = msg->pose.pose.position.y;
}
void Callback4(const nav_msgs::Path::ConstPtr& msg)
{
  if(new_goal_flag1)
  {
    time3 = msg->header.stamp.toSec();
    new_goal_flag1 = 0;
  }

}
void Callback5(const nav_msgs::OccupancyGrid::ConstPtr& msg)
{
  if(new_goal_flag2)
  {
    grid = *msg;
    new_goal_flag2 = 0;
  }

}
int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "watcher_A_star");
  ros::NodeHandle n;
  ros::Duration(5).sleep();
  ros::Subscriber sub1 = n.subscribe<geometry_msgs::PoseStamped>("move_base_simple/goal",10,Callback1);
  ros::Subscriber sub2 = n.subscribe<move_base_msgs::MoveBaseActionResult>("move_base/result",10,Callback2);
  ros::Subscriber sub3 = n.subscribe<nav_msgs::Odometry>("odom",10,Callback3);
  ros::Subscriber sub4 = n.subscribe<nav_msgs::Path>("move_base/GlobalPlanner/plan",10,Callback4);
  ros::Subscriber sub5 = n.subscribe<nav_msgs::OccupancyGrid>("move_base/GlobalPlanner/potential",10,Callback5);

  while(ros::ok())
  {

    if(time2 != 0 && time1 !=0)
    {
      int size = grid.data.size();
      int number_nodes =0;
      for (int i= 0; i < size; i++)
      {


        if (grid.data.data()[i] != -1)
          number_nodes++;
      }
      ROS_INFO("the number of explored nodes is = %d\n",number_nodes);
      double delta_t = time2 - time1;
      double delta_t1 = time3 - time1;
      ROS_INFO("the excutiontime is = %f\n",delta_t);
      ROS_INFO("the runtime is = %f\n",delta_t1);
      ROS_INFO("the total length is = %f\n",total_distance);
      time3 = 0;
      time2 = 0;
      time1 = 0;
      total_distance = 0;

    }
    ros::spinOnce();
  }
}
