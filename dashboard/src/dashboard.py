#!/usr/bin/python
import math
import os
import time
import rospy
from sensor_msgs.msg import Imu

def callback(data):
    os.system("clear")
    print "time: ", data.header.stamp
    print "gx: ", data.angular_velocity.x
    print "gy: ", data.angular_velocity.y
    print "gz: ", data.angular_velocity.z
    
    print "ax: ", data.linear_acceleration.x
    print "ay: ", data.linear_acceleration.y
    print "az: ", data.linear_acceleration.z

def display():
    pub = rospy.Subscriber('gy6500',Imu,callback)
    rospy.init_node('dasgboard',anonymous=True)
    rospy.spin()


if __name__ == '__main__':
    try:
        display()
    except rospy.ROSInterruptException:
        pass

