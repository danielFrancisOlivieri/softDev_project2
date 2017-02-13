/*****************************************************************************/
/*                                                                           */
/*  Filename:     textindex.cpp                                             */
/*  Author(s):    Jim Skon                                                   */
/*  Last Update:  2/10/2013                                                  */
/*                                                                           */
/*  This code creates an inverted list of tall the words in some text        */
/*  as a STL map structure that maps from words points into the file.        */
/*  The resulting structure can than be used to retrieve a complete list of  */
/*  All places in the file that contain a certain word.                      */
/*                                                                           */
/*  The function "index_create()" creates the inverted list.                 */
/*                                                                           */
/*  The function "text_search(string) returns a STL list structure of        */
/*  all place where that word is found.                                      */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <map>
#include <utility>
#include <list>
#include <set>
// Include stemming stuff
#include "english_stem.h"

using namespace std;

#include "textindex.h"

map<string, list<int> > refs;


/*****************************************************************************/
/*                                                                           */
/*      getNextWord(string&) given a string, return the next word, and     */
/*                remove this word from the current string                   */
/*                                                                           */
/*****************************************************************************/
string getNextWord(string& line) {

  string word="";
  int pos;

  if (line.length() > 1)
	{
	  pos = line.find_first_of(".,; :?!""''()");
	  /* get next word */
	  if (pos != 0) {
		word = line.substr(0,pos);
        }
	  /* trim the line */
	  if (pos == string::npos) {
		pos = line.length()-1;
	  }
	  line = line.substr(pos+1, 2000);
	}
  return word;

}


/*****************************************************************************/
/*                                                                           */
/*      Load - Load text into inverted list                                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
int buildTextIndex (string filename) {

  ifstream  infile;     /* input file descriptor */
  int position;         /* Location of line in the file */
  string text, line, word;

  int wordcount = 0, rootcount = 0, pos;

  stemming::english_stem<char, std::char_traits<char> > StemEnglish;

  /* open text file */
  infile.open(filename.c_str(), ios::in);
  if (!infile) {
	cerr << "Error - can't open input file: " << filename << endl;
	return 1;  /* error */
  }

  int total = 0;

  /* process text file */
  while (!infile.fail()) {
    /* Get the file position */
    position = infile.tellg();
    /* get the next line */
    getline(infile,line);

    /* Convert verse to upper case*/
    transform(line.begin(), line.end(), line.begin(), ::toupper);

	/* for each word in the verse, stem and put in map */
	while (line.length() > 1) {

	  word = getNextWord(line);
	  
	  if (word.length() > 0 ) {
		/* Reduce to Stem */
		StemEnglish(word);
		/* Convert to upper case*/
		transform(word.begin(), word.end(),word.begin(), ::toupper);
		wordcount++;
		refs[word].push_back(position);
	  }
	}

  }
  cout << "Words: " << wordcount << " Unique: " << refs.size() << endl;
  
  return 1;  /* success */
}

/*****************************************************************************/
/*                                                                           */
/*  Search - Returns refs for all verseswith word matching the input string  */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
list<int> indexSearch(string word) {

  map<string, list<int> >::iterator it;  // iterator for find
  list<int> blank; // return for no matches

  /* Convert search to all caps */
  transform(word.begin(), word.end(),word.begin(), ::toupper);
  /* return the refs */
  /* First use find, so as to NOT create a new entry */
  it = refs.find(word);
  if (it == refs.end()) {
    return(blank);
  } else {
    return (refs[word]);
  }
}















