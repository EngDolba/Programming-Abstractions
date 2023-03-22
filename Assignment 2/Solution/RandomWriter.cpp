/*
* File: RandomWriter.cpp
* ----------------------
* Name: [TODO: enter name here]
* Section: [TODO: enter section leader here]
* This file is the starter project for the Random Writer problem.
* [TODO: rewrite the documentation]
*/

#include <iostream>
#include "console.h"
#include <fstream>
#include "vector.h"
#include "map.h"
#include "simpio.h"
#include "random.h"
using namespace std;
ifstream input;
ofstream  output;
void readInput(ifstream& input,string& filename,int& markovNumber);
void readAndBuildStructure(string& filename,int& markovNumber,Map<string,Vector<char> >& text);
void proccessAndGenerateText(string& filename,int &markovNumber);
void proccessString(string& str,Map<string,Vector<char> >& text);
void offsetStringByOne(string& str);
void generateText(Map<string,Vector<char> >& text);
string findMostFrequent(Map<string,Vector<char> >& text);


int main() {
	int markovNumber;
	string filename;
	readInput(input,filename,markovNumber);
	proccessAndGenerateText(filename,markovNumber);
	cout << endl << "THE END OF THE PROGRAM" << endl;
	return 0;
}

void readInput(ifstream& input,string& filename,int& markovNumber) {
	filename = getLine("Enter the filename: ");
	filename+=".txt"; // ragac mxriv arasworia radgan mxolod txt-ebi ar shemodis tumca didi mnishvneloba ar aqvs da ase ufro komfortulia
	input.open(filename.c_str());
	while(input.fail())
	{
		input.clear();
		filename = getLine("Incorrect filename, please enter again: ");
		filename+=".txt";
		input.open(filename.c_str());
	}
	while(true)
	{
		markovNumber = getInteger("Enter the markov number model(1-10: )");
		if(markovNumber >= 1 && markovNumber <= 10) break;
	}

}
void proccessAndGenerateText(string &filename,int &markovNumber)
{
	Map<string,Vector<char> > text;
	readAndBuildStructure(filename,markovNumber,text);
	generateText(text);
}
void readAndBuildStructure(string& filename,int& markovNumber,Map<string,Vector<char> >& text)
{	
	string str = "";
	while(true)
	{
		
		char ch = input.get();
		str += ch;
		if(str.size()==markovNumber+2)
		{
			offsetStringByOne(str);
		}
		if(str.size()==markovNumber+1)
		{
			proccessString(str,text);
		}
		if(ch==EOF) break;
	}
}



void generateText(Map<string,Vector<char> >& text){	

	string mostFrequent = findMostFrequent(text);
	int charCount = mostFrequent.size();
	cout << mostFrequent;
	string activeString = mostFrequent;
	while(charCount!=2000)
	{
		Vector<char> vct = text[activeString];
		if(vct.size()==0) break;
		char nextCh = vct.get(randomInteger(0,vct.size()-1));
		cout << nextCh;
		offsetStringByOne(activeString);
		activeString+=nextCh;
		charCount++;
	}
}
string findMostFrequent(Map<string,Vector<char> >& text)
{
	
	string frqt;
	int max = 0;
	foreach(string str in text)
	{
		if(text[str].size() > max){
			frqt = str;
		}
	}
	return frqt;
}

void offsetStringByOne(string &str)
{
	string str2 = "";
	for(int i=0;i<str.size()-1;i++)
	{
		str2+=str[i+1];
	}
	str = str2;
}
void proccessString(string &str,Map<string,Vector<char> > &text)
{
	str.size();
	char nextChar = str[str.length()-1];
	text[str.substr(0,str.length()-1)] += nextChar;


}