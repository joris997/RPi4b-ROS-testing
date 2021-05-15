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

 
def read_byte(reg):
    return bus.read_byte_data(address,reg)
 
def read_word(reg):
    h = bus.read_byte_data(address,reg)
    l = bus.read_byte_data(address,reg+1)
    value = (h << 8) + l
    return value
 
def read_word_2c(reg):
    val = read_word(reg)
    if (val >= 0x8000):
        return -((65535 - val) + 1)
    else:
        return val
 
def dist(a,b):
    return math.sqrt((a*a)+(b*b))
 
def get_y_rotation(x,y,z):
    radians = math.atan2(x, dist(y,z))
    return -math.degrees(radians)
 
def get_x_rotation(x,y,z):
    radians = math.atan2(y, dist(x,z))
    return math.degrees(radians)


def measure():
    # init ros 
    pub = rospy.Publisher('gy6500',Imu,queue_size=1)
    rospy.init_node('gy6500_python',anonymous=True)
    rate = rospy.Rate(10)

    while not rospy.is_shutdown():
        gx = read_word_2c(0x43)
        gy = read_word_2c(0x45)
        gz = read_word_2c(0x47)
        gx_scaled = gx / 131.0
        gy_scaled = gy / 131.0
        gz_scaled = gz / 131.0
 
        ax = read_word_2c(0x3b)
        ay = read_word_2c(0x3d)
        az = read_word_2c(0x3f)
        ax_scaled = ax / 16384.0
        ay_scaled = ay / 16384.0
        az_scaled = az / 16384.0

        imu = Imu()
        imu.header.stamp = rospy.Time.now()
        imu.angular_velocity.x = gx_scaled
        imu.angular_velocity.y = gy_scaled
        imu.angular_velocity.z = gz_scaled
        imu.linear_acceleration.x = ax_scaled
        imu.linear_acceleration.y = ay_scaled
        imu.linear_acceleration.z = az_scaled

        pub.publish(imu)
        
        os.system("clear")
        print "gx: ", ("%5d" % gx), " scaled: ", ("%.2f" % gx_scaled)
        print "gy: ", ("%5d" % gy), " scaled: ", ("%.2f" % gy_scaled)
        print "gz: ", ("%5d" % gz), " scaled: ", ("%.2f" % gz_scaled)
     
        print "ax: ", ("%6d" % ax), " scaled: ", ("%.2f" % ax_scaled)
        print "ay: ", ("%6d" % ay), " scaled: ", ("%.2f" % ay_scaled)
        print "az: ", ("%6d" % az), " scaled: ", ("%.2f" % az_scaled)
     
        print "X Rotation: " , get_x_rotation(ax_scaled, ay_scaled, az_scaled)
        print "Y Rotation: " , get_y_rotation(ax_scaled, ay_scaled, az_scaled)
        
        rate.sleep()


if __name__ == '__main__':
    try:
        measure()
    except rospy.ROSInterruptException:
        pass

