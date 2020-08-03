cmake_minimum_required(VERSION 3.0.2)
project(answer_led)

find_package(catkin REQUIRED COMPONENTS roscpp)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(answer_led src/answer_led.cpp)

target_link_libraries(answer_led ${catkin_LIBRARIES} pigpio)
