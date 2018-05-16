#include "Puzzle.h"
#include "Cwords.h"
#include "Dictionary.h"
#include <iostream>
#include <fstream> 

using namespace std;

int main() {
	Cwords a(15, 15);
	a.printboard();
	string word, ori;
	for (size_t i = 0; i < 6; i++)
	{
		cin >> word;
		cin >> ori;
		a.insertword(ori, word);
		a.printboard();
	}
	for (size_t i = 0; i < 3; i++)
	{
		cin >> word;
		a.removeword(word);
	}
	a.printboard();
	return 0;
}