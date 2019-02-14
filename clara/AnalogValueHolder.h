#pragma once

#include <cassert>
#include <Arduino.h>

class AnalogValueHolder
{
private:
	int capacity;
	int index;
	int size;
	double *values;
public:
	AnalogValueHolder(int capacity);
	void AddValue(double val);
	double GetMax();
	double GetMin();
	double GetAvg();
	~AnalogValueHolder();
};

