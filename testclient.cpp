#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "fifo.h"

using namespace std;
string receive_fifo = "Wordreply";
string send_fifo = "Wordrequest";

int main() {
  string message, word;
  string reply;
  vector <string> vectorOfLines;

  while (1) {
	cout << "Enter a new word:";
	cin >>  word;
	transform(word.begin(), word.end(), word.begin(), ::toupper);

	
	// create the FIFOs for communication
	Fifo recfifo(receive_fifo);
	Fifo sendfifo(send_fifo);

	message = "$WORD*" + word;
	cout << "Send:" << message << endl;
	sendfifo.openwrite();
	sendfifo.send(message);

	/* Get a message from a server */
	
	recfifo.openread();
	
	do {
		
			reply = recfifo.recv();
	//vectorOfLines.push_back(reply);
	cout << "working: " << reply << endl;
	}
		while (reply != "$END");

	
		
	recfifo.fifoclose();
	sendfifo.fifoclose();
	/*
	for (int i; i < vectorOfLines.size() - 1; i++)
	{
	cout << "Server sent: " << vectorOfLines[i] << endl;	
	}
	*/
  }


}
