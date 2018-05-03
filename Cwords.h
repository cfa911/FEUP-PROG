#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;



class Cwords
{
public:
	Cwords(int x,int y);
	vector<string> emptycword(int x, int y);
	void printcword();
	bool wordexists(string word);
	bool wordfits(string word, int x, int y, char orientation);
	bool spaceocuppied(string word, int x, int y, char orientation);
	void insertword(string xyo, string word);
	
	//Cwords();

private:
	vector<string> cword;
	map<string,string> palex;
};

