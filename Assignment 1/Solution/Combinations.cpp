/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
using namespace std;

int factorial(int n);
int pascalTriangle(int c,int k);
int main() {
    return 0;
}
int factorial(int n)
{
	if(n==1) return 1;
	return n*factorial(n-1);
}
int pascalTriangle(int n,int k)
{
	if(n==0 && k==0) return 1;
	if(n==0) return 1;
	if(n==k) return 1;
	return pascalTriangle(n-1,k)+pascalTriangle(n-1,k+1);


}