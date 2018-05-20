#include "Timer.h"

using namespace std;

Timer::Timer() {
	start = time(NULL); 
}

Timer::~Timer()
{
}

unsigned long Timer::clock()
{
	return time(NULL) - start;
}
