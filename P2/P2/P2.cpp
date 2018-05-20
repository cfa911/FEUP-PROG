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
			srand(time(NULL));
			Timer time;
			int n = 0;
			string puzzlename;
			string player;
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "Please enter your name: ";
			cin.clear();
			cin.ignore();
			getline(cin,player);
			cout << "Name of the file where the puzzle is stored" << endl;
			cin >> puzzlename;
			Cwords puzzlefinal(puzzlename);
			Cwords puzzle(puzzlename,player);
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
				do
				{
					cout << "Position (LCD / CTRL + Z = stop ) ?" << endl;
					cin >> pos;
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
							int a = n;
							string solution;
							map<string, string> aux_palex = puzzlefinal.getWordsPos();
							map<string, vector<string>> aux_words = words.getMap();
							for (auto it = aux_palex.begin(); it != aux_palex.end(); ++it) {
								if (it->second == pos) {
									n++;
									solution = it->first;
									break;
								}
							}
							if(n == a)
								cout << endl << "There isn't a word starting in that position " << endl;
							else
							{
								//int i = 0;
								for (auto it = aux_words.begin(); it != aux_words.end(); ++it) {
									//vector<string> vec_aux;
									//vector<string> vec;
									if (it->first == solution) {
										//i++;
										vector<string> vec = it->second;
										/*for (int m = 0; m < vec.size(); m++) {
												vec_aux.push_back(vec[m]);
										}*/
										//if (i == 1) {
											int ran = vec.size() - 1; //size of auxiliary vector with synonims inside
											int value = rand() % ran;     // value in the range 1 to ran
											cout << "\nHint: "<< vec[value] << endl << endl;
											break;
										//}
									}
								}
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
				} while ((puzzle.getBoard().getVector() != puzzlefinal.getBoard().getVector()) && (!cin.eof()));
				string save = player + " completed the puzzle " + puzzlename + " in " + to_string(time.clock()) + " seconds." + " With " + to_string(n) + " hints";
				if (puzzle.getBoard().getVector() == puzzlefinal.getBoard().getVector()) {
					puzzle.saveinfile(save_file_name, save);
					cout << "Congratulations!! You finished the board in: " << time.clock() << " seconds!!";
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