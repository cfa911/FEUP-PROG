#pragma once
#include <iostream>
#include <time.h>

class Timer {
public:
	Timer();
	virtual ~Timer();
	unsigned long clock();
private:
	unsigned long start;
};

