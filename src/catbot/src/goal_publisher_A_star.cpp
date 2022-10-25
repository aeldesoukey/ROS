#include "ros/ros.h"
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <unistd.h>
#include <tf/transform_datatypes.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "goal_pub");
  ros::NodeHandle n;
  
  if (argc != 4){
    ROS_INFO("USAGE: goal_pub [x] [y]");
    return 0;
  }
  
  ros::Publisher goal_pub = n.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 1000);
  
  geometry_msgs::PoseStamped goal_msg;
  goal_msg.pose.position.x = atof(argv[1]);
  goal_msg.pose.position.y = atof(argv[2]);
  tf::Quaternion q = tf::createQuaternionFromRPY(0,0,atof(argv[3])*3.14159265359/180);

  goal_msg.pose.orientation.x = q.getX();
  goal_msg.pose.orientation.y = q.getY();
  goal_msg.pose.orientation.z = q.getZ();
  goal_msg.pose.orientation.w = q.getW();
  goal_msg.header.frame_id = "odom";
  goal_msg.header.stamp = ros::Time::now();
  ros::Rate loop_rate(100);
  
  
  while(goal_pub.getNumSubscribers() == 0){
    loop_rate.sleep();
  }
  
  ros::Duration(5.0).sleep();

  goal_pub.publish(goal_msg);

  return 0;
}
