#include "Puzzle.h"
#include "Cwords.h"
#include "Dictionary.h"
#include <iostream>
#include <fstream> 

using namespace std;

Puzzle::Puzzle(){
}

Puzzle::Puzzle(string file) {
	solution = Cwords(file);

}