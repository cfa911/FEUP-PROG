#include "Puzzle.h"
#include "Cwords.h"

using namespace std;

int main() {
	Cwords a = Cwords(10, 5);
	a.printcword();
	string s = "Nao", o = "H";
	bool b = a.wordfits(s, 9, 5, o[0]);
}