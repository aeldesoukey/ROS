#include <ros/ros.h>
#include <std_msgs/Time.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>
#include <visualization_msgs/MarkerArray.h>

double time3=0, time2=0, time1=0;
int node_counter = 0;
int new_goal_flag = 0;
int new_goal_flag1 = 0;
double total_distance = 0;
nav_msgs::Odometry old_odom;

void Callback1(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
  time1 = msg->header.stamp.toSec();
  new_goal_flag = 1;
  new_goal_flag1 = 1;
}
void Callback2(const visualization_msgs::MarkerArray::ConstPtr& msg)
{
  node_counter+= msg->markers.size();

}

void Callback3(const nav_msgs::Odometry::ConstPtr& msg)
{

  total_distance += sqrt(pow((msg->pose.pose.position.x-old_odom.pose.pose.position.x),2)+pow((msg->pose.pose.position.y-old_odom.pose.pose.position.y),2));
  old_odom.pose.pose.position.x = msg->pose.pose.position.x;
  old_odom.pose.pose.position.y = msg->pose.pose.position.y;
}
void Callback4(const std_msgs::Time::ConstPtr& msg)
{
  if(new_goal_flag1)
  {
    time3 = msg->data.toSec();
    new_goal_flag1 = 0;
  }
  ROS_INFO("%f  %f  %d",time3,time1,new_goal_flag1);

}

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "time_watcher");
  ros::NodeHandle n;
  ros::Duration(5).sleep();
  ros::Subscriber sub1 = n.subscribe<geometry_msgs::PoseStamped>("goal",10,Callback1);
  ros::Subscriber sub2 = n.subscribe<visualization_msgs::MarkerArray>("node_markers",10,Callback2);
  ros::Subscriber sub3 = n.subscribe<nav_msgs::Odometry>("odom",10,Callback3);
  ros::Subscriber sub4 = n.subscribe<std_msgs::Time>("goal_reached",10,Callback4);

  while(ros::ok())
  {

    if(time3 != 0 && time1 !=0)
    {
      ROS_INFO("the number of explored nodes is = %d\n",node_counter);
      double delta_t = time2 - time1;
      double delta_t1 = time3 - time1;
      ROS_INFO("the excutiontime is = %f\n",delta_t);
      ROS_INFO("the runtime is = %f\n",delta_t1);
      ROS_INFO("the total length is = %f\n",total_distance);
      time3 = 0;
      time2 = 0;
      time1 = 0;
      node_counter = 0;
      total_distance = 0;

    }
    ros::spinOnce();
  }
}
