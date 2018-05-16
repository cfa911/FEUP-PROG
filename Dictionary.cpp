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

Dictionary::Dictionary(ifstream file) {

}
void removespaces(string &token) {
	size_t ps = token.find_first_not_of(" ");
	token.erase(0, ps);
}

vector<string> dividestring(string line) {
	vector<string> syn;
	string token;
	size_t del = line.find_first_of(",");
	while (line.size() > 0) {
		if (del > line.size())
		{
			removespaces(line);
			syn.push_back(line);
			line.clear();
			return;
		}
		else
		{
			token = line.substr(0, del);
			removespaces(token);
			syn.push_back(token);
			token.clear();
			line.erase(0, del + 1);
		}
		del = line.find_first_of(",");
	}
	
}

void Dictionary::insertword(string line) {
	string a;
	size_t npos;
	vector<string> temp;
	npos = line.find_first_of(":");
	a = line.substr(0, npos);
	for (size_t i = 0; i < a.size(); i++)
	{
		a[i] = toupper(a[i]);
	}
	if (wands.find(a) == wands.end())
	{
		line.erase(0, npos + 1);
		temp = dividestring(line);
		for (size_t i = 0; i < temp.size(); i++)
		{
			wands.find(a)->second.push_back(temp.at(i));
		}
	}
	else
	{
		wands.insert(std::pair<string, vector<string>>(a, temp));
	}
	return;
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

