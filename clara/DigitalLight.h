#pragma once

#include "Eventable.h"
#include "BinaryStateController.h"
#include "Savable.h"
#include <string>
#include <Arduino.h>

class DigitalLight : Eventable, Savable {
private:
	BinaryStateController stateController;
	int StartTime;
	int EndTime;
	bool ManualMode;
public:
	DigitalLight(int pin, int ID, bool ManualMode = false, int StartTime = 8 * 60 * 60, int EndTime = 20 * 60 * 60);

	void OnChangeDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond) override;
	String OnWebRequest(String address, std::vector<String> &params, std::vector<String> &values) override;

	void TurnOn();
	void TurnOff();

	void SetManualMode(bool mode);
	bool GetManualMode();

	void SetStartTime(int value);
	int GetStartTime();

	void SetEndTime(int value);
	int GetEndTime();

	bool GetState();
	String GetJson();

	~DigitalLight();
};

