#!/bin/bash
# folder exists test script

pwm_directory14="/sys/devices/ocp.3/pwm_test_P9_14.15"
pwm_directory16="/sys/devices/ocp.3/pwm_test_P9_16.16"
pwm_directory21="/sys/devices/ocp.3/pwm_test_P9_21.17"
pwm_directory22="/sys/devices/ocp.3/pwm_test_P9_22.18"
pwm_directory42="/sys/devices/ocp.3/pwm_test_P9_42.19"
pwm_directory13="/sys/devices/ocp.3/pwm_test_P8_13.20"
pwm_directory19="/sys/devices/ocp.3/pwm_test_P8_19.21"

	echo "look for $pwm_directory14"
	echo "look for $pwm_directory16"
	echo "look for $pwm_directory21"
	echo "look for $pwm_directory22"
	echo "look for $pwm_directory42"
	echo "look for $pwm_directory13"
	echo "look for $pwm_directory19"

if [ -d "$pwm_directory14" ]
then
	echo "$pwm_directory14 found."
else
	echo "$pwm_directory14 NOT found."
fi

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

echo "Did not find all PWM directories"
echo "Initializing PWMs"
/root/camera/pwm_init/setup_pwm.sh
/root/camera/pwm_init/pwminit
echo "Initialized PWMs"

fi
