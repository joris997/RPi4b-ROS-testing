cmake_minimum_required(VERSION 2.8.3)
project(tele_op_python)

find_package(catkin REQUIRED COMPONENTS message_generation rospy)
catkin_package()

catkin_install_python(PROGRAMS src/keypress.py DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
