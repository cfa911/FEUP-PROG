#include "Cwords.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

vector<string> Cwords::emptycword(int x, int y)
{
	vector<string> crossword;
	string a;
	char c, C;
	for (size_t i = 0; i < y; i++)
	{
		if (y == 0)
		{
			for (size_t j = 0; j < x * 2; j++)
			{
				if ((y *2) % 2 == 0)
				{
					a = a + " ";
				}
				else
				{
					c = 'a' + j - 1;
					a = a + c;
				}

			}
			crossword[i] = a;
			a.clear();
		}
		else
		{
			for (size_t j = 0; j < x * 2; j++)
			{
				if (j == 0)
				{
					C = 'A' + y - 1;
					a = a + C;
				}
				else
				{
					if ((x*2) % 2 == 0)
					{
						a = a + " ";
					}
					else
					{
						a = a + ".";
					}
				}
			}
			crossword[i] = a;
			a.clear();
		}
	}
	return crossword;
}

int main() {






}