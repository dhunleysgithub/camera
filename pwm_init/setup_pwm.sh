#!/bin/bash
# PWM assignments script

echo "Hello Dwight!"

cd /lib/firmware/
export SLOTS=/sys/devices/bone_capemgr.9/slots
echo bone_pwm_P9_14 > $SLOTS 
echo bone_pwm_P9_16 > $SLOTS
echo bone_pwm_P9_21 > $SLOTS
echo bone_pwm_P9_22 > $SLOTS
echo bone_pwm_P9_42 > $SLOTS
echo bone_pwm_P8_13 > $SLOTS
echo bone_pwm_P8_19 > $SLOTS
echo am33xx_pwm > $SLOTS
cat $SLOTS

ls /sys/devices/ocp.3/
