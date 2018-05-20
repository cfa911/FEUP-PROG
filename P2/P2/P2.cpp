#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include "Cwords.h"
#include "Dictionary.h"
#include "Timer.h"

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
	string save_file_name = "b000_p.txt";
	int it = -1;
	int op;
	bool loop = true;
	string my_file_name, line;
	ifstream my_file;
	cout << "CROSSWORD PUZZLE PLAYER" << endl;
	cout << "=================================================================" << endl << endl;
	cout << "INSTRUCTIONS:" << endl;
	cout << "Position (LCD / CTRL + Z = stop):" << endl;
	cout << "LCD -> Line, column and direction (ex.: aAH)" << endl;
	cout << "CTRL + Z -> Give up and start another puzzle" << endl << endl;
	cout << "Word (- = remove / ? = help):" << endl;
	cout << "- -> Removes a word from the board" << endl;
	cout << "? -> Shows synonims of the word in the given position" << endl;
	cout << "-------------------------------------------------------------------------" << endl << endl;
	cout << "OPTIONS: " << endl;
	cout << "1 - Play a puzzle!!" << endl;
	cout << "0 - Exit" << endl;
	while (loop)
	{
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "Select an option" << endl;
		cin >> op;
		switch (op)
		{
		case 0: {
			loop = false;
			break;
		}
		case 1: {
			Timer time;
			string puzzlename;
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "Name of the file where the puzzle is stored" << endl;
			cin >> puzzlename;
			Cwords puzzlefinal(puzzlename);
			Cwords puzzle(puzzlename,"player");
			string dictionary_name = puzzlefinal.dictionaryname();
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
				while ((puzzle.getBoard().getVector() != puzzlefinal.getBoard().getVector())&&(!cin.eof()))
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

							/*
							string a = puzzle.spacetofill(pos);
							vector<string> wordhelp = words.help(a);
							for (size_t i = 0; i < wordhelp.size(); i++)
							{
								cout << wordhelp[i] << endl;;
							}
							*/
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
				if (puzzle.getBoard().getVector() == puzzlefinal.getBoard().getVector()) {
					puzzle.saveinfile(save_file_name,time.clock());
					cout << "Congratulations!! You finished the board in: " << time.clock() << "seconds!!";
				}

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