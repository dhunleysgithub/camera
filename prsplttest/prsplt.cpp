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

int main (int argc, char** argv)
{
   // Power on or off the 5V sensor power supply
 
   // If argc less than two, whoops
    if(argc < 2)
    {
        // Print out a usage example
        std::cerr << "Usage: " << argv[0] << " <Put pressure plate Down or Up >.  e.g. " << argv[0] << " 1=Down or 0=Up " << std::endl;

        // Exit
        return 1;
    }

   GPIO inGPIO(46);  // P8_16  
   inGPIO.setDirection(INPUT);

   GPIO inputGPIO(115);  // P9_27 
   inputGPIO.setDirection(INPUT);


// P9_22 is Pin Number 5
   PWM pwm_apos("pwm_test_P9_22.18");      // P9_22 MUST be loaded as a slot before use
   pwm_apos.setPeriod(50000);              // Set the period in ns
   pwm_apos.setDutyCycle(0.0f);            // Set the duty cycle as a percentage
   pwm_apos.setPolarity(PWM::ACTIVE_HIGH); // using active low PWM
   pwm_apos.run();                         // start the PWM output
 

   usleep(10000);
   pwm_apos.setDutyCycle(50.0f);        
   usleep(500000);
   pwm_apos.setDutyCycle(0.0f);        
   usleep(500000);




   int slotsnsr_state = 0;
   int slotsnsr_target=2;
   int icntr = 0;
   int ilast_on = 0;
   int istop = 0;

   slotsnsr_state=inGPIO.getValue();
   std::cout << " slot sensor state is " << slotsnsr_state << std::endl;
    
    while(icntr<6)
    {
     //usleep(1000000);
     std::cout << " slot sensor target is " << slotsnsr_target << std::endl;
     pwm_apos.setDutyCycle(50.0f); 
     
     int icntr2 = 0;
     while (slotsnsr_state != slotsnsr_target && icntr2 < 100)
     {

       slotsnsr_state=inGPIO.getValue();
       //std::cout << ilast_on << ", " << slotsnsr_state << std::endl;
       //std::cout << "ilast_on, sensor state" << ilast_on << ", " << slotsnsr_state << std::endl;
       //std::cout << " ilast_on is " << ilast_on << std::endl;

      if (slotsnsr_state==1)
       {
       std::cout << ilast_on << ", " << slotsnsr_state << std::endl;

        istop=0;
        if ( atoi(argv[1]) == 0 ){
           if (ilast_on < 8)
           {
           while (inputGPIO.getValue() == 0 )
           {
           usleep(50000);
           }
          std::cout << " Pressure plate is UP !! **  " << std::endl;
          istop=1;
           }
        }
       if ( atoi(argv[1]) == 1 ){
           if (ilast_on > 8)
           {
          std::cout << " Pressure plate is DOWN !! **  " << std::endl;
            istop=1;

           }
        }
        //if (ilast_on < 5)
        //if (ilast_on >10 )
        if (istop > 0)
        {
          std::cout << " at the mark sleeping 5 sec " << std::endl;
          pwm_apos.setDutyCycle(0.0f);        
          usleep(500000);
          // Exit
          return 1;
          //pwm_apos.setDutyCycle(50.0f);        
         }

        ilast_on=0;
        usleep(500000);
       }

       if (slotsnsr_state==10)
       {
         if (ilast_on < 6)
         {
          std::cout << " at the mark sleeping 5 sec " << std::endl;
          pwm_apos.setDutyCycle(0.0f);        
          usleep(5000000);
          pwm_apos.setDutyCycle(90.0f);        
          usleep(1000000);
         }
          
         ilast_on=0;
       }

       //if (slotsnsr_state==0)
        //{
         ilast_on=ilast_on+1;
        //}
     icntr2++;
     usleep(100000);
     }


     pwm_apos.setDutyCycle(0.0f);
//     std::cout << " Hit Control C to end program - Pressure plate inoperable *** " << std::endl; 
     std::cout << " Pressure plate inoperable - Exiting Program *** " << std::endl; 
//     usleep(50000000);
     usleep(500000);
     return 1;


       if (slotsnsr_state==1) {
        slotsnsr_target=0;
       }
       if (slotsnsr_state==0) {
        slotsnsr_target=1;
       }
       usleep(1000000);
   icntr=icntr+1;
      std::cout << " icntr is " << icntr << std::endl;
    }

   pwm_apos.setDutyCycle(0.0f);        

   inGPIO.streamClose(); 
   usleep(1000000); //micro-second sleep 0.5 seconds
   pwm_apos.stop();                    // stop the PWM output
   usleep(10000);
 
   return 1;


} 
