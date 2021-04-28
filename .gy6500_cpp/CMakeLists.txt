cmake_minimum_required(VERSION 3.0.2)
project(gy6500)

find_package(catkin REQUIRED COMPONENTS roscpp)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(gy6500 src/main.cpp src/gy6500.cpp)

target_link_libraries(gy6500 ${catkin_LIBRARIES} pigpiod_if2 pigpio)
