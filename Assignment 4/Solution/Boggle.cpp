/*
* File: Boggle.cpp
* ----------------
* Name: [TODO: enter name here]
* Section: [TODO: enter section leader here]
* This file is the main starter file for Assignment #4, Boggle.
* [TODO: extend the documentation]
*/

#include <iostream>
#include "gboggle.h"
#include "set.h"
#include "vector.h"
#include "grid.h"
#include "strlib.h"
#include <string>
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

/*const string STANDARD_CUBES[16]  = {
"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
"AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
"DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
"EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
}; */
const string STANDARD_CUBES[16]  = {
	"A", "R", "M", "I",
	"AOOTTW", "CIMOTU", "DEILRX", "E", //es shevcvale da dzveli kombinacia ar maxsovs magram ra mnishvneloba aqvs
	"DISTTY", "EEGHNW", "EEINSU", "S",
	"EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
string STANDARD_CUBES2[16]  = {
	"A", "R", "M", "I",
	"AOOTTW", "CIMOTU", "DEILRX", "E", 
	"DISTTY", "EEGHNW", "EEINSU", "S",
	"EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
Lexicon lex("EnglishWords.dat");
const string BIG_BOGGLE_CUBES[25]  = {
	"AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
	"AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
	"CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
	"DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
	"FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};
Grid<char> table(4,4);

/* Function prototypes */
void game();
struct pointT;
void welcome();
void giveInstructions();
bool isGoodWord(string str,Set<string>& usedWords,Grid<bool>& usedCells);
void generateTable();
void computerTurn(string& str,Grid<bool> usedCells,Set<pointT> neighborPoints,Set<string>& foundWords);
int cmp(pointT p1, pointT p2);
void userTurn(Set<string>& enteredWords,int &userPoints);
bool isConnected(pointT p1,pointT p2,Grid<bool>& usedCells);
Set<pointT>  findAllNeighbors(pointT p,Grid<bool>& usedCells);
Vector<char> chooseOneWordFromEachCube();
void RandomiseCubesInTable(Vector<char>& letters);
Set<pointT> findAllPoints(char ch);
void fillTable(Vector<char>& letters);
bool isValidInput(string str,Grid<bool>& usedCells);
void doGraphicPartOfGeneratingTable(Vector<char>& letters);
struct pointT{
	int x;
	int y;

	pointT(int xValue = 0, int yValue = 0){
		x = xValue;
		y = yValue;
	}
};

/* Main program */
int main() {
	GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
	initGBoggle(gw);
	welcome();
	giveInstructions();
	while(true)
	{
		string line = getLine("would you like to Enter Combinations?: ");
		if(line=="Y")
		{
			for(int i = 0;i<16;i++)
			{
				string line1 = getLine("enter Combination number: " + i);
					STANDARD_CUBES2[i] = line1;
			}
		}
		game();
		while(true)
		{
			string line = getLine("do you wish to start again(Y or N): ");
			if(line=="N")
				return 0;
			if(line=="Y")
				break;
		}
	}  
	return 0;
}

/*
* Function: welcome
* Usage: welcome();
* -----------------
* Print out a cheery welcome message.
*/

void welcome() {
	cout << "Welcome!  You're about to play an intense game ";
	cout << "of mind-numbing Boggle.  The good news is that ";
	cout << "you might improve your vocabulary a bit.  The ";
	cout << "bad news is that you're probably going to lose ";
	cout << "miserably to this little dictionary-toting hunk ";
	cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
* Function: giveInstructions
* Usage: giveInstructions();
* --------------------------
* Print out the instructions for the user.
*/

void giveInstructions() {
	cout << endl;
	cout << "The boggle board is a grid onto which I ";
	cout << "I will randomly distribute cubes. These ";
	cout << "6-sided cubes have letters rather than ";
	cout << "numbers on the faces, creating a grid of ";
	cout << "letters on which you try to form words. ";
	cout << "You go first, entering all the words you can ";
	cout << "find that are formed by tracing adjoining ";
	cout << "letters. Two letters adjoin if they are next ";
	cout << "to each other horizontally, vertically, or ";
	cout << "diagonally. A letter can only be used once ";
	cout << "in each word. Words must be at least four ";
	cout << "letters long and can be counted only once. ";
	cout << "You score pointTs based on word length: a ";
	cout << "4-letter word is worth 1 pointT, 5-letters ";
	cout << "earn 2 pointTs, and so on. After your puny ";
	cout << "brain is exhausted, I, the supercomputer, ";
	cout << "will find all the remaining words and double ";
	cout << "or triple your paltry score." << endl << endl;
	cout << "Hit return when you're ready...";
	getLine();
}
void game()
{
	Set<string> enteredWords;
	int userPoints = 0;
	string str = "";
	generateTable();
	Grid<bool> usedCells(4,4);
	userTurn(enteredWords,userPoints);
	Set<pointT> neighborPoints(cmp);
	Set<string> foundWords;
	for(int i = 0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			pointT p(i,j);
			neighborPoints.add(p);
		}

		computerTurn(str,usedCells,neighborPoints,foundWords);
		cout << foundWords.toString() << endl;
		foreach(string str in foundWords)
		{
			recordWordForPlayer(str,COMPUTER);
		}

}
void generateTable()
{
	Vector<char> letters = chooseOneWordFromEachCube();
	RandomiseCubesInTable(letters);
	fillTable(letters);
	doGraphicPartOfGeneratingTable(letters);


}
Vector<char> chooseOneWordFromEachCube()
{
	Vector<char> chars;
	foreach(string str in STANDARD_CUBES2)
	{
		chars.add(str[randomInteger(0,str.size()-1)]);
	}
	return chars;
}
void RandomiseCubesInTable(Vector<char>& letters)

{
	for (int i = 0;i<letters.size(); i++)
	{
		int a = randomInteger(i,letters.size()-1);
		int temp = letters[i];
		letters[i] = letters[a];
		letters[a] = temp;
	}
}
void fillTable(Vector<char>& letters)
{
	for(int i = 0;i<4;i++)
		for(int j = 0;j<4;j++)
		{
			table[j][i] = letters[j+4*i];
		}
}

void doGraphicPartOfGeneratingTable(Vector<char>& letters)	
{
	drawBoard(4,4);
	for(int i = 0;i<4;i++)
		for(int j = 0;j<4;j++)
		{
			labelCube(j,i,letters[j+4*i]);
		}
}
void userTurn(Set<string>& enteredWords,int &userPoints)
{
	Set<string> usedWords;
	while(true)
	{
		string str = getLine("enter word,if there is not left any,enter empty string: ");
		str = toUpperCase(str);
		if(str.empty()) break;
		Grid<bool> usedCells(4,4);

		if(isGoodWord(str,usedWords,usedCells))
		{
			enteredWords.add(str);
			userPoints+= str.size()-3;
			usedWords.add(str);
			recordWordForPlayer(str,HUMAN);

		}
		else 
		{
			cout << "The string is not a word" << endl;
		}
	}
}
Set<pointT>  findAllNeighbors(pointT p,Grid<bool>& usedCells)
{
	Set<pointT> points(cmp);
	if(usedCells.inBounds(p.x+1,p.y) && usedCells[p.x+1][p.y]==false)
		points.add(pointT(p.x+1,p.y));
	if(usedCells.inBounds(p.x-1,p.y) && usedCells[p.x-1][p.y]==false)
		points.add(pointT(p.x-1,p.y));
	if(usedCells.inBounds(p.x,p.y+1) && usedCells[p.x][p.y+1]==false)
		points.add(pointT(p.x,p.y+1));
	if(usedCells.inBounds(p.x,p.y-1) && usedCells[p.x][p.y-1]==false)
		points.add(pointT(p.x,p.y-1));
	if(usedCells.inBounds(p.x+1,p.y+1) && usedCells[p.x+1][p.y+1]==false)
		points.add(pointT(p.x+1,p.y+1));
	if(usedCells.inBounds(p.x-1,p.y-1) && usedCells[p.x-1][p.y-1]==false)
		points.add(pointT(p.x-1,p.y-1));
	if(usedCells.inBounds(p.x+1,p.y-1) && usedCells[p.x+1][p.y-1]==false)
		points.add(pointT(p.x+1,p.y-1));
	if(usedCells.inBounds(p.x-1,p.y+1) && usedCells[p.x-1][p.y+1]==false)
		points.add(pointT(p.x-1,p.y+1));

	return points;
}
void computerTurn(string& str,Grid<bool> usedCells,Set<pointT> neighborPoints,Set<string>& foundWords)
{
	if(!lex.containsPrefix(str)) return;
	if(str.size()>4 && lex.contains(str))
	{
		foundWords.add(str);
	}
	foreach(pointT p in neighborPoints)
	{
		str+=table[p.x][p.y];
		usedCells[p.x][p.y]=true;
		computerTurn(str,usedCells,findAllNeighbors(p,usedCells),foundWords);
		str = str.substr(0,str.size()-1);
		usedCells[p.x][p.y]=false;
	}
}
int cmp(pointT p1, pointT p2){
	if(p1.x < p2.x){
		return -1;
	}else if(p1.x > p2.x){
		return 1;
	}else if(p1.y < p2.y){
		return -1;
	}else if(p1.y > p2.y){
		return 1;
	}
	return 0;
}
Set<pointT> findAllPoints(char ch)
{
	Set<pointT> points(cmp);
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			if(table[i][j]==ch)
			{
				points.add(pointT(i,j)); 

			}


			return points;
}
bool isConnected(pointT p1,pointT p2,Grid<bool>& usedCells)
{

	if(table.inBounds(p2.x,p2.y) && usedCells[p2.x][p2.y]==true) return false;


	if(p1.x+1==p2.x && p1.y==p2.y)
		return true;
	if(p1.x-1==p2.x && p1.y==p2.y)
		return true;
	if(p1.x==p2.x && p1.y+1==p2.y)
		return true;
	if(p1.x==p2.x && p1.y-1==p2.y)
		return true;
	if(p1.x+1==p2.x && p1.y+1==p2.y)
		return true;
	if(p1.x-1==p2.x && p1.y-1==p2.y)
		return true;
	if(p1.x+1==p2.x && p1.y-1==p2.y)
		return true;
	if(p1.x-1==p2.x && p1.y+1==p2.y)
		return true;
	return false;

}


bool isGoodWord(string str,Set<string>& usedWords,Grid<bool>& usedCells)
{
	if(str.size()<4)return false;
	if(usedWords.contains(str)) return false;
	if(!lex.contains(str))return false;
	if(!isValidInput(str,usedCells)) return false;
	return true;
}
bool isValidInput(string str,Grid<bool>& usedCells)
{

	if(str.size()==2)
	{
		foreach(pointT p1 in findAllPoints(str[0]))
			foreach(pointT p2 in findAllPoints(str[1]))
		{
			if(isConnected(p1,p2,usedCells))
			{
				usedCells[p1.x][p1.y]=true;
				usedCells[p2.x][p2.y]=true;
				return true;
			}
		}
		return false;
	}
	foreach(pointT p1 in findAllPoints(str[0]))
		foreach(pointT p2 in findAllPoints(str[1]))
	{
		if(isConnected(p1,p2,usedCells))
		{
			usedCells[p1.x][p1.y]=true;
			if(isValidInput(str.substr(1),usedCells)) return true;;
			usedCells[p1.x][p1.y]=false;
		}
	}

	return false;
}