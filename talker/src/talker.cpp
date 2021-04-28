#include <ros/ros.h>

int main(int argc, char **argv){
	ros::init(argc,argv,"talker");
	ros::NodeHandle nh;
	ROS_INFO_STREAM("Hello ROS!");
}
