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
	Puzzle(string file);
private:
	Cwords solution;
	Cwords player;
};