#include "Cwords.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

Cwords::Cwords(int x, int y)
{
	this->cword = emptycword(x, y);
}

vector<string> Cwords::emptycword(int x, int y)
{
	vector<string> crossword;
	crossword.resize(y + 1);
	string a;
	int b = x * 2, d = 0;
	char c = 'a', C = 'A';
	for (size_t i = 0; i < y + 1; i++)
	{
		if (i == 0)
		{
			for (size_t j = 0; j < b; j++)
			{
				if (j % 2 == 0)
				{
					a = a + " ";
				}
				else
				{
					c = c + d;
					a = a + c;
					d = 1;
				}
				
			}
			crossword[i] = a;
			a.clear();
		}
		else
		{
			d = 0;
			for (size_t j = 0; j < x * 2; j++)
			{
				if (j == 0)
				{
					a = a + C;
				}
				else
				{
					if (j % 2 == 0)
					{
						a = a + " ";
					}
					else
					{
						a = a + ".";
					}
				}
				d = 1;
			}
			crossword[i] = a;
			a.clear();
			C++;
		}
	}
	return crossword;
}

void Cwords::printcword() {
	for (size_t i = 0; i < this->cword.size(); i++)
	{
		cout << this->cword[i] << endl;
	}
}

bool Cwords::wordexists(string word) {
	for (size_t i = 0; i < this->presw.size(); i++)
	{
		if (word == this->presw.at(i))
		{
			return true;
		}
	}
	return false;
}

bool Cwords::wordfits(string word, int x, int y) {
	if (word.size() > (this->cword.at(0).size() / 2) && word.size() > (this->cword.size()))
	{
		return false;
	}
	else
	{

	}
}
	