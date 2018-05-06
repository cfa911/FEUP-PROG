#include "Puzzle.h"
#include "Cwords.h"

using namespace std;

int main() {
	Cwords a = Cwords(10, 10);
	a.printcword();
	string s = "Nao", o = "H";
	bool b = a.wordfits(s, 9, 5, o[0]);
	string word = "BRIDGE", ori = "aAH";
	string word1 = "CAR", ori1 = "bBH";
	string word2 = "BLOCK", ori2 = "aAV";
	string word3 = "TANK", ori3 = "aAH";
	string word4 = "BRICK", ori4 = "aAH";
	string word5 = "ALIEN", ori5 = "aAH";
	string word6 = "DRUG", ori6 = "aAH";
	a.insertword(ori, word);
	a.insertword(ori2, word2);
	a.insertword(ori1, word1);
	a.printcword();
	return 0;
}