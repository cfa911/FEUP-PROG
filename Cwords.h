#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Cwords
{
public:
	Cwords(int x,int y);
	vector<string> emptycword(int x, int y);
	void printcword();
	//Cwords();

private:
	vector<string> cword;
};

