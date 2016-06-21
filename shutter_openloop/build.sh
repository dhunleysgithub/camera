#!/bin/sh
g++ --std=c++0x -o shutter_openloop PWM.cpp util.cpp GPIO.cpp shutter_openloop.cpp -pthread