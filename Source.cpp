#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;


void insertwords(string line, set<string> &words) {
	string a;
	int i = 1;
	size_t npos;
	while (line.size() != 0)
	{
		if (i == 1)
		{
			npos = line.find_first_of(":");
			if (npos > line.size())
			{
				a = line.substr(0, line.size());
				line.clear();
				words.insert(a);
				a.clear();
			}
			else
			{
				a = line.substr(0, npos);
				line.erase(0, npos + 1);
				words.insert(a);
				a.clear();
			}
			i = i - 1;
		}
		else
		{
			npos = line.find_first_of(",");
			if (npos > line.size())
			{
				a = line.substr(0, line.size());
				line.clear();
				words.insert(a);
				a.clear();
			}
			else
			{
				a = line.substr(0, npos);
				line.erase(0, npos + 1);
				words.insert(a);
				a.clear();
			}
		}
	}

}

int main() {
	set<string> words;
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