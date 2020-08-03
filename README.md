# RPi4b_ROS_testing
Multiple simple tests with ROS on the Raspberry Pi 4B using GPIO ports. Ensure you have the pigpio library installed and that you run the Pigpio Daemon on Raspberry startup (can do it manually if you want) according to [this forum post](https://www.raspberrypi.org/forums/viewtopic.php?t=103752)

## talker
just testing the workings of ROS on the RPi by printing a single statement

## blinking_led
send an on/off signal to a GPIO port on the RPi, enabling or disabling an LED and publishing a boolean (std_msgs::Bool) indicating the status of the LED
- requires pigpio library
- requires root access in order to access the GPIO pins

## answer_led
listens to the blinking_led 'ledstatus' topic. Subsequentially enables a LED if the ledstatus is true and thus copies the 'blinking_led' LED. The answer_led package also counts how many times the answer_led has been on and publishes this integer count (std_msgs::Int8) to the 'blinkcnt' topic.
