#include "Puzzle.h"
#include "Cwords.h"

using namespace std;

int main() {
	Cwords a = Cwords(10, 10);
	a.printcword();
	string s = "Nao", o = "H";
	bool b = a.wordfits(s, 9, 5, o[0]);
	string word = "BRIDGE", ori = "bAH";
	string word1 = "TANK", ori1 = "aBV";
	string word2 = "CAR", ori2 = "hBV";
	string word3 = "TANK", ori3 = "aAH";
	string word4 = "BRICK", ori4 = "aAH";
	string word5 = "ALIEN", ori5 = "aAH";
	string word6 = "DRUG", ori6 = "aAH";
	a.insertword(ori, word);
	a.insertword(ori1, word1);
	a.insertword(ori2, word2);
	a.printcword();
	//a.removeword(word);
	a.fillempty();
	a.printcword();

	return 0;
}