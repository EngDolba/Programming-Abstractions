/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include <iostream>
#include "error.h"
#include <stddef.h>

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	numOfMembers=0;
	
	head = new monomer;
	tail = new monomer;
	head->next=tail;
	tail->next=NULL;
	head->val = "LinkedListHead";
	tail->val="LinkedListTail"; 
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	monomer* ptr = head;
	while(ptr)
	{
		monomer* tmp = ptr->next;
		delete ptr;
		ptr = tmp;
	}
}

int LinkedListPriorityQueue::size() {
	return numOfMembers;
}

bool LinkedListPriorityQueue::isEmpty() {
	return numOfMembers==0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	monomer* ptr = head;
	monomer* newMemb = new monomer;
	newMemb->val = value;
   while(true)
   {
	   monomer* tmp = ptr;
	   ptr = tmp->next;
	if(value<ptr->val || ptr==tail)
	   {
		   tmp->next = newMemb;
		   newMemb->next = ptr;
			numOfMembers++;
			return;
	   }
   }
}

string LinkedListPriorityQueue::peek() {
	if(isEmpty()) error("");
	return head->next->val;
}

string LinkedListPriorityQueue::dequeueMin() {
	if(isEmpty()) error("");
	numOfMembers--;
	monomer* tmp = head->next;
	string result = head->next->val;
	head->next = head->next->next;
	delete tmp;
	return result;
}

