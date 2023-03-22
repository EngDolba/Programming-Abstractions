/*
* File: FleschKincaid.cpp
* ----------------------
* Name: [TODO: enter name here]
* Section: [TODO: enter section leader here]
* This file is the starter project for the Flesch-Kincaid problem.
* [TODO: rewrite the documentation]
*/

#include <iostream>
#include "console.h"
#include "simpio.h"
#include <string>
#include "tokenscanner.h"
#include <fstream>
using namespace std;
void readInput(ifstream& input,string& filename);
bool isMark(char ch);
bool isVowel(char ch);
int howManyVowels(string s);
void proccesFile(TokenScanner& scanner);
	int wordCount = 0;
	int markCount = 0;
	int marcvaliCount = 0;
	ifstream input;
int main() {

	
	double grade = 0;
	string filename;
	readInput(input,filename);
	TokenScanner scanner(input);
	scanner.ignoreWhitespace();
	scanner.addWordCharacters("'-`");
	proccesFile(scanner);
	if(wordCount==0) wordCount++;
	if(markCount==0) markCount++;
	grade=-15.59+0.39*((double)wordCount/markCount)+11.8*((double)marcvaliCount/wordCount);



	return 0;
}

void readInput(ifstream& input,string& filename) {
	filename = getLine("Enter the filename: ");
	input.open(filename.c_str());
	while(input.fail())
	{
		input.clear();
		filename = getLine("Incorrect filename, please enter again: ");
		input.open(filename.c_str());
	}

}
bool isMark(char ch) {
	return ch=='?' ||ch=='!' ||ch=='.' ||ch==',';
}
bool isVowel(char ch)
{
	return ch=='a' ||ch=='e' ||ch=='i' ||ch=='o'||ch=='u' || ch=='y';

}
int howManyVowels(string s)
{
	int result=0;
	for(int i = 0;i<s.length();i++)
	{
		if(i+1!=s.length()-1 && isVowel(s[i]) && isVowel(s[i+1])) result--;
		if(isVowel(s[i])) result++;
		if(i==s.length()-1 && s[i]=='e') result--;

	}
	if(result==0) return 1;
	return result;
}
void proccesFile(TokenScanner& scanner)
{
	while(scanner.hasMoreTokens())
	{

		string line = scanner.nextToken();
		if((line[0] >= 'a' && line[0] <= 'z') || (line[0] >= 'A' && line[0] <= 'Z')) wordCount++;
		if(isMark(line[0])) markCount++;
		marcvaliCount+=howManyVowels(line); 
	
	}
}