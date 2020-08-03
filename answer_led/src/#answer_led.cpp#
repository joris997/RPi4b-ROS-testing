// Author: Joris Verhagen
// Original creation: 29-08-2020
// This ROS package is a publisher and subscriber that, at the rate of incoming
// messages, listens to whether or not the led from "blinking_led" is on or off
// It uses a physical GPIO pin on the Raspberry Pi 4B to mimic the behavior of
// the listened to led. Therefore, by connecting a led and resistor in series
// from the GPIO pin to the ground pin should show you the blinking at the
// same rate as "blinking_led". Additionally, it publishes the amount of times
// that the led has been 'on' over "/blinkcnt".

#include <ros/ros.h>
extern "C" {
#include <pigpio.h>
}
#include <std_msgs/Bool.h>
#include <std_msgs/Int8.h>
#include <stdlib.h>

ros::Publisher pub;
std_msgs::Int8 ctr;

void statusMessageReceived(const std_msgs::Bool &msg){
  if (msg.data == true){
    ROS_INFO_STREAM("Sender led status: true");
    gpioWrite(7,1);
    ctr.data += 1;
  }
  else{
    ROS_INFO_STREAM("Sender led status: false");
    gpioWrite(7,0);
  }

  ros::NodeHandle nh2;
  pub = nh2.advertise<std_msgs::Int8>("/blinkcnt",1);
  ROS_INFO_STREAM("led has now blinked " << ctr << " times!");
  pub.publish(ctr);
}


int main(int argc, char **argv){
  ros::init(argc, argv, "answer_led");

  if (gpioInitialise() < 0){
    ROS_INFO_STREAM("pigpio init failed");
    return 1;
  }
  gpioSetMode(5,PI_OUTPUT);
  
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("ledstatus",1,&statusMessageReceived);
  ros::spin();
}
