/**********************************************
 * File: pqueue-extra.h
 *
 * Unsorted Array based priority Queue
 * it just adds words to array(does not sort)
 * if dequeueing, it gets string, returns and changes the index to ""(Demo Program does not permit to enqueue empty string so I suppose that empty string wont be added)
 * if array is full it deletes ""-s and rewrites array without them if that is not enough it doubles the size
 */
#pragma once

#include <string>
using namespace std;

/*
 * TODO: Describe this class!
 */
class ExtraPriorityQueue {
public:
	/* Constructs a new, empty priority queue. */
	ExtraPriorityQueue();
	
	/* Cleans up all memory allocated by this priority queue. */
	~ExtraPriorityQueue();
	
	/* Returns the number of elements in the priority queue. */
	int size();
	
	/* Returns whether or not the priority queue is empty. */
	bool isEmpty();
	
	/* Enqueues a new string into the priority queue. */
	void enqueue(string value);
	
	/* Returns, but does not remove, the lexicographically first string in the
	 * priority queue.
	 */
	string peek();
	
	/* Returns and removes the lexicographically first string in the
	 * priority queue.
	 */
	string dequeueMin();

private:
	string* words;
	int currentSize;
	int deletedWords;
	int arraySize;
    void cleanArrayFromDeletedWords();
	void changeArraySize();
	int findMinWord();
};


