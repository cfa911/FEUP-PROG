#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Board
{
public:
	Board();
	Board(int x, int y);
	void replaceboard(vector<string> bfile);
	void printBoard();
	void insertWBoard(string word, size_t posx, size_t posy, char ori);
	void changechar(char s, size_t posx, size_t posy);
	vector<string> vec();
	size_t bsize();
	size_t bssize();
	string wup(int x, int y);
	string wdown(int x, int y);
	string wleft(int x, int y);
	string wright(int x, int y);
	bool spaceoccupied(string word, int x, int y, char orientation);
	void fill();
	
private:
	vector<string> board;
};