#include "Dictionary.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// WildcardMatch
// str - Input string to match
// strWild - Match mask that may contain wildcards like ? and *
//
// A ? sign matches any character, except an empty string.
// A * sign matches any string inclusive an empty string.
// Characters are compared caseless.
//
// ADAPTED FROM:
// https://www.codeproject.com/Articles/188256/A-Simple-Wildcard-Matching-Function
bool wildcardMatch(const char *str, const char *strWild)
{
	// We have a special case where string is empty ("") and the mask is "*".
	// We need to handle this too. So we can't test on !*str here.
	// The loop breaks when the match string is exhausted.
	while (*strWild)
	{
		// Single wildcard character
		if (*strWild == '?')
		{
			// Matches any character except empty string
			if (!*str)
				return false;
			// OK next
			++str;
			++strWild;
		}
		else if (*strWild == '*')
		{
			// Need to do some tricks.
			// 1. The wildcard * is ignored.
			// So just an empty string matches. This is done by recursion.
			// Because we eat one character from the match string,
			// the recursion will stop.
			if (wildcardMatch(str, strWild + 1))
				// we have a match and the * replaces no other character
				return true;
			// 2. Chance we eat the next character and try it again,
			// with a wildcard * match. This is done by recursion.
			// Because we eat one character from the string,
			// the recursion will stop.
			if (*str && wildcardMatch(str + 1, strWild))
				return true;
			// Nothing worked with this wildcard.
			return false;
		}
		else
		{
			// Standard compare of 2 chars. Note that *str might be 0 here,
			// but then we never get a match on *strWild
			// that has always a value while inside this loop.
			if (toupper(*str++) != toupper(*strWild++))
				return false;
		}
	}
	// Have a match? Only if both are at the end...
	return !*str && !*strWild;
}

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
			for (size_t i = 0; i < word.size(); i++)
			{
				word.at(i) = toupper(word.at(i));
			}
			size_t pos = line.find(" ");
			sline = line.substr(pos + 1);
			sword = "";
			while (sline.length() != 0) {
				if (sline[i] == ',') {
					for (size_t i = 0; i < sword.size(); i++)
					{
						sword.at(i) = toupper(sword.at(i));
					}
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
					for (size_t i = 0; i < sword.size(); i++)
					{
						sword.at(i) = toupper(sword.at(i));
					}
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
			for (size_t i = 0; i < word.size(); i++)
			{
				word.at(i) = toupper(word.at(i));
			}
			size_t pos = line.find(" ");
			sline = line.substr(pos + 1);
			sword = "";
			while (sline.length() != 0) {
				if (sline[i] == ',') {
					for (size_t i = 0; i < sword.size(); i++)
					{
						sword.at(i) = toupper(sword.at(i));
					}
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
					for (size_t i = 0; i < sword.size(); i++)
					{
						sword.at(i) = toupper(sword.at(i));
					}
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

vector<string> Dictionary::help(string place) {
	vector<string> words;
	map<string, vector<string>>::iterator it;
	for ( it = wands.begin(); it != wands.end(); it++)
	{
		const char * a = it->first.c_str();
		const char * b = place.c_str();
		if (wildcardMatch(a,b) == true)
		{
			words.push_back(it->first);
		}
	}
	return words;
}

map<string, vector<string>> Dictionary::getMap()
{
	return wands;
}

