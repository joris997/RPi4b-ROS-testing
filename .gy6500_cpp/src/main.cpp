//#include <gy6500.h>
#include <ros/ros.h>
extern "C" {
  #include <pigpio.h>
  #include <pigpiod_if2.h>
}
#include <iostream>
#include <sensor_msgs/Imu.h>

int pi = pigpio_start(nullptr,nullptr);

// constants
int BUS = 1;
#define DEVICE_ADDRESS 0x68
#define PWR_MGMT_1     0x6B
#define SMPLRT_DIV     0x19
#define CONFIG         0x1A
#define GYRO_CONFIG    0x1B
#define INT_ENABLE     0x38
#define ACCEL_XOUT_H   0x3B
#define ACCEL_YOUT_H   0x3D
#define ACCEL_ZOUT_H   0x3F
#define GYRO_XOUT_H    0x43
#define GYRO_YOUT_H    0x45
#define GYRO_ZOUT_H    0x47


int main(int argc, char **argv){
  ros::init(argc, argv, "gy6500");
  int i2c = i2c_open(pi,BUS,DEVICE_ADDRESS,0);
  if (i2c <= 0){
    ROS_INFO_STREAM("cannot init IMU");
    return 1;
  }

  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<sensor_msgs::Imu>("/gy6500",1);
  ros::Rate rate(10);

  sensor_msgs::Imu msg;

  while(ros::ok()){
    //int ax = i2c_read_byte_data(pi,i2c,ACCEL_XOUT_H);
    //int ay = i2c_read_byte_data(pi,i2c,ACCEL_YOUT_H);
    //int ax_chk = i2c_read_i2c_block_data(pi,i2c,ACCEL_XOUT_H,char *ax,8);
    //int ay_chk = i2c_read_i2c_block_data(pi,i2c,ACCEL_YOUT_H,char *ay,8);
    
    int16_t ax = i2c_read_byte_data(pi,i2c,ACCEL_XOUT_H);
    int16_t ay = i2c_read_byte_data(pi,i2c,ACCEL_YOUT_H);

    // FILL SNESOR MESSAGE
    msg.header.stamp = ros::Time::now();
    msg.linear_acceleration.x = (float) ax;
    msg.linear_acceleration.y = (float) ay;
    msg.linear_acceleration.z = 0;
    msg.orientation.x = 0;
    msg.orientation.y = 0;
    msg.orientation.z = 0;
    msg.orientation.w = 0;
    msg.angular_velocity.x = 0;
    msg.angular_velocity.y = 0;
    msg.angular_velocity.z = 0;
    
    // PUBLISH AND SLEEP
    ROS_INFO_STREAM("ax: " << (float) ax << ", ay: " << (float) ay);
    pub.publish(msg);
    rate.sleep();
  }
  gpioTerminate();
  return 0;
}
