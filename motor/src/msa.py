#!/usr/bin/python
import RPi.GPIO as GPIO
import time

def measure():
    # init ros 
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(7,GPIO.OUT)
    
    p = GPIO.PWM(7,50)

    p.start(0)
    print("starting 0")
    time.sleep(3)

    p.ChangeDutyCycle(3)
    print("start")

    time.sleep(5)

    while True:
        i = 8 
        while i<20:
            print(i)
            p.ChangeDutyCycle(i)
            time.sleep(0.05)
            i+=.1

        while i>8:
            print(i)
            p.ChangeDutyCycle(i)
            time.sleep(0.05)
            i-=.1

if __name__ == '__main__':
    measure()
