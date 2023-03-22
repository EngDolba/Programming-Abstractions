/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"
#include <iostream>
HeapPriorityQueue::HeapPriorityQueue() {
	arraySize = 32;
	words = new string[arraySize];
	numOfMembers = 0;
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] words;
}

int HeapPriorityQueue::size() {
	return numOfMembers;
}

bool HeapPriorityQueue::isEmpty() {
	return size()==0;
}

void HeapPriorityQueue::enqueue(string value) {
	if(numOfMembers+1==arraySize)
		changeArraySize();
	numOfMembers++;
	words[numOfMembers] = value;
	if(numOfMembers==1) 
		return;
	int parent = numOfMembers/2;
	int child = numOfMembers;
	while(words[child]<words[parent])
	{
		swap(child,parent);
		if(parent<=1) return;
		child = parent;
		parent/=2;
	}
}

string HeapPriorityQueue::peek() {
	if(isEmpty()) error("");
	return words[1];
}

string HeapPriorityQueue::dequeueMin() {
	string result = peek();
	swap(1,numOfMembers);
	numOfMembers--;
	int lowestChild;
	int parent = 1;
	if(numOfMembers==1)
		return result;
	if(numOfMembers==2) lowestChild = 2;
	else
		lowestChild = chooseMin(2,3);
	string str = words[lowestChild];
	while(str<words[parent])
	{
		swap(lowestChild,parent);
		parent = lowestChild;
		if (parent*2+1<=numOfMembers){ 
			lowestChild = chooseMin(parent*2,parent*2+1);
		}
		else if (parent*2<=numOfMembers){ 
			lowestChild = parent*2;

		} 
		else break;
		str = words[lowestChild];
	}
return result;
}
void HeapPriorityQueue::swap(int a,int b)
{
	string tmp = words[a];
	words[a] = words[b];
	words[b] = tmp;
}
int HeapPriorityQueue::chooseMin(int str1,int str2)
{
	if(words[str1]>words[str2]) return str2;
	return str1;
}
void HeapPriorityQueue::changeArraySize()
{
	arraySize = arraySize*2;
	string* tmp = words;
	words = new string[arraySize];
	for(int i = 0;i<arraySize/2;i++)
			words[i] = tmp[i];
	delete[] tmp;
}