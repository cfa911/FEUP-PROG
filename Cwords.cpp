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
	if (this->palex.find(word) == this->palex.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Cwords::wordfits(string word, int x, int y, char orientation) {
	char a = toupper(orientation);
	size_t line_s = this->cword.at(0).size(), colun_s = this->cword.size();
	switch (a)
	{
	case 'V':
	{
		if (word.size() > colun_s / 2)
		{
			return false;
		}
		else
		{
			if (colun_s - y >= word.size())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		break;
	}
	case 'H':
	{
		size_t trues = line_s / 2;
		if (trues < word.size())
		{
			return false;
		}
		else
		{
			if (trues - (x -1) >= word.size())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		break;
	}
	default:
		cout << "Invalid orientation" << endl;
		return false;
		break;
	}
}
bool Cwords::spaceocuppied(string word, int x, int y, char orientation) {
	size_t line_s = this->cword.at(0).size() / 2;
	size_t posx = (line_s - (x - 1)) * 2 + 1, posy = y + 1;
	switch (toupper(orientation))
	{
	case 'H': {



		break;
	}
	case 'V': {
		break;
	}
	default:
		break;
	}
}

void Cwords::insertword(string xyo, string word) {
	if (wordexists(word) == true)
	{
		cout << "The word already exists" << endl;
		return;
	}
	else
	{
		char a = xyo[0], A = xyo[1], o = xyo[2];
		int b = a -'a', B = a - 'A';
		if (wordfits(word,b,B,o) == false)
		{
			cout << "The word doesn't fit in the crossword" << endl;
			return;
		}
		else
		{

		}
	}
}
	