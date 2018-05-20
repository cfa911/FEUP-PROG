#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Board.h"

using namespace std;



class Cwords
{
public:
	Cwords(int x,int y, string filename);//Creates a new Crosswords
	Cwords(string filename, string player);//Creates a empty Crosswords with same dimensions as puzzle
	Cwords(string filename);//Creates a new Crosswords from a file
	Cwords();
	void printboard();//Prints the Crossword
	bool wordexists(string word);//Checks if a word already exists in the Crossword
	bool wordfits(string word, int x, int y, char orientation);// Checks if a word we want to place fits in the board
	void insertword(string xyo, string word);//Inserts word in the Crossword
	bool adjup(int x, int y);//Checks if the is a word adjecent above
	bool adjdown(int x, int y);//Checks if the is a word adjecent below
	bool adjleft(int x, int y);//Checks if the is a word adjecent to the left
	bool adjright(int x, int y);//Checks if the is a word adjecent to the right
	void removeword(string word);//Removes word from the Crossword
	void finishboard();// Fills the remaining spaces of the board
	void saveinfile(string filename, string player);
	void saveinfile(string filename);//Saves the Crossword in a file
	string dictionaryname();//Return the name of the dictionary used
	string spacetofill(string xyo);//returns a string of the space we want to place a word
	string possibleword(string xyo);//returns a word to check if it exists in the dictionary and if it can be inserted in the Crossword
	bool cwordsisfull();
	Board getBoard();
	~Cwords();//Destructor
	map<string, string> getWordsPos();

private:
	string dictionary;//Name of the dictionary used
	Board board;//the board of the crossword
	map<string,string> palex;//Existing words(key) and their positions(value) 
};

