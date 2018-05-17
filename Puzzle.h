#pragma once
#include <iostream>
#include <vector>
#include "Cwords.h"
#include <fstream>

using namespace std;

class Puzzle
{
public:
	Puzzle();
	Puzzle(ifstream file);
private:
	Cwords solution;
	Cwords player;
};