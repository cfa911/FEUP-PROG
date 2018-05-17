#include "Dictionary.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

Dictionary::Dictionary()
{
	wands={};
}

Dictionary::Dictionary(ifstream& file) {
	map <string, vector<string>> sword_map;
	if (file.is_open()) {
		while (!file.eof())
		{
			vector<string> synonims;
			string line;
			string word;
			string sword;
			string sline;
			int i = 0;
			getline(file, line);
			word = line.substr(0, line.find(":"));
			size_t pos = line.find(" ");
			sline = line.substr(pos + 1);
			sword = "";
			while (sline.length() != 0) {
				if (sline[i] == ',') {
					synonims.push_back(sword);
					if (sline.length() == sword.length() + 1)
						break;
					if (sline[i + 1] == ' ' && sline[i + 2] == ',') { //caso especial de ", ,"
						i += 4;
						sword = "";
					}
					else { // casos normais
						sline = sline.substr(i + 2);
						sword = "";
						i = 0;
					}
				}
				else if (sline.length() == i + 1) { // caso "palavra," e fim de linha
					sword += sline[i];
					synonims.push_back(sword);
					break;
				}
				sword += sline[i];
				i++;
			}
			sword_map.insert(std::pair<string, vector<string>>(word, synonims));
		}
	}
	wands.insert(sword_map.begin(), sword_map.end());
}
//
//void removespaces(string &token) {
//	size_t ps = token.find_first_not_of(" ");
//	token.erase(0, ps);
//}
//
//vector<string> dividestring(string line) {
//	vector<string> syn;
//	string token;
//	size_t del = line.find_first_of(",");
//	while (line.size() > 0) {
//		if (del > line.size())
//		{
//			removespaces(line);
//			syn.push_back(line);
//			line.clear();
//			return;
//		}
//		else
//		{
//			token = line.substr(0, del);
//			removespaces(token);
//			syn.push_back(token);
//			token.clear();
//			line.erase(0, del + 1);
//		}
//		del = line.find_first_of(",");
//	}
//	
//}
//
//void Dictionary::insertword(string line) {
//	string a;
//	size_t npos;
//	vector<string> temp;
//	npos = line.find_first_of(":");
//	a = line.substr(0, npos);
//	for (size_t i = 0; i < a.size(); i++)
//	{
//		a[i] = toupper(a[i]);
//	}
//	if (wands.find(a) == wands.end())
//	{
//		line.erase(0, npos + 1);
//		temp = dividestring(line);
//		for (size_t i = 0; i < temp.size(); i++)
//		{
//			wands.find(a)->second.push_back(temp.at(i));
//		}
//	}
//	else
//	{
//		wands.insert(std::pair<string, vector<string>>(a, temp));
//	}
//	return;
//}

void Dictionary::insertwords(ifstream& file)
{
	map <string, vector<string>> sword_map;
	if (file.is_open()) {
		while (!file.eof())
		{
			vector<string> synonims;
			string line;
			string word;
			string sword;
			string sline;
			int i = 0;
			getline(file, line);
			word = line.substr(0, line.find(":"));
			size_t pos = line.find(" ");
			sline = line.substr(pos + 1);
			sword = "";
			while (sline.length() != 0) {
				if (sline[i] == ',') {
					synonims.push_back(sword);
					if (sline.length() == sword.length() + 1)
						break;
					if (sline[i + 1] == ' ' && sline[i + 2] == ',') { //caso especial de ", ,"
						i += 4;
						sword = "";
					}
					else { // casos normais
						sline = sline.substr(i + 2);
						sword = "";
						i = 0;
					}
				}
				else if (sline.length() == i + 1) { // caso "palavra," e fim de linha
					sword += sline[i];
					synonims.push_back(sword);
					break;
				}
				sword += sline[i];
				i++;
			}
			sword_map.insert(std::pair<string, vector<string>>(word, synonims));
		}
	}
	wands.insert(sword_map.begin(), sword_map.end());
}

bool Dictionary::wordexists(string word) {
	if (wands.find(word) == wands.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

