/*
 * stepper.cpp  Created on: 7 Feb 2016

 * Dwight Hunley
*/


#include<iostream>
#include"PWM.h"      //placed in the current directory for ease of use
#include<unistd.h> //for usleep

using namespace exploringBB;
using namespace std;

int main ( )
{


// Turn all PWMs off first
   PWM pwm1("pwm_test_P9_14.15");      
   pwm1.setPeriod(50000);                // Set the period in ns
   pwm1.setDutyCycle(0.0f);             // Set the duty cycle as a percentage
   pwm1.setPolarity(PWM::ACTIVE_HIGH);   // using active low PWM
   pwm1.run();                           // start the PWM output
   usleep(100000);
   pwm1.stop();                          // stop the PWM output
   usleep(100000);
   PWM pwm2("pwm_test_P9_16.16");      
   pwm2.setPeriod(50000);                // Set the period in ns
   pwm2.setDutyCycle(0.0f);             // Set the duty cycle as a percentage
   pwm2.setPolarity(PWM::ACTIVE_HIGH);   // using active low PWM
   pwm2.run();                           // start the PWM output
   usleep(100000);
   pwm2.stop();                          // stop the PWM output
   usleep(100000);
   PWM pwm3("pwm_test_P9_21.17");      
   pwm3.setPeriod(50000);                // Set the period in ns
   pwm3.setDutyCycle(0.0f);             // Set the duty cycle as a percentage
   pwm3.setPolarity(PWM::ACTIVE_HIGH);   // using active low PWM
   pwm3.run();                           // start the PWM output
   usleep(100000);
   pwm3.stop();                          // stop the PWM output
   usleep(100000);
   PWM pwm4("pwm_test_P9_22.18");      
   pwm4.setPeriod(50000);                // Set the period in ns
   pwm4.setDutyCycle(0.0f);             // Set the duty cycle as a percentage
   pwm4.setPolarity(PWM::ACTIVE_HIGH);   // using active low PWM
   pwm4.run();                           // start the PWM output
   usleep(100000);
   pwm4.stop();                          // stop the PWM output
   usleep(100000);
   PWM pwm5("pwm_test_P9_42.19");      
   pwm5.setPeriod(50000);                // Set the period in ns
   pwm5.setDutyCycle(0.0f);             // Set the duty cycle as a percentage
   pwm5.setPolarity(PWM::ACTIVE_HIGH);   // using active low PWM
   pwm5.run();                           // start the PWM output
   usleep(100000);
   pwm5.stop();                          // stop the PWM output
   usleep(100000);
   PWM pwm6("pwm_test_P8_13.20");      
   pwm6.setPeriod(50000);                // Set the period in ns
   pwm6.setDutyCycle(0.0f);             // Set the duty cycle as a percentage
   pwm6.setPolarity(PWM::ACTIVE_HIGH);   // using active low PWM
   pwm6.run();                           // start the PWM output
   usleep(100000);
   pwm6.stop();                          // stop the PWM output
   usleep(100000);
   PWM pwm7("pwm_test_P8_19.21");      
   pwm7.setPeriod(50000);                // Set the period in ns
   pwm7.setDutyCycle(0.0f);             // Set the duty cycle as a percentage
   pwm7.setPolarity(PWM::ACTIVE_HIGH);   // using active low PWM
   pwm7.run();                           // start the PWM output
   usleep(100000);
   pwm7.stop();                          // stop the PWM output
   usleep(100000);

   usleep(1000000);

} 