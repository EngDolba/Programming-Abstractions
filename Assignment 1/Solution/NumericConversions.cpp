/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);
string intToStringForNLessThanZero(int n);

/* Main program */

int main() {
	cout << intToString(0) << endl;
	cout << stringToInt("") << endl;
    return 0;
}
string intToString(int n)
{
	if(n<0) return intToStringForNLessThanZero(n);
	string s = "S";
	if(n<10) 
	{
		s[0] = (char)(n+'0');
		return s;
	}
	return intToString(n/10)+intToString(n%10);
		
} 
int stringToInt(string str) 
{
	if(str[0]=='-')
	{	
		if(str.length()==2) return -1*(str[1]-'0');
		str = str.substr(1,str.length()-1);
		return -1 * (stringToInt(str.substr(0,str.length()-1))*10+str[str.length()-1]-'0');
	}
	if(str.length()==0) return -1; // ideashi amis nulad chatvla sheidzleba magram chemi azrit aralogikuria
	if(str.length()==1) return str[0]-'0';
	return stringToInt(str.substr(0,str.length()-1))*10+str[str.length()-1]-'0';
}
string intToStringForNLessThanZero(int n)
{
	return (string)"-"+intToString(n*-1);
}
