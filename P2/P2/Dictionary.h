#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


class Dictionary
{
public:
	Dictionary();
	Dictionary(ifstream& file);
	void insertwords(ifstream& file);
	bool wordexists(string word);
	vector<string> help(string place);
	map<string, vector<string>> getMap();
private:
	map<string, vector<string>> wands;
};