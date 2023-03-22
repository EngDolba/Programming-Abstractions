/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include "simpio.h"
using namespace std;
void drawSerpinskiTrixugolnik(int fractalOrder,double sideLength,GWindow& gw,GPoint p);

int main() {
	GWindow gw;
	int fractalOrder = getInteger("Enter Fractal Order Number: ");
	int sideLength = getInteger("Enter Side Length: ");
	GPoint p(gw.getWidth()/2-sideLength/2,gw.getHeight()/2+sideLength/2);
	drawSerpinskiTrixugolnik(fractalOrder,sideLength,gw,p);
	return 0;
}
void drawSerpinskiTrixugolnik(int fractalOrder,double sideLength,GWindow& gw,GPoint p)
{
	
	
	int degree = 0;
	if(fractalOrder==0)
	{
		p = gw.drawPolarLine(p,sideLength,60);
		p = gw.drawPolarLine(p,sideLength,-60);
		p = gw.drawPolarLine(p,sideLength,180);
		return;
	}
	drawSerpinskiTrixugolnik(fractalOrder-1,sideLength/2,gw,p);
	p = gw.drawPolarLine(p,sideLength/2,60); // aq ver vipove funqcia romelic daxatvis gareshe gauketebda p-s shesabamis transformacias torem daxatva arafer shuashia
	drawSerpinskiTrixugolnik(fractalOrder-1,sideLength/2,gw,p);
	p = gw.drawPolarLine(p,sideLength/2,60);
	p = gw.drawPolarLine(p,sideLength,-60);
	p = gw.drawPolarLine(p,sideLength/2,180);
	drawSerpinskiTrixugolnik(fractalOrder-1,sideLength/2,gw,p);
}