#pragma once

#include <string>
#include <Arduino.h>

class BinaryStateController
{
private:
	int pin;
	bool state;
	bool reverse;

public:
	BinaryStateController(int pin, bool reverse = false);
	~BinaryStateController();
	void TurnOn();
	void TurnOff();
	bool GetState();
	void Switch();
	int GetPin();
	void SetPin(int pin);
};

