#include <iostream>         // for the input/output
#include <stdlib.h>         // for the system, getenv calls
#include <sys/sysinfo.h>    // for the system uptime call
#include <cgicc/Cgicc.h>    // the cgicc headers
#include <cgicc/CgiDefs.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include "LED.h"            // the LED class from Chapter 5 of the book 
#include <fstream>
#include <sstream>

using namespace std;
using namespace cgicc;

#define exposureCount_PATH "/root/expcounts.txt"

int main()
{

string exposureCount1;
int number;
stringstream ss;
ss << exposureCount_PATH;
fstream fs;
fs.open(ss.str().c_str(), fstream::in);
fs >> number;
ostringstream temp;  //temp as in temporary
temp<<number;
exposureCount1=temp.str();      //str is temp as string
//exposureCount=ss.str();      //str is temp as string
//cout << "The integer number value was " << number << " exposure counts." << endl;
//cout << "The string number number value was " << number << " exposure counts." << endl;
fs.close();

ofstream myfile;
   int i;
   Cgicc form;                                     // the CGI form object
   string pwr_cmd, command, exposureCount, exposuresRequested, exposuresReset, expsReset;

myfile.open ("example.html");

   //bool isStatus = form.queryCheckbox("status");   // get the state of the status checkbox
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
      //exposureCount = "0";                         // if it is invalid use 100
      exposureCount = exposureCount1;
   }
   else { exposureCount = it->getValue(); }          // otherwise use submitted value
      exposureCount = exposureCount1;
   
   it = form.getElement("multexpreq");   // get the exisitng number of exposures executed value
   if (it == form.getElements().end() || it->getValue()==""){
      exposuresRequested = "0"; // if it is invalid use 100
   }
   else { exposuresRequested = it->getValue(); }          // otherwise use submitted value
   
   char *value = getenv("REMOTE_ADDR");	           // The remote address CGI env. variable

//  it = form.getElement("expsReset");   // get the exisitng number of exposures executed value
//  exposuresRequested = it->getValue();
  expsReset = "No";
//  exposuresReset = "No";

// Generate the form but use states that are set in the form that was submitted
   cout << HTTPHTMLHeader() << endl;               // Generate the HTML form using cgicc
//   cout << html() << head() << title("EBB C++ Post Power Example") << head() << endl;
 //  cout << body() << h1("BeagleBone POST Camera Example") << endl;;

//cout << "<form action=\"\">\n";
cout << "<form action=\"/cgi-bin/postCamera.cgi\" method=\"POST\">\n";
//cout << "<input type=\"submit\" value=\"Execute Command\" onclick=\"/cgi-bin/postCamera.cgi\" method=\"POST\">\n";
//cout << "</form>\n";
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
cout <<  "<h1>Hunley's June 21th, 2016 Eng Inc.</h1>" << endl;
cout <<  "</div>" << endl;

cout <<  "<div id=\"nav\">" << endl;
cout <<  "<h2>Control </h2>" << endl;
cout <<  "<label class=\"description\" for=\"element_1\">Exposure Time : </label>" << endl;
cout <<  "<input id=\"element_1\" name=\"element_1\" class=\"element text small\" type=\"text\" size = \"6\" maxlength=\"25\" value=\"\"/><br>" << endl;
cout <<  "<label class=\"description\" for=\"element_1\">Multiple Exp. : </label>" << endl;
cout <<  "<input id=\"element_1\" name=\"multexpreq\" class=\"element text small\" type=\"text\" size = \"6\"  maxlength=\"25\" value=\""<< exposuresRequested << "\"/><br>" << endl;
cout <<  "<label class=\"description\" for=\"element_1\">Multiple Advance : </label>" << endl;
cout <<  "<input id=\"element_1\" name=\"element_1\" class=\"element text small\" type=\"text\" size = \"6\"  maxlength=\"5\" value=\"\"/><br>" << endl;
cout <<  "<label class=\"description\" for=\"element_1\">Exposure Count : </label>" << endl;
cout <<  "<input id=\"element_1\" name=\"exposures\" class=\"element text small\" type=\"text\" size = \"6\"  maxlength=\"125\" value=\""<< exposureCount << "\"/>" << endl;
cout <<  "<input  type=\"checkbox\" name=\"expsReset\" value=\"Yes\" checked><br>" << endl;

cout <<  "<button type=\"button\" onclick=\"alert('Hello world!')\">Click Me!</button><br>" << endl;

cout <<  "<label class=\"description\" for=\"element_1\">Frame Count : </label>" << endl;

cout <<  "<button type=\"button\" onclick=\"/cgi-bin/helloworld.sh\"  method=\"POST\">run helloworld.sh!</button><br>" << endl;

cout <<  "<input id=\"element_1\" name=\"element_1\" class=\"element text small\" type=\"text\" size = \"6\"  maxlength=\"125\" value=\"\"/><br>" << endl;
cout <<  "<label class=\"description\" for=\"element_1\">Film Used : </label>" << endl;
cout <<  "<input id=\"element_1\" name=\"element_1\" class=\"element text small\" type=\"text\" size = \"6\"  maxlength=\"125\" value=\"\"/><br>" << endl;
cout <<  "</div>" << endl;


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
cout <<  "  <option value=\"yada yada\">Quarter</option>" << endl;
cout <<  "</select>" << endl;
cout <<  "</div>" << endl;


cout <<  "<div id=\"nav3\">" << endl;
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
cout << "<input type=\"submit\" value=\"Process Selections\" />";
cout <<  "</div>" << endl;



cout <<  "<div id=\"footer\">" << endl;
cout <<  "Serial Number: XYZ Phone: 480-406-9804 Email: dwight_hunley@hotmail.com" << endl;
cout <<  "</div>" << endl;

cout <<  "</body>" << endl;
cout <<  "</html>" << endl;


   // Process the form data to trigger the Power or LED state
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

    if (command=="single")
    {
     i = system("nice -20 /root/camera/shutter_openloop/shutter_openloop");
     cout << "<div> Ran a single exposure ! </div>";
    }

    cout << "<div> The exposure count file is " << ss.str() << "</div>";
    cout << "<div> The exposure count is  " << exposureCount1 << "</div>";
    cout << "<div> The exposure count reset value is  " << expsReset << "</div>";



myfile <<  "temp file myfile" << endl;


  myfile.close();
  return 0;

}
