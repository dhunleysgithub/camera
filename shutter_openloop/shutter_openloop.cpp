/*
 * stepper.cpp  Created on: 7 Feb 2016
 * Dwight Hunley
*/


#include<iostream>
#include"PWM.h"      //placed in the current directory for ease of use
#include"GPIO.h"
#include<unistd.h> //for usleep
#include <stdlib.h>         // for the system calls
#include <fstream>
#include <sstream>

using namespace exploringBB;
using namespace std;

#define exposureCount_PATH "/root/expcounts.txt"

int main (int argc, char** argv)
{


/* placeholder for future arguments
 
   // If argc less than two, whoops
    if(argc < 2)
    {
        // Print out a usage example
        std::cerr << "Usage: " << argv[0] << " < placeholder >.  e.g. " << argv[0] << " 1= tbd or 0= tbd " << std::endl;
        // Exit
        return 1;
    }
*/

string exposureCount1; 
int number;
stringstream ss;
ss << exposureCount_PATH;
fstream fs;
fs.open(ss.str().c_str(), fstream::in);
fs >> number;
cout << "The starting exposure count is " << number << endl;
number+=1;  // add one exposure count each time this program is called
ostringstream temp;  //temp as in temporary
temp<<number;
exposureCount1=temp.str();      //str is temp as string
//exposureCount=ss.str();      //str is temp as string
cout << "The ending exposure count is " << number << endl;
fs << exposureCount1;
fs.close();

// P9_21 is Pin Number 6
   PWM pwm_apos("pwm_test_P9_21.17");      // P9_21 MUST be loaded as a slot before use
   pwm_apos.setPeriod(50000);              // Set the period in ns
   pwm_apos.setDutyCycle(0.0f);            // Set the duty cycle as a percentage
   pwm_apos.setPolarity(PWM::ACTIVE_HIGH); // using active low PWM
   pwm_apos.run();                         // start the PWM output
 
// P9_42 is Pin Number 8
   PWM pwm_aneg("pwm_test_P9_42.19");      // P9_42 MUST be loaded as a slot before use
   pwm_aneg.setPeriod(50000);              // Set the period in ns
   pwm_aneg.setDutyCycle(0.0f);            // Set the duty cycle as a percentage
   pwm_aneg.setPolarity(PWM::ACTIVE_HIGH); // using active low PWM
   pwm_aneg.run();                         // start the PWM output

/*
   usleep(1000000);
   pwm_apos.setDutyCycle(40.0f);        
   usleep(2000000);
   pwm_apos.setDutyCycle(0.0f);        
   usleep(500000);
*/
   usleep(100000);
   pwm_apos.setDutyCycle(90.0f);        
   usleep(140000);
   pwm_apos.setDutyCycle(0.0f);        
   usleep(500000);


   pwm_apos.setDutyCycle(90.0f);        
   usleep(120000);
   pwm_apos.setDutyCycle(0.0f);        
   usleep(100000);

   pwm_apos.setDutyCycle(0.0f);        
   pwm_apos.stop();                    // stop the PWM output
   pwm_aneg.setDutyCycle(0.0f);        
   pwm_aneg.stop();                    // stop the PWM output


   usleep(10000);
 
   return 1;


} 
