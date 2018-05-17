#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include "Cwords.h"
#include "Dictionary.h"

using namespace std;


int main() {
	int it = 0;
	int op;
	bool loop = true;
	string my_file_name, line;
	ifstream my_file;
	cout << "CROSSWORD PUZZLE CREATOR" << endl;
	cout << "=================================================================" << endl << endl;
	cout << "INSTRUCTIONS:" << endl;
	cout << "Position (LCD / CTRL + Z = stop):" << endl;
	cout << "LCD -> Line, column and direction (ex.: aAH)" << endl;
	cout << "CTRL + Z -> Finish the puzzle creation" << endl << endl;
	cout << "Word (- = remove / ? = help):" << endl;
	cout << "- -> Removes a word from the puzzle" << endl;
	cout << "? -> Shows all possible words that can be placed" << endl;
	cout << "-------------------------------------------------------------------------" << endl << endl;
	cout << "OPTIONS: " << endl;
	cout << "1 - Create a new puzzle" << endl;
	cout << "2 - Resume a puzzle" << endl;
	cout << "0 - Exit" << endl;
	cout << "-------------------------------------------------------------------------" << endl << endl;
	while (true)
	{
		cin >> op;
		switch (op)
		{
		case 0: {

			break;
		}
		case 1: {
			string my_dictionary_name;
			ifstream my_dictionary;
			cout << "Dictionary file name ? " << endl;
			cin >> my_dictionary_name;
			my_dictionary.open(my_dictionary_name);
			if (!my_dictionary.is_open())
			{
				cout << "The file could not be open" << endl;
				break;
			}
			else
			{
				it++;
				string a;
				Dictionary words;
				words.insertwords(my_dictionary);
				/*while (getline(my_dictionary, a))
				{
					words.insertword(a);
				} */// Eliminar futuramente
				int x = 0, y = 0;
				cout << "Board size (lines columns) ? " << endl;
				while (x == 0 || y == 0)
				{
					cin >> x >> y;
				}
				Cwords puzzle(x, y);
				string pos, word; 
				puzzle.printboard();
				cout << "Position (LCD / CTRL + Z = stop ) ?";
				cin >> pos;
				cout << "Word ( - = remove / ? = help ) .. ?";
				cin >> word;
				while (!cin.eof())
				{
					if (pos.size() > 3 || (tolower(pos.at(0)) > 'z' || tolower(pos.at(0)) < 'a') || (toupper(pos.at(1)) > 'Z' || toupper(pos.at(1)) < 'A') || (toupper(pos.at(2)) != 'V' && toupper(pos.at(2)) != 'H'))
					{
						cout << "Incorrect format of the position" << endl;
					}
					else
					{
						pos.at(0) = tolower(pos.at(0));
						pos.at(1) = toupper(pos.at(1));
						pos.at(2) = toupper(pos.at(2));
					}
				}
				
			}
			break;
		}
		case 2: {
			break;
		}
		default:
			break;
		}
	}
	
	return 0;
}