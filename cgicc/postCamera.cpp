#include <iostream>         // for the input/output
#include <stdlib.h>         // for the system, getenv calls
#include <sys/sysinfo.h>    // for the system uptime call
#include <cgicc/Cgicc.h>    // the cgicc headers
#include <cgicc/CgiDefs.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <fstream>
#include <sstream>
#include <unistd.h> 
#include <sys/types.h> 
#include <pthread.h>

using namespace std;
using namespace cgicc;

#define exposureCount_PATH "/root/expcounts.txt"
//FUNCTION  DECLARATIONS: 
 pid_t popen2(const char *shell_cmd, int *p_fd_in, int *p_fd_out); 
 int str2int(const string &str);

// This is the thread function that will execute when the thread is created
//  it passes and receives data by void pointers
void *threadFunction(void *value){
   string runcommandstring, exposureCount;
   const char* mcmd_char;
   int fd_out3, fd_in3 =0; 
   //pid_t  pid3 = 0;
   int *x = (int *)value;    //cast the data passed to an int pointer
   int *number = (int *)value;    //cast the data passed to an int pointer
   ///ostringstream temp;  //temp as in temporary
   ///temp << *number;
   while(*x<5){              //while the value of x is less than 5
      //usleep(1000);         //sleep for 1ms - encourage main thread
      sleep(2);         //sleep for 1ms - encourage main thread
      (*x)++;               //increment the value of x by 1
	}
   ///exposureCount=temp.str();      //str is temp as string
   //  runcommandstring = "/usr/lib/cgi-bin/run.sh " + exposureCount + " &";
   ///runcommandstring = "/root/camera/shutter_openloop/shutter_openloop " + exposureCount + " &";
   ///mcmd_char = runcommandstring.c_str();
   ///int i;
   //i = system(mcmd_char);
   cout << " Run Command String : " << runcommandstring << endl;  
   return x;                 //return the pointer x ( as a void*)
}

int main()
{

string logoutput; 
int number;
stringstream ss;
ss << exposureCount_PATH;
fstream fs;
int i,j, ierr, iexposuresRequested;
ierr=0;
iexposuresRequested=0;
   
Cgicc form;                                     // the CGI form object
   
string pwr_cmd, command, exposureCount, exposuresRequested, exposuresReset, expsReset;

string mcmd_str, runcommandstring;
runcommandstring = " ";
const char* mcmd_char;
bool isReset = form.queryCheckbox("expsReset");   // get the state of the status checkbox
   
   form_iterator it = form.getElement("pwr_cmd");   // get the period text value
   if (it == form.getElements().end() || it->getValue()==""){
      pwr_cmd = "off";                         // if it is invalid use 100
   }
   else { pwr_cmd = it->getValue(); }          // otherwise use submitted value
   it = form.getElement("command");                // get the radio command chosen
   if (it == form.getElements().end() || it->getValue()==""){
      command = "single";                             // if it is invalid use "off"
   }
   else { command = it->getValue(); }              // otherwise use submitted value

   it = form.getElement("exposures");   // get the existing number of exposures executed value
   if (it == form.getElements().end() || it->getValue()==""){
      exposureCount = "0";
   }

   it = form.getElement("multexpreq");   // get the exisitng number of exposures executed value
   if (it == form.getElements().end() || it->getValue()==""){
      exposuresRequested = "0"; // if it is invalid use 100
   }
   else { exposuresRequested = it->getValue(); }          // otherwise use submitted value

   it = form.getElement("expsReset");   // get the exisitng number of exposures executed value
   if (it == form.getElements().end() || it->getValue()==""){
      expsReset = "NO"; // if it is invalid use 100
   }
   else { expsReset = it->getValue(); }          // otherwise use submitted value
   
   char *value = getenv("REMOTE_ADDR");	           // The remote address CGI env. variable

// Generate the form but use states that are set in the form that was submitted
cout << HTTPHTMLHeader() << endl;               // Generate the HTML form using cgicc
//cout << html() << head() << title("EBB C++ Post Camera Baseline") << head() << endl;

cout << "<head>" << endl;
cout << "<title>EBB C++ Post Camera Baseline</title>" << endl;
cout << "<meta http-equiv=\"refresh\" content=\"5\">" << endl;
cout << "</head>" << endl;

cout << body() << h1("BeagleBone Black Camera Controller") << endl;;
cout << "<form action=\"/cgi-bin/postCamera.cgi\" method=\"POST\">\n";
cout <<  "<style>" << endl;
cout <<  "#header {" << endl;
cout <<  "    background-color:blue;" << endl;
cout <<  "    color:white;" << endl;
cout <<  "    text-align:center;" << endl;
cout <<  "    padding:5px;" << endl;
cout <<  "}" << endl;
cout <<  "#nav {" << endl;
cout <<  "    line-height:30px;" << endl;
cout <<  "    background-color:#99ccff;" << endl;
cout <<  "    height:400px;" << endl;
cout <<  "    width:300px;" << endl;
cout <<  "    float:left;" << endl;
cout <<  "    padding:2px;" << endl;
cout <<  "}" << endl;
cout <<  "#nav2 {" << endl;
cout <<  "    line-height:30px;" << endl;
cout <<  "    background-color:#ffffcc;" << endl;
cout <<  "    height:400px;" << endl;
cout <<  "    width:300px;" << endl;
cout <<  "    float:left;" << endl;
cout <<  "    padding:2px;" << endl;
cout <<  "}" << endl;
cout <<  "#nav3 {" << endl;
cout <<  "    line-height:30px;" << endl;
cout <<  "    background-color:#cc99ff;" << endl;
cout <<  "    height:400px;" << endl;
cout <<  "    width:300px;" << endl;
cout <<  "    float:left;" << endl;
cout <<  "    padding:2px;" << endl;
cout <<  "}" << endl;
cout <<  "#section {" << endl;
cout <<  "    width:350px;" << endl;
cout <<  "    float:left;" << endl;
cout <<  "    padding:10px;" << endl;
cout <<  "}" << endl;
cout <<  "#footer {" << endl;
cout <<  "    background-color:black;" << endl;
cout <<  "    color:white;" << endl;
cout <<  "    clear:both;" << endl;
cout <<  "    text-align:center;" << endl;
cout <<  "    padding:5px;" << endl;
cout <<  "}" << endl;
cout <<  "</style>" << endl;
cout <<  "</head>" << endl;

cout <<  "<body>" << endl;
cout <<  "<div id=\"header\">" << endl;
cout <<  "<h1>Photoengineering Inc.</h1>" << endl;
cout <<  "</div>" << endl;

cout <<  "<div id=\"nav\">" << endl;
cout <<  "<h2>Command Selection </h2>" << endl;
cout << "<input type=\"radio\" name=\"command\" value=\"single\""
      << ( command=="single" ? "checked":"") << "/> Single <br>";	// is the command="on"?
cout << "<input type=\"radio\" name=\"command\" value=\"multiple\""
       << ( command=="multiple" ? "checked":"") << "/> Multiple <br>";
cout << "<input type=\"radio\" name=\"command\" value=\"load\""
        << ( command=="load" ? "checked":"") << "/> Load <br>";
cout << "<input type=\"radio\" name=\"command\" value=\"unload\""
        << ( command=="unload" ? "checked":"") << "/> Unload <br>";
cout << "<input type=\"radio\" name=\"command\" value=\"singleadv\""
        << ( command=="singleadv" ? "checked":"") << "/> Single Adv. <br>";
cout << "<input type=\"radio\" name=\"command\" value=\"multipleadv\""
        << ( command=="multipleadv" ? "checked":"") << "/> Multiple Adv. <br>";
cout << "<input type=\"radio\" name=\"command\" value=\"expreset\""
        << ( command=="expreset" ? "checked":"") << "/> Reset Exposure Counter <br>";
cout << "<input type=\"submit\" value=\"Process Selections\" />";
cout << "</div>";

// Reset Exposure Count Requested

  if ( command=="expreset"){
   //  cout << "<div> Resetting the exposure count to 0  "  << "</div>";
   ofstream myfile2 (ss.str().c_str());
   if (myfile2.is_open())
    {
      myfile2 << 0;
      myfile2.close();
      logoutput = "Reset the exposure count to 0";
   }
   else {
    cout << "<div> *** Unable to reset exposure count to 0  "  << "</div>";
    }
          }

// Single Exposure Requested

   if (command=="single")
    {
     //   i = system("nice -20 /root/camera/prsplttest/prsplt 0");
     //   i = system("nice -20 /root/camera/stepper_plus_tensioner/stepper_plus_tensioner");
     //   i = system("nice -20 /root/camera/prsplttest/prsplt 1");
        i = system("nice -20 /root/camera/shutter_openloop/shutter_openloop 1");
        logoutput = "Ran a single exposure ";

    }

// Multiple Exposures Requested
   int fd_out3; 
   int fd_in3 =0; 
   pid_t  pid3 = 0;
   int y=0;
   int x=0;
   pthread_t thread;         //this is our handle to the pthread

    if (command=="multiple")
     {
      iexposuresRequested = str2int(exposuresRequested);
      runcommandstring = "/usr/lib/cgi-bin/run.sh " + exposuresRequested + " &";
       //mcmd_str = "/root/camera/run_shutter_ol.sh " + exposuresRequested;
       mcmd_char = runcommandstring.c_str();
       logoutput = "Ran " + exposuresRequested + " exposures ";
    // create the thread, pass the reference, address of the function and data
    // pthread_create() returns 0 on the successful creation of a thread
    //if(pthread_create(&thread, NULL, &threadFunction, &iexposuresRequested)!=0){
    if(pthread_create(&thread, NULL, &threadFunction, &x)!=0){
    	cout << "Failed to create the thread" << endl;
    	return 1;
    }
     // at this point the thread was created successfully
    while(y<5){               // loop and increment y, displaying values
    	cout << "The value of x=" << x << " and y=" << y++ << endl;
    	sleep(1);         // encourage the pthread to run
    }
// pthread_join will block execution until thread completes
    void* result;             // OPTIONAL: receive data back from pthread
    //pthread_join(thread, &result);   // allow the pthread to complete
    //int *z = (int *) result;         // cast from void* to int* to get z
    //cout << "Final: x=" << x << ", y=" << y << " and z=" << *z << endl;
   }

// Read exposure counter value
fs.open(ss.str().c_str(), fstream::in);
fs >> number;
ostringstream temp;  //temp as in temporary
temp<<number;
exposureCount=temp.str();      //str is temp as string
fs.close();

// 5V Power Control Panel

cout <<  "<div id=\"nav2\">" << endl;
cout <<  "<h2>Board 5V Power </h2>" << endl;
cout << "<input type=\"radio\" name=\"pwr_cmd\" value=\"on\""
      << ( pwr_cmd=="on" ? "checked":"") << "/> On ";	// is the pwr_cmd="on"?
cout << "<input type=\"radio\" name=\"pwr_cmd\" value=\"off\""
       << ( pwr_cmd=="off" ? "checked":"") << "/> Off <br><br>";
cout <<  "<h2>Format </h2>" << endl;
cout <<  "<select>" << endl;
cout <<  "  <option value=\"Full\">Full</option>" << endl;
cout <<  "  <option value=\"Half\">Half</option>" << endl;
cout <<  "  <option value=\"tbd\">Quarter</option>" << endl;
cout <<  "</select>" << endl;
cout << "<button type=\"button\" onclick=\"myFunction()\">Click me!</button>" << endl;

cout << "<script>" << endl;
cout << "function myFunction() { " << endl;
cout << "    document.write(\"Hello World\") " << endl;
//cout << "    document.getElementById(\"exposures\").value = \"Fifth Avenue, New York City\"" << endl;
cout << "}" << endl;
cout << "</script>";

cout << "<A Href=\"/cgi-bin/tcount.cgi\">See the counter!</A>" << endl;
cout <<  "</div>" << endl;



cout <<  "<div id=\"nav3\">" << endl;
cout <<  "<h2>Control </h2>" << endl;
cout <<  "<label class=\"description\" for=\"element_1\">Exposure Time : </label>" << endl;
cout <<  "<input id=\"element_1\" name=\"element_1\" class=\"element text small\" type=\"text\" size = \"6\" maxlength=\"25\" value=\"\"/><br>" << endl;
cout <<  "<label class=\"description\" for=\"element_1\">Multiple Exp. : </label>" << endl;
cout <<  "<input id=\"element_1\" name=\"multexpreq\" class=\"element text small\" type=\"text\" size = \"6\"  maxlength=\"25\" value=\""<< exposuresRequested << "\"/><br>" << endl;
cout <<  "<label class=\"description\" for=\"element_1\">Multiple Advance : </label>" << endl;
cout <<  "<input id=\"element_1\" name=\"element_1\" class=\"element text small\" type=\"text\" size = \"6\"  maxlength=\"5\" value=\"\"/><br>" << endl;
cout <<  "<label class=\"description\" for=\"element_1\">Exposure Count : </label>" << endl;
cout <<  "<input id=\"element_1\" name=\"exposures\" class=\"element text small\" type=\"text\" size = \"6\"  maxlength=\"125\" value=\""<< exposureCount << "\"/><br>" << endl;
cout <<  "<label class=\"description\" for=\"element_1\">Frame Count : </label>" << endl;
cout <<  "<input id=\"element_1\" name=\"element_1\" class=\"element text small\" type=\"text\" size = \"6\"  maxlength=\"125\" value=\"\"/><br>" << endl;
cout <<  "<label class=\"description\" for=\"element_1\">Film Used : </label>" << endl;
cout <<  "<input id=\"element_1\" name=\"element_1\" class=\"element text small\" type=\"text\" size = \"6\"  maxlength=\"125\" value=\"\"/><br>" << endl;

//it = form.getElement("command");                // get the radio command chosen
//it->setData()="load";
 

cout <<  "</div></form>" << endl;



cout <<  "<div id=\"footer\">" << endl;
cout <<  "Serial Number: XYZ Phone: 480-406-9804 Email: dwight_hunley@hotmail.com" << endl;
cout <<  "</div>" << endl;

 
   // Process the 5V Power Control form data
   if (pwr_cmd=="on")
    {
     i = system("echo 65 > /sys/class/gpio/export");
     i = system("echo \"out\" > /sys/class/gpio/gpio65/direction"); // turn the Power on?
     i = system("echo 1 > /sys/class/gpio/gpio65/value"); // turn the Power on?
     cout << "<div> pwr_cmd = on! </div>";
    }
   else if (pwr_cmd=="off")
   {
     i = system("echo 0 > /sys/class/gpio/gpio65/value"); // off?
     i = system("echo 65 > /sys/class/gpio/unexport"); // turn the Power on?
     cout << "<div> pwr_cmd = off! </div>";
    }
    else cout << "<div> Invalid command! </div>";        // not possible at the moment
  
 
          
         
   cout << "<div> " << logoutput   << "</div>";

   cout << "<div> The CGI REMOTE_ADDR environment variable is " << value << "</div>";

         if(pid3 <= 0) 
         { 
           cout << "<div> Unable to exec prog Test Case 3 </div>"; 
          } 

sleep(5);

while(pwr_cmd=="on")
{
   if (command=="load" && pwr_cmd=="on" )
    {
    	
        i = system("/usr/lib/cgi-bin/tcount.cgi");
        it = form.getElement("pwr_cmd");   // get the period text value
        pwr_cmd = it->getValue();          // otherwise use submitted value
        sleep(1);
    }
}

//form.getElement("command")
//document.getElementById("myTextarea").value = "Fifth Avenue, New York City";

//sleep(10);

/*

cout << body() << html();

cout <<  "DEBUG 1a3" << endl;  



sleep(10);


// Generate the form but use states that are set in the form that was submitted
cout << HTTPHTMLHeader() << endl;               // Generate the HTML form using cgicc
cout << html() << head() << title("EBB C++ Post Camera Baseline") << head() << endl;
cout << body() << h1("BeagleBone Black Camera Controller") << endl;;
cout << "<form action=\"/cgi-bin/postCamera.cgi\" method=\"POST\">\n";
cout <<  "<style>" << endl;
cout <<  "#header {" << endl;
cout <<  "    background-color:blue;" << endl;
cout <<  "    color:white;" << endl;
cout <<  "    text-align:center;" << endl;
cout <<  "    padding:5px;" << endl;
cout <<  "}" << endl;
cout <<  "#nav {" << endl;
cout <<  "    line-height:30px;" << endl;
cout <<  "    background-color:#99ccff;" << endl;
cout <<  "    height:400px;" << endl;
cout <<  "    width:300px;" << endl;
cout <<  "    float:left;" << endl;
cout <<  "    padding:2px;" << endl;
cout <<  "}" << endl;
cout <<  "#nav2 {" << endl;
cout <<  "    line-height:30px;" << endl;
cout <<  "    background-color:#ffffcc;" << endl;
cout <<  "    height:400px;" << endl;
cout <<  "    width:300px;" << endl;
cout <<  "    float:left;" << endl;
cout <<  "    padding:2px;" << endl;
cout <<  "}" << endl;
cout <<  "#nav3 {" << endl;
cout <<  "    line-height:30px;" << endl;
cout <<  "    background-color:#cc99ff;" << endl;
cout <<  "    height:400px;" << endl;
cout <<  "    width:300px;" << endl;
cout <<  "    float:left;" << endl;
cout <<  "    padding:2px;" << endl;
cout <<  "}" << endl;
cout <<  "#section {" << endl;
cout <<  "    width:350px;" << endl;
cout <<  "    float:left;" << endl;
cout <<  "    padding:10px;" << endl;
cout <<  "}" << endl;
cout <<  "#footer {" << endl;
cout <<  "    background-color:black;" << endl;
cout <<  "    color:white;" << endl;
cout <<  "    clear:both;" << endl;
cout <<  "    text-align:center;" << endl;
cout <<  "    padding:5px;" << endl;
cout <<  "}" << endl;
cout <<  "</style>" << endl;
cout <<  "</head>" << endl;

cout <<  "<body>" << endl;
cout <<  "<div id=\"header\">" << endl;
cout <<  "<h1>Photoengineering Inc.</h1>" << endl;
cout <<  "</div>" << endl;

cout <<  "<div id=\"nav\">" << endl;
cout <<  "<h2>Command Selection </h2>" << endl;
cout << "<input type=\"radio\" name=\"command\" value=\"single\""
      << ( command=="single" ? "checked":"") << "/> Single <br>";	// is the command="on"?
cout << "<input type=\"radio\" name=\"command\" value=\"multiple\""
       << ( command=="multiple" ? "checked":"") << "/> Multiple <br>";
cout << "<input type=\"radio\" name=\"command\" value=\"load\""
        << ( command=="load" ? "checked":"") << "/> Load <br>";
cout << "<input type=\"radio\" name=\"command\" value=\"unload\""
        << ( command=="unload" ? "checked":"") << "/> Unload <br>";
cout << "<input type=\"radio\" name=\"command\" value=\"singleadv\""
        << ( command=="singleadv" ? "checked":"") << "/> Single Adv. <br>";
cout << "<input type=\"radio\" name=\"command\" value=\"multipleadv\""
        << ( command=="multipleadv" ? "checked":"") << "/> Multiple Adv. <br>";
cout << "<input type=\"radio\" name=\"command\" value=\"expreset\""
        << ( command=="expreset" ? "checked":"") << "/> Reset Exposure Counter <br>";
cout << "<input type=\"submit\" value=\"Process Selections\" />";
cout << "</div>";


// Read exposure counter value
fs.open(ss.str().c_str(), fstream::in);
fs >> number;
//ostringstream temp;  //temp as in temporary
temp<<number;
exposureCount=temp.str();      //str is temp as string
fs.close();

// 5V Power Control Panel

cout <<  "<div id=\"nav2\">" << endl;
cout <<  "<h2>Board 5V Power </h2>" << endl;
cout << "<input type=\"radio\" name=\"pwr_cmd\" value=\"on\""
      << ( pwr_cmd=="on" ? "checked":"") << "/> On ";	// is the pwr_cmd="on"?
cout << "<input type=\"radio\" name=\"pwr_cmd\" value=\"off\""
       << ( pwr_cmd=="off" ? "checked":"") << "/> Off <br><br>";
cout <<  "<h2>Format </h2>" << endl;
cout <<  "<select>" << endl;
cout <<  "  <option value=\"Full\">Full</option>" << endl;
cout <<  "  <option value=\"Half\">Half</option>" << endl;
cout <<  "  <option value=\"tbd\">Quarter</option>" << endl;
cout <<  "</select>" << endl;
cout <<  "</div>" << endl;


cout <<  "<div id=\"nav3\">" << endl;
cout <<  "<h2>Control </h2>" << endl;
cout <<  "<label class=\"description\" for=\"element_1\">Exposure Time : </label>" << endl;
cout <<  "<input id=\"element_1\" name=\"element_1\" class=\"element text small\" type=\"text\" size = \"6\" maxlength=\"25\" value=\"\"/><br>" << endl;
cout <<  "<label class=\"description\" for=\"element_1\">Multiple Exp. : </label>" << endl;
cout <<  "<input id=\"element_1\" name=\"multexpreq\" class=\"element text small\" type=\"text\" size = \"6\"  maxlength=\"25\" value=\""<< exposuresRequested << "\"/><br>" << endl;
cout <<  "<label class=\"description\" for=\"element_1\">Multiple Advance : </label>" << endl;
cout <<  "<input id=\"element_1\" name=\"element_1\" class=\"element text small\" type=\"text\" size = \"6\"  maxlength=\"5\" value=\"\"/><br>" << endl;
cout <<  "<label class=\"description\" for=\"element_1\">Exposure Count : </label>" << endl;
cout <<  "<input id=\"element_1\" name=\"exposures\" class=\"element text small\" type=\"text\" size = \"6\"  maxlength=\"125\" value=\""<< exposureCount << "\"/><br>" << endl;
cout <<  "<label class=\"description\" for=\"element_1\">Frame Count : </label>" << endl;
cout <<  "<input id=\"element_1\" name=\"element_1\" class=\"element text small\" type=\"text\" size = \"6\"  maxlength=\"125\" value=\"\"/><br>" << endl;
cout <<  "<label class=\"description\" for=\"element_1\">Film Used : </label>" << endl;
cout <<  "<input id=\"element_1\" name=\"element_1\" class=\"element text small\" type=\"text\" size = \"6\"  maxlength=\"125\" value=\"\"/><br>" << endl;
cout <<  "</div></form>" << endl;



cout <<  "<div id=\"footer\">" << endl;
cout <<  "Serial Number: XYZ Phone: 480-406-9804 Email: dwight_hunley@hotmail.com" << endl;
cout <<  "</div>" << endl;


*/

return 0;

}

int str2int (const string &str) {
  stringstream ss(str);
  int num;
  if((ss >> num).fail())
  {
      //ERROR
  }
  return num;
}

//FUNCTION  DEFINITION: 
  
 /*  Pre:  The  shell  command  that  should  be  executed  is  passed  as  a  parameter. 
   *            Values  of  0  for  p_fd_in  or  p_fd_out  indicates  shell  command  doesn't 
   *            use  stin  or  stdout  respectively,  so  they  should  be  closed. 
   *  Post:  Makes  accessible  both  the  standard  input  and  output  of  the  shell  
   *              process  it  creates. 
   *              Two  pipes  are  created:  one  provides  standard  input  for  the  shell   
   *              commmand,  and  the  other  for  passing  back  its  standard  output.
   *              The  pipe  file  descriptors  for  the  caller  to  use  are  pointed  to  by   
   *              p_fd_in  and  p_fd_out. 
   */       
 pid_t popen2(const char *shell_cmd, int *p_fd_in, int *p_fd_out) 
 { 
    //CREATING  TWO  PIPES: 
  int fds_processInput[2];  //pipe  for  process  input 
  int fds_processOutput[2]; //pipe  for  process  output 
    
   if(pipe(fds_processInput) != 0) //create  process  input  pipe 
     { 
       cerr << "pipe (process input) failed\n"; 
       exit(1); 
     } 
    
   if(pipe(fds_processOutput) != 0) //create  process  output  pipe 
     { 
       cerr << "pipe (process output) failed\n"; 
       exit(1); 
     } 
    
   //FORKING  A  CHILD  PROCESS: 
   pid_t pid; 
   if((pid = fork()) < 0) 
     { 
       cerr << "fork failed\n"; 
       exit(2); 
     } 
    
  //CONNECT  THE  CORRECT  PIPE  ENDS  IN  THE  CHILD: 
   if(pid == 0)  //child  process 
     { 
       //for  process  input  pipe: 
       close(fds_processInput[1]);   //close  output 
       dup2(fds_processInput[0], 0); //close  fd  0,  fd  0  =  fds_processInput[0] 
        
       //for  process  output  pipe: 
       close(fds_processOutput[0]);   //close  input 
       dup2(fds_processOutput[1], 1); //close  fd  1,  fd  1  =  fds_processOutput[1] 
        
  
       execl("/bin/sh", "sh", "-c", shell_cmd, 0 );  
       cerr << "failed to run shell_cmd\n"; 
     } 
   else  //parent  process 
     { 
       //for  process  input  pipe: 
       close(fds_processInput[0]);   //close  input 
        
       //for  process  output  pipe: 
       close(fds_processOutput[1]);   //close  output 
  
       if(p_fd_in == 0) 
     close(fds_processInput[1]); 
       else 
     *p_fd_in = fds_processInput[1]; 
        
       if(p_fd_out == 0) 
     close(fds_processOutput[0]); 
       else 
     *p_fd_out = fds_processOutput[0]; 
  
     } 
   return pid;  
 }
 
