// Author: Joris Verhagen
// Original creation: 27-08-2020
// This ROS package is a publisher that, at a rate of 10ms, turns on and off a led
// while publishing the status of the led as a boolean over "/ledstatus"
// It uses a physical GPIO pin on the Raspberry Pi 4B and subsequentally by connecting
// a led and resistor in series from the GPIO pin to the ground pin should show you
// the blinking

#include <ros/ros.h>
extern "C" {
#include <pigpio.h>
}
#include <std_msgs/Bool.h>
#include <stdlib.h>

int main(int argc, char **argv){
	ros::init(argc, argv, "blinking_led");
	
	if (gpioInitialise() < 0){
		ROS_INFO_STREAM("pigpio init failed");
		return 1;
	}
	gpioSetMode(4,PI_OUTPUT)
	
	ros::NodeHandle nh;
	ros::Publisher pub = nh.advertise<std_msgs::Bool>("/ledstatus",1);
	ros::Rate rate(10);

	std_msgs::Bool msg;
	msg.data = false;

	while(ros::ok()){
		if(msg.data == false){
			msg.data = true;
			gpioWrite(4,1);
		}
		else{
			msg.data = false;
			gpioWrite(4,0);
		}
		if (msg.data == true){
			ROS_INFO_STREAM("Sending led status: true");
		}
		else{
			ROS_INFO_STREAM("Sending led status: false");
		}
		pub.publish(msg);

		rate.sleep();
	}
	gpioTerminate();
	return 0;
}
