#include "Board.h"
#include "Colors.h"

Board::Board()
{
}

Board::Board(int x, int y)
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
	board = crossword;
}
void Board::replaceboard(vector<string> bfile) {
	for (size_t i = 1; i < board.size(); i++)
	{
		board.at(i).erase(1, board.at(i).size() - 1);
		board.at(i) = board.at(i) + bfile.at(i - 1);
	}
}

void Board::printBoard() {
	for (int i = 0; i < board.size(); i++)
	{

		for (int j = 0; j <= board.at(i).size(); j++)
		{
			if (i == 0 || j == 0)
				setcolor(RED, BLACK);
			else if (board[i][j] == '#')
				setcolor(WHITE, BLACK);
			else
				setcolor(BLACK, WHITE);
			cout << board[i][j];
		}
		cout << endl;
	}
	setcolor(WHITE, BLACK);
	return;
}

void Board::insertWBoard(string word, size_t posx, size_t posy, char ori) {
	size_t linex = (board.at(0).size() - 1) / 2;
	switch (ori)
	{
	case 'V': {
		if (word.size() == board.size() - 1)
		{
			for (size_t i = 0; i < word.size(); i++)
			{
				board.at(posy + i).at(posx) = word.at(i);
			}
		}
		else if (posy == 1)
		{
			if (board.at(posy + word.size()).at(posx) != '.' && board.at(posy + word.size()).at(posx) != '#')
			{
				cout << "Could not place the word" << endl;
				return;
			}
			else
			{
				board.at(posy + word.size()).at(posx) = '#';
				for (size_t i = 0; i < word.size(); i++)
				{
					board.at(posy + i).at(posx) = word.at(i);
				}
			}

		}
		else if (board.size() - posy == word.size())
		{
			if (board.at(posy - 1).at(posx) != '.' && board.at(posy - 1).at(posx) != '#')
			{
				cout << "Could not place the word" << endl;
				return;
			}
			else
			{
				board.at(posy - 1).at(posx) = '#';
				for (size_t i = 0; i < word.size(); i++)
				{
					board.at(posy + i).at(posx) = word.at(i);
				}
			}
		}
		else
		{
			if ((board.at(posy - 1).at(posx) != '.' && board.at(posy - 1).at(posx) != '#') || (board.at(posy + word.size()).at(posx) != '.' && board.at(posy + word.size()).at(posx) != '#'))
			{
				cout << "Could not place the word" << endl;
				return;
			}
			else
			{
				board.at(posy - 1).at(posx) = '#';
				board.at(posy + word.size()).at(posx) = '#';
				for (size_t i = 0; i < word.size(); i++)
				{
					board.at(posy + i).at(posx) = word.at(i);
				}
			}
		}
		break;
	}
	case 'H': {
		size_t b = (posx - 2) / 2;
		if (linex == word.size())
		{
			for (size_t i = 0; i < word.size(); i++)
			{
				board.at(posy).at(posx + i * 2) = word.at(i);
			}
		}
		else if (posx == 2)
		{
			if ((board.at(posy).at(posx + word.size() * 2) != '.') && (board.at(posy).at(posx + word.size() * 2) != '#'))
			{
				cout << "Could not place the word" << endl;
				return;
			}
			else
			{
				board.at(posy).at(posx + word.size() * 2) = '#';
				for (size_t i = 0; i < word.size(); i++)
				{
					board.at(posy).at(posx + i * 2) = word.at(i);
				}
				
			}
		}
		else if (linex - b == word.size())
		{
			if ((board.at(posy).at(posx - 1 * 2) != '.') && (board.at(posy).at(posx - 1 * 2) != '#'))
			{
				cout << "Could not place the word" << endl;
				return;
			}
			else
			{
				board.at(posy).at(posx - 1 * 2) = '#';
				for (size_t i = 0; i < word.size(); i++)
				{
					board.at(posy).at(posx + i * 2) = word.at(i);
				}
			}
		}
		else
		{
			if (((board.at(posy).at(posx - 1 * 2) != '.') && (board.at(posy).at(posx - 1 * 2) != '#')) || ((board.at(posy).at(posx + word.size() * 2) != '.') && (board.at(posy).at(posx + word.size() * 2) != '#')))
			{
				cout << "Could not place the word" << endl;
				return;
			}
			else
			{
				board.at(posy).at(posx + word.size() * 2) = '#';
				board.at(posy).at(posx - 1 * 2) = '#';
				for (size_t i = 0; i < word.size(); i++)
				{
					board.at(posy).at(posx + i * 2) = word.at(i);
				}
			}
		}
	}
	default:
		break;
	}
	return;
}

void Board::changechar(char s, size_t posx, size_t posy) {
	board.at(posy).at(posx) = s;
}



vector<string> Board::vec() {
	vector<string> temp = board;
	return temp;
}

size_t Board::bsize() {
	return board.size();
}

size_t Board::bssize() {
	return board.at(0).size();
}

void invertstring(string &word) {
	int n = word.length();
	for (int i = 0; i < n / 2; i++) 
	{
		swap(word[i], word[n - i - 1]);
	}
		
	return;
}

string Board::wup(int x, int y) {
	string a;
	size_t i = y - 1;
	while (i >= 1 && board.at(i).at(x) != '#')
	{
		a = a + board.at(i).at(x);
		i--;
	}
	invertstring(a);
	return a;
}

string Board::wdown(int x, int y) {
	string a;
	size_t i = y + 1;
	while (i <= board.size() - 1 && board.at(i).at(x) != '#')
	{
		a = a + board.at(i).at(x);
		i++;
	}
	return a;
}

string Board::wleft(int x, int y) {
	string a;
	size_t i = x - 2;
	while (i >= 2 && board.at(y).at(i) != '#')
	{
		a = a + board.at(y).at(i);
		i = i - 2;
	}
	invertstring(a);
	return a;
}

string Board::wright(int x, int y) {
	string a;
	size_t i = x + 2;
	while (i <= board.at(0).size() - 1 && board.at(y).at(i) != '#')
	{
		a = a + board.at(y).at(i);
		i = i + 2;
	}
	return a;
}

bool Board::spaceoccupied(string word, int x, int y, char orientation) {
	size_t posx = x * 2 + 2, posy = y + 1;
	switch (toupper(orientation))
	{
	case 'H': {
		for (size_t i = 0; i < word.size(); i++)
		{
			if (board.at(posy).at(posx + i * 2) == '.')
			{
				continue;
			}
			else
			{
				if (board.at(posy).at(posx + i * 2) == '#')
				{
					return true;
				}
				else if (board.at(posy).at(posx + i * 2) >= 'A' && board.at(posy).at(posx + i * 2) >= 'Z')
				{
					if (board.at(posy).at(posx + i * 2) == word.at(i))
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
			if (board.at(posy + i).at(posx) == '.')
			{
				continue;
			}
			else
			{
				if (board.at(posy + i).at(posx) == '#')
				{
					return true;
				}
				else if (board.at(posy + i).at(posx) >= 'A' && board.at(posy + i).at(posx) >= 'Z')
				{
					if (board.at(posy + i).at(posx) == word.at(i))
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

void Board::fill() {
	char s = '#' ;
	for (size_t i = 1; i < board.size(); i++)
	{
		for (size_t j = 0; j < board.at(i).size(); j++)
		{
			if (board.at(i).at(j) == '.')
			{
				board.at(i).at(j) = s;
			}
		}
	}
}