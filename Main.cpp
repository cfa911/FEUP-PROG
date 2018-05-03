#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>

using namespace std;


void insertwords(string line, map<string, string> &words) {
	string a;
	size_t npos;
	npos = line.find_first_of(":");
	a = line.substr(0, npos);
	for (size_t i = 0; i < a.size(); i++)
	{
		a[i] = toupper(a[i]);
	}
	if (words.find(a) == words.end())
	{
		line.erase(0, npos + 1);
		words.insert(std::pair<string, string>(a, line));
		line.clear();
	}
	else
	{
		line.erase(0, npos + 1);
		words.find(a)->second = words.find(a)->second + "," + line;
	}
}

int main() {
	map<string,string> words;
	string my_file_name, line;
	ifstream my_file;
	cout << "File name?" << endl;
	cin >> my_file_name;
	my_file.open(my_file_name);
	if (my_file.fail())
	{
		cout << "File could not be open" << endl;
		return 0;
	}
	else
	{
		while (!my_file.eof())
		{
			getline(my_file, line);
			insertwords(line, words);
		}
	}
	return 0;
}