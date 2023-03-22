/*
* File: WordLadder.cpp
* --------------------------
* Name: [TODO: enter name here]
* Section: [TODO: enter section leader here]
* This file is the starter project for the Word Ladder problem.
* [TODO: rewrite the documentation]
*/

#include <iostream>
#include "console.h"
#include "vector.h"
#include "simpio.h"
#include "queue.h"
#include "set.h"
#include "foreach.h"
#include "map.h"
#include "vector.h"
#include "lexicon.h"
using namespace std;

Queue<string> wordLadder(string startWord, string destWord);
bool checkSimpleCasesIfWordsAreGood(string startWord,string destWord);
bool isAttainableByChangingOneChar(string startWord,string endWord);
Set<string> oneLetterChangedWord(string word);
bool isUsed(string word,Set<string>& usedWords);
Lexicon english("EnglishWords.dat");
int main() {
	while(true)
	{
		string startingWord = getLine("Enter the starting word or nothing to quit: ");
		if(startingWord=="") break;
		string endingWord = getLine("Enter Ending Word: ");

		cout <<"Here is Your Word Ladder" << wordLadder(startingWord,endingWord).toString() << endl; 
	}
	return 0; 


}
Queue<string> wordLadder(string startWord, string destWord)
{
	Queue<string> qiu;
	if(!checkSimpleCasesIfWordsAreGood(startWord,destWord))
	{
		qiu.enqueue("There is no such ladder");
		return qiu;
	}
	Queue<Queue<string> > wordLadders;
	Queue<string> initialQueue;
	initialQueue.enqueue(startWord);
	wordLadders.enqueue(initialQueue);
	Set<string> usedWords;
	usedWords.add(startWord);
	while(!wordLadders.isEmpty())
	{
		Queue<string> samushaoQueue = wordLadders.dequeue();
		string samushaoWord = samushaoQueue.back();
		usedWords.add(samushaoWord);
		if(samushaoWord==destWord) return samushaoQueue;

		foreach(string str in oneLetterChangedWord(samushaoWord))
		{
			if(str==destWord) 
			{
				Queue<string> q = samushaoQueue;
				q.enqueue(str);
				return q;
			}
			if(!isUsed(str,usedWords))
			{
				usedWords.add(str);
				Queue<string> q = samushaoQueue;
				q.enqueue(str);
				wordLadders.enqueue(q);


			}

		}

	}
	Queue<string> qr;
	qr.enqueue("There is no such ladder"); //cota uxeshi implementaciaa magram ara ushavs
	return qr;

}
bool checkSimpleCasesIfWordsAreGood(string startWord,string destWord)
{
	if(startWord.size() != destWord.size()) return false;
	if(destWord.size()==0) return false;
	if(startWord.size()==0) return false;
	return true;
}

Set<string> oneLetterChangedWord(string word)
{
	Set<string> result1;
	for(size_t i = 0;i<word.size();i++)
	{
		for(int j =0;j<26;j++)
		{
			char tmp = word[i];
			word[i]='a'+j;
			if(english.contains(word))
			{
				result1.add(word);
			}

			word[i]=tmp;

		}
	}

	return result1;

}
bool isUsed(string word,Set<string>& usedWords)
{
	if(usedWords.contains(word)) return true;
	return false;
}