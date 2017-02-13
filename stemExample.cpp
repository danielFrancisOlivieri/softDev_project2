/*****************************************************************************/
/*                                                                           */
/*  Filename:     stemExample.cpp                                             */
/*  Author(s):    Jim Skon                                                   */
/*  Last Update:  1/21/2017                                                  */
/*                                                                           */
/*  This is a program that shows how to use the English word stemmer.        */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <utility>
#include <algorithm>
// Include stemming stuff
#include "english_stem.h"

using namespace std;

int main () {

  string word;

  stemming::english_stem<char, std::char_traits<char> > StemEnglish;

  while (1) {
    cout << "Enter word the word to find the stem of: ";
    cin >> word;
    /* Convert word to upper case*/
    transform(word.begin(), word.end(), word.begin(), ::toupper);
    string saveWord = word;
    /* Reduce to Stem */
    StemEnglish(word);
    cout << "The stemmed version of \"" << saveWord <<"\" is \"" << word << "\"" << endl;
  }
  return 0;
}














