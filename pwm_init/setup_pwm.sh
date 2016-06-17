#!/bin/bash
# PWM assignments script

pwm_directory14="/sys/devices/ocp.3/pwm_test_P9_14"
pwm_directory16="/sys/devices/ocp.3/pwm_test_P9_16"
pwm_directory21="/sys/devices/ocp.3/pwm_test_P9_21"
pwm_directory22="/sys/devices/ocp.3/pwm_test_P9_22"
pwm_directory42="/sys/devices/ocp.3/pwm_test_P9_42"
pwm_directory13="/sys/devices/ocp.3/pwm_test_P8_13"
pwm_directory19="/sys/devices/ocp.3/pwm_test_P8_19"

if [ -d "$pwm_directory14" ] && [ -d "$pwm_directory16" ] && [ -d "$pwm_directory19" ]
then
	echo "$pwm_directory14 found."
	echo "$pwm_directory16 found."
	echo "$pwm_directory19 found."
	 if [ -d "$pwm_directory21" ] && [ -d "$pwm_directory22" ]
	 then
	 	echo "$pwm_directory21 found."
	  echo "$pwm_directory22 found."
    fi
	    if [ -d "$pwm_directory42" ] && [ -d "$pwm_directory13" ]
	    then
	 	   echo "$pwm_directory42 found."
	     echo "$pwm_directory13 found."
      fi
    
else

echo "Initializing PWMs"
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

fi
