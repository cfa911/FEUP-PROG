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

void changefilename(int it, string &filename) {
	string a = to_string(it);
	size_t b = a.size();
		switch (b)
		{
		case 1: {
				filename[3] = a[0];
		}
		case 2: {

			for (size_t i = 0; i < a.size(); i++)
			{
				filename[2 + i] = a[i];
			}
			break;
		}
		case 3: {
			for (size_t i = 0; i < a.size(); i++)
			{
				filename[i + 1] = a[i];
			}
			break;
		}
		default:
			break;
		};
	return;
}

int main() {
	string save_file_name = "b000.txt";
	int it = -1;
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
	while (true)
	{
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "Select an option" << endl;
		cin >> op;
		switch (op)
		{
		case 0: {

			break;
		}
		case 1: {
			cout << "-------------------------------------------------------------------------" << endl;
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
				changefilename(it, save_file_name);
				string a;
				Dictionary words;
				words.insertwords(my_dictionary);
				int x = 0, y = 0;
				cout << "Board size (lines columns) ? " << endl;
				while (x == 0 || y == 0)
				{
					cin >> x >> y;
				}
				Cwords puzzle(x, y, my_dictionary_name);
				string pos, word;
				puzzle.printboard();
				cout << "Position (LCD / CTRL + Z = stop ) ? "<<endl;
				cin >> pos;
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
						cout << "Word (- = remove / ? = help) .. ? " << endl;
						cin >> word;
						for (size_t i = 0; i < word.size(); i++)
						{
							word.at(i) = toupper(word.at(i));
						}
						if (word == "-")
						{
							puzzle.removeword(pos);
						}
						 if (word == "?")
						{
							string a = puzzle.spacetofill(pos);
							vector<string> wordhelp = words.help(a);
							for (size_t i = 0; i < wordhelp.size(); i++)
							{
								cout << wordhelp[i] << endl;;
							}
						}
						else
						{
							if (words.wordexists(word) == true)
							{
								puzzle.insertword(pos, word);
							}
							else
							{
								cout << "Word doesn't exist in the dictionary" << endl;
							}
						}
					}
					puzzle.printboard();
					cout << "Position (LCD / CTRL + Z = stop ) ?" << endl;
					cin >> pos;
				}
				map<string, string> temp = puzzle.npossiblewords();
				map<string, string>::iterator t;
				for ( t = temp.begin(); t != temp.end(); t++)
				{
					if (words.wordexists(t->first) == true)
					{
						puzzle.insertword2(t->second, t->first);
					}
				}
				puzzle.printboard();
				puzzle.saveinfile(save_file_name);
			}
			cin.clear();
			break;
		}
		case 2:{
			string puzzlename;
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "Name of the file where the puzzle is stored" << endl;
			cin >> puzzlename;
			Cwords puzzle(puzzlename);
			string dictionary_name = puzzle.dictionaryname();
			ifstream dictionary;
			dictionary.open(dictionary_name);
			if (!dictionary.is_open())
			{
				cout << "Could not open the file" << endl;
			}
			else
			{
				Dictionary words;
				words.insertwords(dictionary);
				string pos, word;
				puzzle.printboard();
				cout << "Position (LCD / CTRL + Z = stop ) ? " << endl;
				cin >> pos;
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
						cout << "Word (- = remove / ? = help) .. ? " << endl;
						cin >> word;
						for (size_t i = 0; i < word.size(); i++)
						{
							word.at(i) = toupper(word.at(i));
						}
						if (word == "-")
						{
							puzzle.removeword(pos);
						}
						else if (word == "?")
						{

						}
						else
						{
							if (words.wordexists(word) == true)
							{
								puzzle.insertword(pos, word);
							}
							else
							{
								cout << "Word doesn't exist in the dictionary" << endl;
							}
						}
					}
					puzzle.printboard();
					cout << "Position (LCD / CTRL + Z = stop ) ?" << endl;
					cin >> pos;
				}
				puzzle.saveinfile(save_file_name);
			}
			cin.clear();
			break;
		}
		default:
			break;
		}
	}
	
	return 0;
}