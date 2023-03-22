/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */

#include "vector.h"
#include "pqueue-vector.h"
#include "error.h"
using namespace std;

VectorPriorityQueue::VectorPriorityQueue() {
	return;
}

VectorPriorityQueue::~VectorPriorityQueue() {
	return;
}

int VectorPriorityQueue::size() {
	return data.size();
}

bool VectorPriorityQueue::isEmpty() {
	return data.size()==0;
}

void VectorPriorityQueue::enqueue(string value) {
	data.add(value);
}

string VectorPriorityQueue::peek() {
	if(isEmpty()) error("");
	return data[findMinElem()];

}
int VectorPriorityQueue::findMinElem()
{
	int minElemIndex = 0;
	string minElem = data[0];
	for(int i = 0;i<data.size();i++)
	{
		if(data[i]<minElem)
		{
			minElem = data[i];
			minElemIndex = i;
		}
	}
	return minElemIndex;
}
string VectorPriorityQueue::dequeueMin() {
	int minElem = findMinElem();
	string minStr = data[minElem];
	data.remove(minElem);
	
	return minStr;
}

