#pragma once

#include "Eventable.h"
#include "BinaryStateController.h"
#include "Savable.h"
#include <string>
#include <Arduino.h>

class Water : Eventable, Savable {
private:
	BinaryStateController stateController;
	int StartTime;
	double lInMin;
	double L;
	bool ManualMode;
public:
	Water(int pin, int ID, bool ManualMode = false, int StartTime = 8 * 60 * 60, double lInMin = 4, double L = 1);

	void OnChangeDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond) override;
	String OnWebRequest(String address, std::vector<String> &params, std::vector<String> &values) override;

	void TurnOn();
	void TurnOff();

	void SetManualMode(bool mode);
	bool GetManualMode();

	void SetStartTime(int value);
	int GetStartTime();

	void SetLInMin(double value);
	double GetLInMin();

	void SetL(double value);
	double GetL();

	bool GetState();
	String GetJson();

	~Water();
};

