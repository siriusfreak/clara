#include "BinaryStateController.h"



BinaryStateController::BinaryStateController(int pin, bool reverse) {
	this->pin = pin;
	this->reverse = false;

	if (pin != -1) {
		pinMode(pin, OUTPUT);

		if (this->reverse)
			digitalWrite(pin, HIGH);
		else
			digitalWrite(pin, LOW);

		this->state = false;
	}
}


BinaryStateController::~BinaryStateController()
{
}

void BinaryStateController::TurnOn()
{
	this->state = true;
	if (this->reverse)
		digitalWrite(this->pin, LOW);
	else
		digitalWrite(this->pin, HIGH);
}

void BinaryStateController::TurnOff()
{
	this->state = false;
	if (this->reverse)
		digitalWrite(this->pin, HIGH);
	else
		digitalWrite(this->pin, LOW);
}

bool BinaryStateController::GetState()
{
	return this->state;
}

void BinaryStateController::Switch()
{
	if (this->state)
		this->TurnOff();
	else
		this->TurnOn();
}

int BinaryStateController::GetPin() {
	return this->pin;
}

void BinaryStateController::SetPin(int pin) {
	this->pin = pin;

	pinMode(pin, OUTPUT);

	if (this->reverse)
		digitalWrite(pin, HIGH);
	else
		digitalWrite(pin, LOW);

	this->state = false;
}

