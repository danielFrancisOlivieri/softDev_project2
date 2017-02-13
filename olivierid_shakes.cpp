#include <iostream>
// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

//Stuff for pipes
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "fifo.h"
using namespace std;
using namespace cgicc; // Needed for AJAX functions.

// Possible values returned by results_select
#define WORD

vector <string> linesToPresentVector;

//myString needs to be a copy of the original string
std::string StringToUpper(std::string myString)
{
  const int length = myString.length();
  for(int i=0; i!=length ; ++i)
    {
      myString[i] = std::toupper(myString[i]);
    }
  return myString;
}

// Take a string of words and make a HTML table line.
void makeTableLine(string& line) {

  cout << "<tr><td> ";
  for (int i = 0; i <  line.length() ; i++) {

    if (line[i] == ' ') {
      cout << " <td> ";
    } else {
      cout << line[i];
    }
  }
  cout << " </tr> ";
}

// fifo for communication
string receive_fifo = "Wordreply";
string send_fifo = "Wordrequest";

int main() {
  Cgicc cgi;    // Ajax object
  char *cstr;
  //string results;
 
  // Create AJAX objects to recieve information from web page.
  //form_iterator word = cgi.getElement("word");

  form_iterator name = cgi.getElement("name");
  //form_iterator name = cgi.getElement("name");

  // create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo);
  
   cout << "Content-Type: text/plain\n\n";

  
 
  // Call server to get results
  string stname = **name;
  cout << "stname: " << stname << endl;
  stname = StringToUpper(stname);
  string message =  stname;
  sendfifo.openwrite();
  sendfifo.send(message);
  
   recfifo.openread();
  string results = recfifo.recv();
  recfifo.fifoclose();
  sendfifo.fifoclose();
  
  cout << results;
  
  
  /* Get a message from a server */
  
  //recfifo.openread();
 
 // while (1)
 // {
	  // cout << "girth" << endl;
   // results = recfifo.recv();
   // // cout << results;
   // linesToPresentVector.push_back(results);
   // if (results == "$END")
   // {
	   // break;
   // }
 // }
 
 

cout << "FINISHED" << endl;
  
return 0;
}
