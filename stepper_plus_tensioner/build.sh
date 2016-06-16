#!/bin/sh
g++ --std=c++0x -o stepper_plus_tensioner PWM.cpp util.cpp GPIO.cpp stepper_plus_tensioner.cpp -pthread
