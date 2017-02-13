/***************************************************************************
 * shakespeare.cpp  -  Program for shakespeare nerds
 *
 * copyright : (C) 2017 by Daniel Olivieri
 *
 * This program finds the lines that words in shakespeare appear on and puts the searched for word in bold 
 *   It also displays the book that the word was found in 
 * 
 *
 ***************************************************************************/
 
 
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <map>
//#include <algorithm>
#include <vector>
#include <sstream>
//#include <wchar.h>
//#include <windows.h>
#include <string>
#include <utility>
#include <algorithm>

#include "english_stem.h"
 
using namespace std;

// class that allows the vectors to hold both the line number and the name of the play the line is in 
class textLineNumbers {
   
  public:
    int lineNumber;
	string title;
};


 map<string, vector<textLineNumbers> > curMap; // curMap maps to the vectors that hold the line numbers and names of plays 
 
// precon: curMap exists
// postcon:  when passed a word, returns a vector of references
vector <textLineNumbers> indexSearch(string word) {
     map<string, vector<textLineNumbers> >::iterator it;  // iterator for find                                                                
     vector<textLineNumbers> blank; // return for no matches                                                                                  
    /* find the word and get the vector of references */
    /* First use find, so as to NOT create a new entry */
    it = curMap.find(word);
    if (it == curMap.end()) {
         return(blank);
    } else {
        return (curMap[word]);
    }
}

void displayVector (vector <textLineNumbers> & vec, ifstream &is, string choice);
//void putIntoMap(map<string, vector<int> > & curMap);

// precon: is exists and 
// postcon: runs the user interface portion of the program for as long as the user wants to continue 
void runLoop (ifstream & is);

// precon: program started
// postcon: feeds textLineNumbers objects into the map of vectors
void putIntoMap (map<string, vector<textLineNumbers> > &curMap, ifstream &is);

int main() {

		
	 stemming::english_stem<char, std::char_traits<char> > StemEnglish; // allows for stemming 

	string path = "/home/class/SoftDev/Shakespeare/"; // holds first part of file path 
	
		// sets file
	string filename = path + "Shakespeare.txt";  
	
	
 string line; // variable to use for inputting individual lines 

	  
	  	// sets is as an ifstream for the shakespeare file 
	ifstream is(filename.c_str());
	  putIntoMap(curMap, is); // this feeds all lines into the map for easy access later
	 
  
is.close(); // closes file 

runLoop(is);



}

void displayVector (vector <textLineNumbers> & vec, ifstream &is, string choice)
{
	string aLine;
	
	stemming::english_stem<char, std::char_traits<char> > StemEnglish;
	int c = 0;
	cout << endl;
	cout << "**********************************************************" << endl;
	cout << "The following are all of the matches for " << choice << endl;
	cout << "**********************************************************" << endl;
	cout << endl;
	for (int i = 0; i < vec.size(); i++)
	{
		int firstIndex, secondIndex; // for finding place to insert the bold 
	
		cout << vec[i].title << endl; // puts out the title of the play 
		
		
		is.seekg(vec[i].lineNumber, is.beg);
		//cout << is.tellg() << endl;
		getline(is, aLine);
		
		StemEnglish(choice);
		//cout << "Choice: " << choice << endl;
		
		stringstream forBolding (aLine);  // puts line into stringstream for easy use 
		string singleWord, wholeLine = ""; // initializes strings to be used in bolding process 
		while( forBolding >> singleWord)
		{
			// selects the right word to bold 
			if (singleWord.find(choice) != std::string::npos) 
			{
				singleWord = "\e[1m" + singleWord + "\e[0m ";
			}
			else
			{
			singleWord = singleWord + " " ;	
			}
			wholeLine = wholeLine + singleWord;
		}
		cout << wholeLine << endl; // prints line 
		
		

	}
// in case search comes up empty 
	if (vec.size() == 0)
	{
		cout << "It looks like Shakespeare never used this word." << endl << endl;
	}
	else
	{
		cout << "number of matches: " << vec.size() << endl;
	}
	
	
};


// precon: program started
// postcon: feeds textLineNumbers objects into the map of vectors
void putIntoMap (map<string, vector<textLineNumbers> > &curMap, ifstream &is)
	{
		
		stemming::english_stem<char, std::char_traits<char> > StemEnglish;
		
		vector<string> vectorOfLines; // useful for finding titles 
		
		textLineNumbers currentWord;
		
	  int c = 0;
	  int currentTitle; 
	 while (!is.eof())
	 {
		 string line;
		 // line position used to keep track of where the line begins 
		 int linePosition = is.tellg();
		 
		    getline (is,line); // puts next line into var line 
			vectorOfLines.push_back(line);

string title; // holds ttitle 
if (!line.empty())
{
	if ( (line.at(0) == '1') && ((line.at(1) == '5') || (line.at(1) == '6')) ) // finds line that holds year 
{
	c++;
	getline(is, line);
	// this while loop searches for the actual title of the play 
	while (line.size() < 4)
	{
		getline(is, line);
		currentWord.title = line;
		
	}


		}

}
currentWord.lineNumber = linePosition;
	
		transform(line.begin(), line.end(), line.begin(),(int (*)(int))tolower); // makes the line lower case

			
			stringstream  ssLine(line); // puts line into ssLine for processing 
			
				string wordToProcess;
			while (ssLine >> wordToProcess)
			{
				StemEnglish(wordToProcess);
		
				curMap[wordToProcess].push_back(currentWord);
				
			}
			
	 }
  
is.close();

	}

void runLoop (ifstream & is)
{
		string path = "/home/class/SoftDev/Shakespeare/";
	stemming::english_stem<char, std::char_traits<char> > StemEnglish;
	
		// sets file
	string filename = path + "Shakespeare.txt"; 
	//ifstream is(filename.c_str());
	
	cout << "Hail to your grace and welcome to the world of Shakespeare!" << endl << endl;
	cout << "This program will help you find every instance of a word in all of Shakespeare's work. " << endl << endl;
	is.open(filename.c_str());
	string choice;
	while (( choice != "q") || ( choice != "q"))
{
	
		 cout << "Put in the name of the word you want to search for or type 'q' to quit." << endl << endl;
 cin >> choice;
	 
	StemEnglish (choice);
	 
 if (!((choice == "q") || (choice == "Q")))
 {
displayVector(curMap[choice], is, choice);
}
}
cout << "I do desire we become better strangers." << endl;
cout << "Goodbye." << endl;
}

