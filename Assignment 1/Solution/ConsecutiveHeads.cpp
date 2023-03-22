/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "random.h"
using namespace std;

bool isThrownCoinHead();
void howManyFlipsDoesItTake();

int main() {
    howManyFlipsDoesItTake();
	return 0;
}
void howManyFlipsDoesItTake()
{
	int counter = 0;
	int headCounter = 0;
	while(true)
	{
		if(isThrownCoinHead()) 
		{
			cout << "H" << endl;
			headCounter++;
			counter++;
		}
		else 
		
		{
			cout << "T" << endl;
			headCounter = 0;
			counter++;
		}
		if(headCounter==3) break;
	}
	cout << "it took " << counter << " flips" << endl;
}
bool isThrownCoinHead() {
return randomChance(0.5);
}