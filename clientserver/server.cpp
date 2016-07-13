/* A Client-Server Application
* Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            */

#include <stdlib.h>     // for system call
#include <iostream>
#include "network/SocketServer.h"
using namespace std;
using namespace exploringBB;

int main(int argc, char *argv[]){
   cout << "Starting Non-threaded Server Example" << endl;
   SocketServer server(54321);
   cout << "Listening for a connection..." << endl;
   server.listen();
   string rec = server.receive(1024);
   cout << "Received from the client [" << rec << "]" << endl;
   const char* runcmdc;
   string runcmd;
   int i;
   runcmd = "/pw/data/controls/cert/dhunley/threadedClientServer_exp/forloop " + rec;
   runcmdc = runcmd.c_str();
   i = system(runcmdc);
   string message("The Server says thanks!");
   cout << "Sending back [" << message << "]" << endl;
   server.send(message);
   cout << "End of Non-threaded Server Example" << endl;
}
