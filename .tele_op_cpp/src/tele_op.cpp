// Author: Joris Verhagen
// Original creation: 26-04-2021
// This ROS package listens for keyboard inputs and sends it as a message to subscribes
// For example, blinking_led might change its frequency depending on the incoming integer

#include <ros/ros.h>
#include <iostream>
#include "keyboard.h"

int main(int argc, char **argv){
	ros::init(argc,argv,"tele_op");

	ros::NodeHandle nh;
	ros::Publisher pub_down = nh.advertise<keyboard::Key>("/teleop_down",1);
	ros::Publisher pub_up   = nh.advertise<keyboard::Key>("/teleop_up",1);
	ros::Rate rate(10);

	bool allow_repeat = false;
	int repeat_delay, repeat_interval;

	nh.param<bool>("allow_repeat",allow_repeat,false);
	nh.param<int>("repeat_delay",repeat_delay,SDL_DEFAULT_REPEAT_DELAY);
	nh.param<int>("repeat_interval",repeat_interval,SDL_DEFAULT_REPEAT_INTERVAL);

	if (!allow_repeat){
		repeat_delay = 0;
	}
	keyboard::Keyboard kbd(repeat_delay,repeat_interval);

	keybaord::Key k;
	bool pressed, new_event;
	while (ros::ok() && kbd.get_key(new_event,pressed,k.code,k.modifiers)){
		if (new_event){
			k.header.stamp = ros::Time::now();
			if (pressed){
				pub_down.publish(k);
			} else {
				pub_up.publish(k);
			}
		}
		ros::spinOnce();
		r.sleep();
	}
	
	ros::waitForShutdown();
}
