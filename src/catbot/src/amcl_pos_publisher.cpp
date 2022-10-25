#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
ros::Publisher pub;
void Callback1(const nav_msgs::Odometry::ConstPtr& msg)
{

  geometry_msgs::PoseWithCovarianceStamped msg2;
  msg2.pose = msg->pose;
  msg2.header = msg->header;
  pub.publish(msg2);

}

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "amcl_pos_publisher");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe<nav_msgs::Odometry> ("odom",10,Callback1);
  pub = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("amcl_pose",10);
  ros::spin();
}
