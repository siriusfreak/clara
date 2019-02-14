#include "AnalogValueHolder.h"



AnalogValueHolder::AnalogValueHolder(int capacity)
{
	this->capacity = capacity;
	this->values = new double(capacity);
	this->size = 0;
}

void AnalogValueHolder::AddValue(double val)
{
	index = (index + 1) % capacity;

	if (this->size < capacity)
		this->size++;

	values[index] = val;
}

double AnalogValueHolder::GetMax()
{
	assert(this->size > 0);

	double max = values[0];

	for (int i = 1; i < this->size; i++)
		if (values[i] > max)
			max = values[i];

	return max;
}

double AnalogValueHolder::GetMin()
{
	assert(this->size > 0);

	double min = values[0];

	for (int i = 1; i < this->size; i++)
		if (values[i] < min)
			min = values[i];

	return min;
}

double AnalogValueHolder::GetAvg()
{
	assert(this->size > 0);
	
	double avg = 0;

	for (int i = 0; i < this->size; i++)
		avg += this->values[i];

	return avg / this->size;
}


AnalogValueHolder::~AnalogValueHolder()
{
	delete this->values;
}
