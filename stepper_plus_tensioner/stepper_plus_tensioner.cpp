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
std::cout << " At 0 " << std::endl;

   GPIO inGPIO(26);  // P8_14 
   inGPIO.setDirection(INPUT);
   GPIO inputGPIO(115);  // P9_27 
   GPIO outputGPIO(27);  // P8_17 
   inputGPIO.setDirection(INPUT);
   outputGPIO.setDirection(OUTPUT);
   outputGPIO.setValue(LOW);


//    pwmstring="pwm_test_P8_13.20";
//    pwmstring="pwm_test_P9_14.15";      
//    pwmstring="pwm_test_P9_16.16";      
//    pwmstring="pwm_test_P8_19.21";      


std::cout << " At 1 " << std::endl;



 // Stepper motor driver -  4 PWMs 
 
   PWM pwm_apos("pwm_test_P8_13.20");       // P9_42 MUST be loaded as a slot before use
   std::cout << " At 1b " << std::endl;
   pwm_apos.setPeriod(50000);              // Set the period in ns
   std::cout << " At 1c " << std::endl;
   pwm_apos.setDutyCycle(0.0f);             // Set the duty cycle as a percentage
   pwm_apos.setPolarity(PWM::ACTIVE_HIGH);  // using active low PWM
   pwm_apos.run();                          // start the PWM output
   usleep(10000);

   PWM pwm_aneg("pwm_test_P9_14.15");       // P8_13 MUST be loaded as a slot before use
   pwm_aneg.setPeriod(500000);              // Set the period in ns
   pwm_aneg.setDutyCycle(0.0f);            // Set the duty cycle as a percentage
   pwm_aneg.setPolarity(PWM::ACTIVE_HIGH);  // using active low PWM
   pwm_aneg.run();                          // start the PWM output
   usleep(10000);

   PWM pwm_bpos("pwm_test_P9_16.16");       // P9_42 MUST be loaded as a slot before use
   pwm_bpos.setDutyCycle(0.0f);             // Set the duty cycle as a percentage
   pwm_bpos.setPolarity(PWM::ACTIVE_HIGH);  // using active low PWM
   pwm_bpos.run();                          // start the PWM output
   usleep(10000);

   PWM pwm_bneg("pwm_test_P8_19.21");       // P8_13 MUST be loaded as a slot before use
   pwm_bneg.setDutyCycle(0.0f);            // Set the duty cycle as a percentage
   pwm_bneg.setPolarity(PWM::ACTIVE_HIGH);  // using active low PWM
   pwm_bneg.run();                          // start the PWM output
   usleep(10000); 
 
std::cout << " At 2 " << std::endl;
    
 // Advance film - Stepper Motor
   
// fast  int dtsegment = 2000;
  int dtsegment = 2000;
  int slotsnsr_state = 0;
  int stepper_dt = 2;
  int cntr = 0;
  
std::cout << " Presure plate is check GPIO state is " << inputGPIO.getValue() << std::endl;

if (inputGPIO.getValue() == 1)
{
  std::cout << " Presure plate is up - Advance file ! " << std::endl;
 }
if (inputGPIO.getValue() == 10)
{
  std::cout << " Presure plate is down ** Can't advance film ** " << std::endl;

}
if (inputGPIO.getValue() == 1)
{

  while( cntr < 120 ) {

// Clockwise
std::cout << " At 3 " << std::endl;

 // Segment 1
   pwm_apos.setDutyCycle(0.0f);        
   pwm_aneg.setDutyCycle(90.0f);       
   pwm_bpos.setDutyCycle(0.0f);       
   pwm_bneg.setDutyCycle(90.0f);      
   usleep(dtsegment);
  
 // Segment 2
   pwm_apos.setDutyCycle(0.0f);        
   pwm_aneg.setDutyCycle(90.0f);       
   pwm_bpos.setDutyCycle(90.0f);       
   pwm_bneg.setDutyCycle(0.0f);      
   usleep(dtsegment);
 
 // Segment 3
   pwm_apos.setDutyCycle(90.0f);        
   pwm_aneg.setDutyCycle(0.0f);       
   pwm_bpos.setDutyCycle(90.0f);       
   pwm_bneg.setDutyCycle(0.0f);      
   usleep(dtsegment);
   
 // Segment 4
   pwm_apos.setDutyCycle(90.0f);        
   pwm_aneg.setDutyCycle(0.0f);       
   pwm_bpos.setDutyCycle(0.0f);       
   pwm_bneg.setDutyCycle(90.0f);       
   usleep(dtsegment);

//   slotsnsr_state=inGPIO.getValue();
//   std::cout << " slot sensor state is " << slotsnsr_state << std::endl;
 
   outputGPIO.setValue(HIGH);
   usleep(2000 ); //micro-second sleep 0.5 seconds
   outputGPIO.setValue(LOW);
   usleep(2000);


    cntr+= 1;  
}
  
}
    outputGPIO.setValue(LOW);
   
     inputGPIO.streamClose(); 
     outputGPIO.streamClose(); 
     usleep(100000); //micro-second sleep 0.1 seconds


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
