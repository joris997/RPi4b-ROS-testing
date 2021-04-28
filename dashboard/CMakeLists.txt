cmake_minimum_required(VERSION 3.0.2)
project(dashboard_python)

find_package(catkin REQUIRED COMPONENTS message_generation rospy)
catkin_package()

catkin_install_python(PROGRAMS src/dashboard.py DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

#include_directories(include ${catkin_INCLUDE_DIRS})
#add_executable(gy6500 src/main.cpp src/gy6500.cpp)

#target_link_libraries(gy6500 ${catkin_LIBRARIES} pigpiod_if2 pigpio)
