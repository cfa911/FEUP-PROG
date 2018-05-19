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
	Cwords(int x,int y, string filename);
	Cwords(string filename);
	void printboard();
	bool wordexists(string word);
	bool wordfits(string word, int x, int y, char orientation);
	void insertword(string xyo, string word);
	bool adjup(int x, int y);
	bool adjdown(int x, int y);
	bool adjleft(int x, int y);
	bool adjright(int x, int y);
	void removeword(string word);
	void finishboard();
	void saveinfile(string filename);
	string dictionaryname();
	~Cwords();

private:
	string dictionary;
	Board board;
	map<string,string> palex;
};

