/*************************************************************
 * File: pqueue-extra.cpp
	
 */
 // carieli stringis damatebis nebas testebi ar idzleva amitom mec im gatvlit vwer rom carieli ar daemateba
	
#include "pqueue-extra.h"
#include <iostream>
#include "error.h"

ExtraPriorityQueue::ExtraPriorityQueue() {
	arraySize = 16;
	currentSize = 0;
	deletedWords = 0;
	words = new string[arraySize];
	
}

ExtraPriorityQueue::~ExtraPriorityQueue() {
	delete[] words;
	return;
}

int ExtraPriorityQueue::size() {
	return currentSize;
}

bool ExtraPriorityQueue::isEmpty() {
	return currentSize==0;
}

void ExtraPriorityQueue::enqueue(string value) {
	if(value.empty()) error("");
	if(arraySize==currentSize+deletedWords)
	{
		if(deletedWords!=0) cleanArrayFromDeletedWords();
		else  changeArraySize();
	}
	words[currentSize+deletedWords] = value;
	currentSize++;
}

string ExtraPriorityQueue::peek() {
	if(currentSize==0) error("empty Queue");
	return words[findMinWord()];
}

string ExtraPriorityQueue::dequeueMin() {

	if(currentSize==0) error("empty queue");
	
	int index = findMinWord();
	string result = words[index];
	
	words[index] = "";
	currentSize--;
	deletedWords++;
	return result;
}
int ExtraPriorityQueue::findMinWord()
{
	int index = 0;
	for(int i = 0; i<deletedWords+currentSize;i++)
	{
		if(words[i]!="") 
		{
			index = i;
			break;
		}
	}
	for(int i = index; i<deletedWords+currentSize;i++)
	{
		if(words[index]>words[i] && words[i]!="") index = i;
	}
	return index;
}
void ExtraPriorityQueue::cleanArrayFromDeletedWords() {
	string* tmp = words;
	words = new string[arraySize];
	int index=0;
	for(int i = 0;i<currentSize+deletedWords;i++)
	{
		if(tmp[i]!="")
		{
			words[index] = tmp[i];
			index++;
		}
	}
	deletedWords = 0;
	delete[] tmp;
}

void ExtraPriorityQueue::changeArraySize() {
	arraySize = arraySize * 2;
	string* tmp = words;
	words = new string[arraySize];
	for(int i = 0;i<currentSize+deletedWords;i++) // aq tu movida deletedWords isedac nulia magram generalizaciistvis iyos ase
	{
			words[i] = tmp[i];
	}
	delete[] tmp;
}
