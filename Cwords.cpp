#include "Cwords.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream>

using namespace std;

bool cmpboards(Board board1, Board board2) {
	vector<string> a = board1.vec(), b = board2.vec();
	for (size_t i = 0; i < a.size(); i++)
	{
		if (a[i].compare(b[i]) != 0)
		{
			return false;
		}
	}
	return true;
}
Cwords::Cwords(int x, int y)
{
	board = Board(x,y);
}

/*Cwords::Cwords(ifstream file) {
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
}*/

void Cwords::printboard() {
	board.printBoard();
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
	size_t line_s = board.bssize(), colun_s = board.bsize();
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
			if (board.spaceoccupied(word, b, B, o) == true)
			{
				cout << "The could not be placed in those coordinates" << endl;
				return;
			}
			else
			{
				size_t posx = b * 2 + 2, posy = B + 1;
				Board temp = this->board;
				this->board.insertWBoard(word, posx, posy, o);
				if (cmpboards(temp,board) == true)
				{
					return;
				}
				else
				{
					palex.insert(std::pair<string, string>(word, xyo));
				}
			}
		}
	}
}

bool  Cwords::adjup(int x, int y) {
	string a;
	if (y - 1 == 0)
	{
		return false;
	}
	else
	{
		a = board.wup(x, y);
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
	if (y == board.bsize() - 1)
	{
		return false;
	}
	else
	{
		a = board.wdown(x, y);
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
		a = board.wleft(x, y);
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
	if (x == board.bssize() - 1)
	{
		return false;
	}
	else
	{
		a = board.wright(x, y);
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


void Cwords::removeword(string word) {
	if (wordexists(word) == false)
	{
		cout << "The word doesn't exist in the crossword" << endl;
		return;
	}
	else
	{
		string xyo = palex.find(word)->second;
		char a = xyo[0], A = xyo[1], o = xyo[2], s = '.';
		int b = a - 'a', B = A - 'A';
		size_t posx = b * 2 + 2, posy = B + 1;
		string temp;
		switch (o)
		{
		case 'V': {
			if (word.size() == board.bsize() - 1)
			{
				for (size_t i = 0; i < word.size(); i++)
				{
					temp = board.wleft((int)posx, (int)posy + i) + word[i] + board.wright((int)posx, (int)posy + i);
					if (wordexists(temp) == false)
					{
						board.changechar(s, posx, posy + i);
					}
				}
				palex.erase(word);
				return;
			}
			else if (B == 0)
			{
				if (adjright(posx, posy + word.size()) == false && adjdown(posx, posy + word.size()) == false && adjleft(posx, posy + word.size()) == false)
				{
					for (size_t i = 0; i < word.size(); i++)
					{
						temp = board.wleft((int)posx, (int)posy + i) + word[i] + board.wright((int)posx, (int)posy + i);
						if (wordexists(temp) == false)
						{
							board.changechar(s, posx, posy + i);
						}
					}
					board.changechar(s, posx, posy + word.size());
					palex.erase(word);
					return;
				}
				else
				{
					for (size_t i = 0; i < word.size(); i++)
					{
						temp = board.wleft((int)posx, (int)posy + i) + word[i] + board.wright((int)posx, (int)posy + i);
						if (wordexists(temp) == false)
						{
							board.changechar(s, posx, posy + i);
						}
					}
					palex.erase(word);
					return;
				}

			}
			else if (board.bsize() - posy == word.size())
			{
				if (adjright(posx, posy - 1) == false && adjdown(posx, posy - 1) == false && adjleft(posx, posy - 1) == false)
				{
					for (size_t i = 0; i < word.size(); i++)
					{
						temp = board.wleft((int)posx, (int)posy + i) + word[i] + board.wright((int)posx, (int)posy + i);
						if (wordexists(temp) == false)
						{
							board.changechar(s, posx, posy + i);
						}
					}
					board.changechar(s, posx, posy - 1);
					palex.erase(word);
					return;
				}
				else
				{
					for (size_t i = 0; i < word.size(); i++)
					{
						temp = board.wleft((int)posx, (int)posy + i) + word[i] + board.wright((int)posx, (int)posy + i);
						if (wordexists(temp) == false)
						{
							board.changechar(s, posx, posy + i);
						}
					}
					palex.erase(word);
					return;
				}
			}
			else
			{
				if (adjright(posx, posy - 1) == false && adjdown(posx, posy - 1) == false && adjleft(posx, posy - 1) == false)
				{
					board.changechar(s, posx, posy - 1);
				}
				if (adjright(posx, posy + word.size()) == false && adjdown(posx, posy + word.size()) == false && adjleft(posx, posy + word.size()) == false)
				{
					board.changechar(s, posx, posy + word.size());
				}
				for (size_t i = 0; i < word.size(); i++)
				{
					temp = board.wleft((int)posx, (int)posy + i) + word[i] + board.wright((int)posx, (int)posy + i);
					if (wordexists(temp) == false)
					{
						board.changechar(s, posx, posy + i);
					}
				}
				palex.erase(word);
				return;
			}
			break;
		}
		case 'H': {
			size_t linex = (board.bssize() - 1) / 2;
			if (linex == word.size())
			{
				for (size_t i = 0; i < word.size(); i++)
				{
					temp = board.wup((int)posx + i*2, (int)posy) + word[i] + board.wdown((int)posx + i*2, (int)posy);
					if (wordexists(temp) == false)
					{
						board.changechar(s, posx + i*2, posy);
					}
				}
				palex.erase(word);
			}
			else if (b == 0)
			{
				if (adjright(posx + word.size()*2, posy) == false && adjdown(posx + word.size() * 2, posy) == false && adjup(posx + word.size() * 2, posy) == false)
				{
					for (size_t i = 0; i < word.size(); i++)
					{
						temp = board.wup((int)posx + i * 2, (int)posy) + word[i] + board.wdown((int)posx + i * 2, (int)posy);
						if (wordexists(temp) == false)
						{
							board.changechar(s, posx + i * 2, posy);
						}
					}
					board.changechar(s, posx + word.size() * 2, posy);
					palex.erase(word);
					return;
				}
				else
				{
					for (size_t i = 0; i < word.size(); i++)
					{
						temp = board.wup((int)posx + i * 2, (int)posy) + word[i] + board.wdown((int)posx + i * 2, (int)posy);
						if (wordexists(temp) == false)
						{
							board.changechar(s, posx + i * 2, posy);
						}
					}
					palex.erase(word);
					return;
				}
			}
			else if (linex - b == word.size())
			{
				if (adjleft(posx - 2, posy) == false && adjdown(posx - 2, posy) == false && adjup(posx - 2, posy) == false)
				{
					for (size_t i = 0; i < word.size(); i++)
					{
						temp = board.wup((int)posx + i * 2, (int)posy) + word[i] + board.wdown((int)posx + i * 2, (int)posy);
						if (wordexists(temp) == false)
						{
							board.changechar(s, posx + i * 2, posy);
						}
					}
					board.changechar(s, posx - 2, posy);
					palex.erase(word);
					return;
				}
				else
				{
					for (size_t i = 0; i < word.size(); i++)
					{
						temp = board.wup((int)posx + i * 2, (int)posy) + word[i] + board.wdown((int)posx + i * 2, (int)posy);
						if (wordexists(temp) == false)
						{
							board.changechar(s, posx + i * 2, posy);
						}
					}
					palex.erase(word);
					return;
				}
			}
			else
			{
				if (adjleft(posx - 2, posy) == false && adjdown(posx - 2, posy) == false && adjup(posx - 2, posy) == false)
				{
					board.changechar(s, posx - 2, posy);
				}
				if (adjright(posx + word.size() * 2, posy) == false && adjdown(posx + word.size() * 2, posy) == false && adjup(posx + word.size() * 2, posy) == false)
				{
					board.changechar(s, posx + word.size() * 2, posy);
				}
				for (size_t i = 0; i < word.size(); i++)
				{
					temp = board.wup((int)posx + i * 2, (int)posy) + word[i] + board.wdown((int)posx + i * 2, (int)posy);
					if (wordexists(temp) == false)
					{
						board.changechar(s, posx + i * 2, posy);
					}
				}
				palex.erase(word);
				return;
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
}