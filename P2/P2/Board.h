#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class Board
{
public:
	Board();
	Board(int x, int y);//Creates an empty board with lenght = y and width = x
	void replaceboard(vector<string> bfile); // replace an empty board with an already built board
	void printBoard();//Prints the board
	void insertWBoard(string word, size_t posx, size_t posy, char ori);//Insert a word in the board
	void changechar(char s, size_t posx, size_t posy);// Changes a char in a certain position 
	vector<string> vec(); // return the board
	size_t bsize(); // returns the size of the vector holding the board
	size_t bssize();// return the size of the strings that make the board
	string wup(int x, int y);// return the word above a position
	string wdown(int x, int y);// return the word below a position
	string wleft(int x, int y);// return the word left of a position
	string wright(int x, int y);// return the word right of a position
	string wdown2(int x, int y);//variation of down
	string wright2(int x, int y);//variation of right
	string wdown3(int x, int y);// second variation of down
	string wright3(int x, int y);// second variation of right
	bool spaceoccupied(string word, int x, int y, char orientation);//Check if the space where we want to place a word is not ocuppied
	void fill();//fill empty spaces with a #
	vector<string> getVector();

	
private:
	vector<string> board;//Board of the puzzle
};