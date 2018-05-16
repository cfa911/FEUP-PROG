#include "Cwords.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream>

using namespace std;

Cwords::Cwords(int x, int y)
{
	this->cword = emptycword(x, y);
}

Cwords::Cwords(ifstream file) {
	string a;
	size_t j = 0;
	while (getline(file, a))
	{
		if (a[0] >= 'A' && a[0] <= 'Z')
		{
			cword.push_back(a);
		}
		else if (a[0] >= 'a' && a[0] <= 'z')
		{
			if (j == 0)
			{
				j++;
			}
			else
			{
				string ori;
				size_t npos = a.find_first_of(" ");
				ori = a.substr(0, npos);
				a.erase(0, npos + 1);
				palex.insert(std::pair<string, string>(a, ori));
			}
		}
		else
		{
		}
	}
}

vector<string> Cwords::emptycword(int x, int y)
{
	vector<string> crossword;
	crossword.resize(y + 1);
	string a;
	int b = x * 2 + 1, d = 0;
	char c = 'a', C = 'A';
	for (size_t i = 0; i < y + 1; i++)
	{
		if (i == 0)
		{
			for (size_t j = 0; j < b; j++)
			{
				if (j == 0)
				{
					a = a + " ";
				}
				else if (j % 2 != 0)
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
			for (size_t j = 0; j < b; j++)
			{
				if (j == 0)
				{
					a = a + C;
				}
				else
				{
					if (j % 2 != 0)
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
		if (word.size() > colun_s - 1)
		{
			return false;
		}
		else
		{
			if (colun_s - (y + 1) >= word.size())
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
		size_t trues = (line_s - 1) / 2;
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
	size_t posx = x*2 + 2, posy = y + 1;
	switch (toupper(orientation))
	{
	case 'H': {
		for (size_t i = 0; i < word.size(); i++)
		{
			if (cword.at(posy).at(posx + i*2) == '.')
			{
				continue;
			}
			else
			{
				if (cword.at(posy).at(posx + i * 2) == '#')
				{
					return true;
				}
				else if (cword.at(posy).at(posx + i * 2) >= 'A' && cword.at(posy).at(posx + i * 2) >= 'Z')
				{
					if (cword.at(posy).at(posx + i * 2) == word.at(i))
					{
						continue;
					}
					else
					{
						return true;
					}
				}
			}
		}
		return false;
		break;
	}
	case 'V': {
		for (size_t i = 0; i < word.size(); i++)
		{
			if (cword.at(posy + i).at(posx) == '.')
			{
				continue;
			}
			else
			{
				if (cword.at(posy + i).at(posx) == '#')
				{
					return true;
				}
				else if (cword.at(posy +  i).at(posx) >= 'A' && cword.at(posy + i).at(posx) >= 'Z')
				{
					if (cword.at(posy + i).at(posx) == word.at(i))
					{
						continue;
					}
					else
					{
						return true;
					}
				}
			}
		}
		return false;
		break;
	}
	default:
		return true;
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
		char a = xyo[0], A = xyo[1], o = toupper(xyo[2]);
		int b = a - 'a', B = A - 'A';
		if (wordfits(word, b, B, o) == false)
		{
			cout << "The word doesn't fit in the crossword" << endl;
			return;
		}
		else
		{
			if (spaceocuppied(word, b, B, o) == true)
			{
				cout << "The could not be placed in those coordinates" << endl;
				return;
			}
			else
			{
				size_t posx = b * 2 + 2, posy = B + 1;
				size_t linex = (cword.at(0).size() - 1) / 2;
				switch (o)
				{
				case 'V': {
					if (word.size() == cword.size() - 1)
					{
						for (size_t i = 0; i < word.size(); i++)
						{
							cword.at(posy + i).at(posx) = word.at(i);
							palex.insert(std::pair<string, string>(word,xyo));
						}
					}
					else if (B == 0)
					{
						if (cword.at(posy + word.size()).at(posx) != '.' && cword.at(posy + word.size()).at(posx) != '#')
						{
							cout << "Could not place the word" << endl;
							return;
						}
						else
						{
							cword.at(posy + word.size()).at(posx) = '#';
							for (size_t i = 0; i < word.size(); i++)
							{
								cword.at(posy + i).at(posx) = word.at(i);
							}
							palex.insert(std::pair<string, string>(word, xyo));
						}

					}
					else if (cword.size() - posy == word.size())
					{
						if (cword.at(posy - 1).at(posx) != '.' && cword.at(posy - 1).at(posx) != '#')
						{
							cout << "Could not place the word" << endl;
							return;
						}
						else
						{
							cword.at(posy - 1).at(posx) = '#';
							for (size_t i = 0; i < word.size(); i++)
							{
								cword.at(posy + i).at(posx) = word.at(i);
							}
							palex.insert(std::pair<string, string>(word, xyo));
						}
					}
					else
					{
						if ((cword.at(posy - 1).at(posx) != '.' && cword.at(posy - 1).at(posx) != '#') || (cword.at(posy + word.size()).at(posx) != '.' && cword.at(posy + word.size()).at(posx) != '#'))
						{
							cout << "Could not place the word" << endl;
							return;
						}
						else
						{
							cword.at(posy - 1).at(posx) = '#';
							cword.at(posy + word.size()).at(posx) = '#';
							for (size_t i = 0; i < word.size(); i++)
							{
								cword.at(posy + i).at(posx) = word.at(i);
							}
							palex.insert(std::pair<string, string>(word, xyo));
						}
					}
					break;
				}
				case 'H': {
					if (linex == word.size())
					{
						for (size_t i = 0; i < word.size(); i++)
						{
							cword.at(posy).at(posx + i * 2) = word.at(i);
						}
						palex.insert(std::pair<string, string>(word, xyo));
					}
					else if (b == 0)
					{
						if ((cword.at(posy).at(posx + word.size() * 2) != '.') && (cword.at(posy).at(posx + word.size() * 2) != '#'))
						{
							cout << "Could not place the word" << endl;
							return;
						}
						else
						{
							cword.at(posy).at(posx + word.size() * 2) = '#';
							for (size_t i = 0; i < word.size(); i++)
							{
								cword.at(posy).at(posx + i * 2) = word.at(i);
							}
							palex.insert(std::pair<string, string>(word, xyo));
						}
					}
					else if (linex - b == word.size())
					{
						if ((cword.at(posy).at(posx - 1 * 2) != '.') && (cword.at(posy).at(posx - 1 * 2) != '#'))
						{
							cout << "Could not place the word" << endl;
							return;
						}
						else
						{
							cword.at(posy).at(posx - 1 * 2) = '#';
							for (size_t i = 0; i < word.size(); i++)
							{
								cword.at(posy).at(posx + i * 2) = word.at(i);
							}
							palex.insert(std::pair<string, string>(word, xyo));
						}
					}
					else
					{
						if (((cword.at(posy).at(posx - 1 * 2) != '.') && (cword.at(posy).at(posx - 1 * 2) != '#')) || ((cword.at(posy).at(posx + word.size() * 2) != '.') && (cword.at(posy).at(posx + word.size() * 2) != '#')))
						{
							cout << "Could not place the word" << endl;
							return;
						}
						else
						{
							cword.at(posy).at(posx + word.size() * 2) = '#';
							cword.at(posy).at(posx - 1 * 2) = '#';
							for (size_t i = 0; i < word.size(); i++)
							{
								cword.at(posy).at(posx + i * 2) = word.at(i);
							}
							palex.insert(std::pair<string, string>(word, xyo));
						}
					}
				}
				default:
					break;
				}
			}
		}
	}
}
void invertstring(string &word) {
	size_t i = 0;
	char temp;
	while (i <= word.size() - 1 - i)
	{
		temp = word.at(word.size() - 1 - i);
		word.at(word.size() - 1 - i) = word.at(i);
		word.at(i) = temp;
		i++;
	}
	return;
}

bool  Cwords::adjup(int x, int y) {
	string a;
	if (y - 1 == 0)
	{
		return false;
	}
	else
	{
		size_t i = y - 1;
		while (i >= 1 && cword.at(i).at(y) != '#')
		{
			a = a + cword.at(i).at(x);
			i--;
		}
		invertstring(a);
		if (wordexists(a) == false)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}
bool  Cwords::adjdown( int x, int y) {
	string a;
	if (y == cword.size() - 1)
	{
		return false;
	}
	else
	{
		size_t i = y + 1;
		while (i <= cword.size() - 1 && cword.at(i).at(x) != '#')
		{
			a = a + cword.at(i).at(x);
			i++;
		}
		if (wordexists(a) == false)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

bool  Cwords::adjleft( int x, int y) {
	string a;
	if (x - 2 == 0)
	{
		return false;
	}
	else
	{
		size_t i = x - 2;
		while (i >= 2 && cword.at(y).at(i) != '#')
		{
			a = a + cword.at(y).at(i);
			i = i - 2;
		}
		invertstring(a);
		if (wordexists(a) == false)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}
bool  Cwords::adjright( int x, int y) {
	string a;
	if (x == cword.at(0).size() - 1)
	{
		return false;
	}
	else
	{
		size_t i = x + 2;
		while (i <= cword.at(0).size() - 1 && cword.at(y).at(i) != '#')
		{
			a = a + cword.at(y).at(i);
			i = i + 2;
		}
		if (wordexists(a) == false)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

void Cwords::fillempty() {
	for (size_t i = 1; i < cword.size(); i++)
	{
		for (size_t j = 0; j < cword.at(0).size(); j++)
		{
			if (cword.at(i).at(j) == '.')
			{
				cword.at(i).at(j) = '#';
			}
		}
	}
	return;
}

bool Cwords::cwordisfull() {
	for (size_t i = 1; i < cword.size(); i++)
	{
		for (size_t j = 0; j < cword.at(i).size(); j++)
		{
			if ((cword.at(i).at(j) < 'A' || cword.at(i).at(j) < 'Z') || cword.at(i).at(j) != ' ' || cword.at(i).at(j) != '#')
			{
				return false;
			}
		}
	}
	return true;
}

void Cwords::worddisappear(string word) {
	if (this->palex.find(word) == this->palex.end())
	{
		cout << "Word doesn't exist" << endl;
		return;
	}
	else
	{
		string xyo = this->palex.find(word)->second;
		int a = xyo[0] - 'a', A = xyo[1] - 'A';
		size_t posx = a * 2 + 2, posy = A + 1;
		char o = xyo[2];
		switch (o)
		{
		case 'V': {
			for (size_t i = 0; i < word.size(); i++)
			{
				cword.at(posy + i).at(posx) = '.';
			}
			break;
		}
		case 'H': {
			for (size_t i = 0; i < word.size(); i++)
			{
				cword.at(posy).at(posx + i * 2) = '.';
			}
			break;
		}
		default:
			break;
		}
	}
	return; 
}
void Cwords::worddreappear(string word) {
	if (this->palex.find(word) == this->palex.end())
	{
		cout << "Word doesn't exist" << endl;
		return;
	}
	else
	{
		string xyo = this->palex.find(word)->second;
		int a = xyo[0] - 'a', A = xyo[1] - 'A';
		size_t posx = a * 2 + 2, posy = A + 1;
		char o = xyo[2];
		switch (o)
		{
		case 'V': {
			for (size_t i = 0; i < word.size(); i++)
			{
				cword.at(posy + i).at(posx) = word.at(i);
			}
			break;
		}
		case 'H': {
			for (size_t i = 0; i < word.size(); i++)
			{
				cword.at(posy).at(posx + i * 2) = word.at(i);
			}
			break;
		}
		default:
			break;
		}
	}
	return;
}

void Cwords::removeword(string word) {
	if (wordexists(word) == false)
	{
		cout << "The word doesn't exist in the crossword" << endl;
		return;
	}
	else
	{
		string xyo = palex.find(word)->second;
		char a = xyo[0], A = xyo[1], o = xyo[2];
		int b = a - 'a', B = A - 'A';
		size_t posx = b * 2 + 2, posy = B + 1;
		switch (o)
		{
		case 'V': {
			if (word.size() == cword.size() - 1)
			{
				for (size_t i = 0; i < word.size(); i++)
				{
					cword.at(posy + i).at(posx) = '.';
					return;
				}
				palex.erase(word);
			}
			else if (B == 0)
			{
				if (adjright(posx, posy + word.size()) == false && adjdown(posx, posy + word.size()) == false && adjleft(posx, posy + word.size()) == false)
				{
					for (size_t i = 0; i <= word.size(); i++)
					{
						cword.at(posy + i).at(posx) = '.';
					}
					palex.erase(word);
					return;
				}
				else
				{
					for (size_t i = 0; i < word.size(); i++)
					{
						cword.at(posy + i).at(posx) = '.';
					}
					palex.erase(word);
					return;
				}

			}
			else if (cword.size() - posy == word.size())
			{
				if (adjright(posx, posy - 1) == false && adjdown(posx, posy - 1) == false && adjleft(posx, posy - 1) == false)
				{
					for (size_t i = 0; i <= word.size(); i++)
					{
						cword.at(posy - 1 + i).at(posx) = '.';
					}
					palex.erase(word);
					return;
				}
				else
				{
					for (size_t i = 0; i < word.size(); i++)
					{
						cword.at(posy + i).at(posx) = '.';
					}
					palex.erase(word);
					return;
				}
			}
			else
			{
				if (adjright(posx, posy - 1) == false && adjdown(posx, posy - 1) == false && adjleft(posx, posy - 1) == false)
				{
					for (size_t i = 0; i <= word.size(); i++)
					{
						cword.at(posy - 1 + i).at(posx) = '.';
					}
					if (adjright(posx, posy + word.size()) == false && adjdown(posx, posy + word.size()) == false && adjleft(posx, posy + word.size()) == false)
					{
						cword.at(posy + word.size()).at(posx) = '.';
					}
					else
					{
					}
					palex.erase(word);
					return;
				}
				else
				{
					for (size_t i = 0; i < word.size(); i++)
					{
						cword.at(posy + i).at(posx) = '.';
					}
					if (adjright(posx, posy + word.size()) == false && adjdown(posx, posy + word.size()) == false && adjleft(posx, posy + word.size()) == false)
					{
						cword.at(posy + word.size()).at(posx) = '.';
					}
					else
					{
					}
					palex.erase(word);
					return;
				}
			}
			break;
		}
		case 'H': {
			size_t linex = (cword.at(0).size() - 1) / 2;
			if (linex == word.size())
			{
				for (size_t i = 0; i < word.size(); i++)
				{
					cword.at(posy).at(posx + i) = '.';
				}
				palex.erase(word);
			}
			else if (b == 0)
			{
				if (adjright(posx + word.size()*2, posy) == false && adjdown(posx + word.size() * 2, posy) == false && adjup(posx + word.size() * 2, posy) == false)
				{
					for (size_t i = 0; i <= word.size(); i++)
					{
						cword.at(posy).at(posx + i*2) = '.';
					}
					palex.erase(word);
					return;
				}
				else
				{
					for (size_t i = 0; i < word.size(); i++)
					{
						cword.at(posy).at(posx + i*2) = '.';
					}
					palex.erase(word);
					return;
				}
			}
			else if (linex - b == word.size())
			{
				if (adjleft(posx - 2, posy) == false && adjdown(posx - 2, posy) == false && adjup(posx - 2, posy) == false)
				{
					for (size_t i = 0; i <= word.size(); i++)
					{
						cword.at(posy).at(posx + i * 2 - 2) = '.';
					}
					palex.erase(word);
					return;
				}
				else
				{
					for (size_t i = 0; i < word.size(); i++)
					{
						cword.at(posy).at(posx + i * 2) = '.';
					}
					palex.erase(word);
					return;
				}
			}
			else
			{
				if (adjleft(posx - 2, posy) == false && adjdown(posx - 2, posy) == false && adjup(posx - 2, posy) == false)
				{
					for (size_t i = 0; i <= word.size(); i++)
					{
						cword.at(posy).at(posx + i * 2 - 2) = '.';
					}
					if (adjright(posx + word.size() * 2, posy) == false && adjdown(posx + word.size() * 2, posy) == false && adjup(posx + word.size() * 2, posy) == false)
					{
						cword.at(posy).at(posx + word.size() * 2) = '.';
						return;
					}
					else
					{
					}
					palex.erase(word);
					return;
				}
				else
				{
					for (size_t i = 0; i < word.size(); i++)
					{
						cword.at(posy).at(posx + i * 2) = '.';
					}
					if (adjright(posx + word.size() * 2, posy) == false && adjdown(posx + word.size() * 2, posy) == false && adjup(posx + word.size() * 2, posy) == false)
					{
						cword.at(posy).at(posx + word.size() * 2) = '.';
						return;
					}
					else
					{
					}
					palex.erase(word);
					return;
				}
			}
			break;
		}
		default:
			break;
		}
	}
}
	
Cwords::~Cwords() {
	palex.erase(palex.begin(), palex.end());
	cword.erase(cword.begin(), cword.end());
}