/*
 * stepper.cpp  Created on: 7 Feb 2016

 * Dwight Hunley
*/


#include<iostream>
#include"PWM.h"      //placed in the current directory for ease of use
#include"GPIO.h"
#include<unistd.h> //for usleep

using namespace exploringBB;
using namespace std;

int main(){

   GPIO outGPIO(46);  // P8_16  
   outGPIO.setDirection(INPUT);




 // Stepper motor driver -  4 PWMs 
 
   PWM pwm_apos("pwm_test_P9_14.15");       // P9_42 MUST be loaded as a slot before use
   pwm_apos.setPeriod(50000);              // Set the period in ns
   pwm_apos.setDutyCycle(0.0f);             // Set the duty cycle as a percentage
   pwm_apos.setPolarity(PWM::ACTIVE_HIGH);  // using active low PWM
   pwm_apos.run();                          // start the PWM output
   usleep(10000);

   PWM pwm_aneg("pwm_test_P9_16.16");       // P8_13 MUST be loaded as a slot before use
   pwm_aneg.setPeriod(500000);              // Set the period in ns
   pwm_aneg.setDutyCycle(0.0f);            // Set the duty cycle as a percentage
   pwm_aneg.setPolarity(PWM::ACTIVE_HIGH);  // using active low PWM
   pwm_aneg.run();                          // start the PWM output
   usleep(10000);


 
   PWM pwm_bpos("pwm_test_P9_21.17");       // P9_42 MUST be loaded as a slot before use
   pwm_bpos.setDutyCycle(0.0f);             // Set the duty cycle as a percentage
   pwm_bpos.setPolarity(PWM::ACTIVE_HIGH);  // using active low PWM
   pwm_bpos.run();                          // start the PWM output
   usleep(10000);

   PWM pwm_bneg("pwm_test_P9_22.18");       // P8_13 MUST be loaded as a slot before use
   pwm_bneg.setDutyCycle(0.0f);            // Set the duty cycle as a percentage
   pwm_bneg.setPolarity(PWM::ACTIVE_HIGH);  // using active low PWM
   pwm_bneg.run();                          // start the PWM output
   usleep(10000); 
 
    
 // Advance film - Stepper Motor
   
  int dtsegment = 2000;

  int stepper_dt = 2;
  int cntr = 0;
  while( cntr < 120 ) {

 // Segment 1
   pwm_apos.setDutyCycle(90.0f);        
   pwm_aneg.setDutyCycle(0.0f);       
   pwm_bpos.setDutyCycle(0.0f);       
   pwm_bneg.setDutyCycle(90.0f);      
   usleep(dtsegment);
  
 // Segment 2
   pwm_apos.setDutyCycle(90.0f);        
   pwm_aneg.setDutyCycle(0.0f);       
   pwm_bpos.setDutyCycle(90.0f);       
   pwm_bneg.setDutyCycle(0.0f);      
   usleep(dtsegment);
 
 // Segment 3
   pwm_apos.setDutyCycle(0.0f);        
   pwm_aneg.setDutyCycle(90.0f);       
   pwm_bpos.setDutyCycle(90.0f);       
   pwm_bneg.setDutyCycle(0.0f);      
   usleep(dtsegment);
   
 // Segment 4
   pwm_apos.setDutyCycle(0.0f);        
   pwm_aneg.setDutyCycle(90.0f);       
   pwm_bpos.setDutyCycle(0.0f);       
   pwm_bneg.setDutyCycle(90.0f);      
   usleep(dtsegment);
    cntr+= 1;
   
}
  
 
   pwm_apos.setDutyCycle(0.0f);            // Set the duty cycle as a percentage
   usleep(1000);
   pwm_aneg.setDutyCycle(0.0f);            // Set the duty cycle as a percentage
   usleep(1000);
   pwm_bpos.setDutyCycle(0.0f);            // Set the duty cycle as a percentage
   usleep(1000);
   pwm_bneg.setDutyCycle(0.0f);            // Set the duty cycle as a percentage
   usleep(10000);

   usleep(100000);

   pwm_apos.stop();                    // stop the PWM output
   usleep(10000);
   pwm_aneg.stop();                    // stop the PWM output
   usleep(10000);
   pwm_bpos.stop();                    // stop the PWM output
   usleep(10000);
   pwm_bneg.stop();                    // stop the PWM output

} 