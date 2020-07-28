
#include <ros/ros.h>
//#include <wiringPi.h>
extern "C" {
	#include <pigpio.h>
}
#include <std_msgs/Bool.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "blinking_led");
	ros::NodeHandle nh;
	ros::Publisher pub = nh.advertise<std_msgs::Bool>("ledstatus",1);
	ros::Rate rate(10);

	std_msgs::Bool msg;
	msg.data = false;

	//wiringPiSetup();
	//pinMode(4,OUTPUT);
	if (gpioInitialise() < 0){
		ROS_INFO_STREAM("pigpio init failed");
		return 1;
	}
	gpioSetMode(4,PI_OUTPUT);

	while(ros::ok()){
		if(msg.data == false){
			msg.data = true;
			//digitalWrite(4,HIGH);
			gpioWrite(4,1);
		}
		else{
			msg.data = false;
			//digitalWrite(4,LOW);
			gpioWrite(4,0);
		}
		if (msg.data == true){
			ROS_INFO_STREAM("Sending led status: true");
		}
		else{
			ROS_INFO_STREAM("Sending led status: false");
		}
		//ROS_INFO_STREAM("Sending led status: " << msg.data);
		pub.publish(msg);

		rate.sleep();
	}
	gpioTerminate();
	return 0;
}
