/*
* File: Subsequences.cpp
* ----------------------
* Name: [TODO: enter name here]
* Section: [TODO: enter section leader here]
* This file is the starter project for the Subsequences problem
* on Assignment #3.
* [TODO: extend the documentation]
*/

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Given two strings, returns whether the second string is a
* subsequence of the first string.
*/
bool isSubsequence(string text, string subsequence);

int main() {
	string str1 = "abc";
	string str2 = "ab";
	cout << isSubsequence(str1,str2) << endl;
	return 0;
}
bool isSubsequence(string text, string subsequence)
{
	if(subsequence.empty()) return true;
	if(text.empty()) return false;
	if(subsequence[0]==text[0])
	{
		return isSubsequence(text.substr(1,text.length()-1),subsequence.substr(1,subsequence.length()-1));
	}
	return isSubsequence(text.substr(1,text.length()-1),subsequence);
}