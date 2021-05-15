#!/usr/bin/python
import smbus
import math
import os
import time
import rospy
from sensor_msgs.msg import Imu

# Register
power_mgmt_1 = 0x6b
power_mgmt_2 = 0x6c

# init sensor
bus = smbus.SMBus(1)
address = 0x68
bus.write_byte_data(address,power_mgmt_1, 0)

def measure():
    # init ros 
    pub = rospy.Publisher('motor',Imu,queue_size=1)
    rospy.init_node('motor_python',anonymous=True)
    rate = rospy.Rate(10)

    while not rospy.is_shutdown():
                
        rate.sleep()


if __name__ == '__main__':
    try:
        measure()
    except rospy.ROSInterruptException:
        pass

