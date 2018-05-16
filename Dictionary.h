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
	Dictionary(ifstream file);
	void insertword(string line);
	bool wordexists(string word);
private:
	map<string, vector<string>> wands;
};