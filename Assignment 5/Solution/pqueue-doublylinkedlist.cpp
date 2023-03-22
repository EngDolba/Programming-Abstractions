/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"
#include <iostream>
#include <stddef.h>

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
		numOfMembers = 0;
		head = new monomer;
		tail = new monomer;
		head->backward = NULL;
		head->val = "LinkedListHead";
		tail->val = "LinkedListTail";
		tail->forward = NULL;
		tail->backward = head;
		head->forward = tail;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	monomer* ptr  = head;
	while(ptr)
	{
		monomer* tmp = ptr->forward;
		delete ptr;
		ptr = tmp;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return numOfMembers;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return numOfMembers==0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	numOfMembers++;
	monomer* tmp = head->forward;
	monomer* newMonomer = new monomer;
	newMonomer->val = value;
	head->forward = newMonomer;
	newMonomer->backward = head;
	newMonomer->forward = tmp;
	newMonomer->forward->backward = newMonomer;
}

string DoublyLinkedListPriorityQueue::peek() {
	if(isEmpty()) error("");
	return findMinString()->val;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
if(isEmpty()) error("");
	numOfMembers--;
	monomer* minMonomer = findMinString();
	string result = minMonomer->val;
	minMonomer->forward->backward = minMonomer->backward;
	minMonomer->backward->forward = minMonomer->forward;
	delete minMonomer;
	return result;
}
DoublyLinkedListPriorityQueue::monomer* DoublyLinkedListPriorityQueue::findMinString()
{
	monomer* minString = head->forward;
	monomer* tmp = head->forward;
	while(tmp!=tail)
	{
		monomer* ptr = tmp;
		tmp = tmp->forward;
		if(minString->val > ptr->val)
		{
			minString = ptr;
		}
	}
	return minString;
}

