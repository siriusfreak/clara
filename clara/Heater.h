#pragma once

#include "Eventable.h"
#include "BinaryStateController.h"
#include "Savable.h"

class Heater: Eventable, Savable {
private:
	BinaryStateController stateController;
	double StartTemp;
	double EndTemp;
	bool ManualMode;

	static const int defaultStartTemp = 15;
	static const int defaultEndTemp = 20;
	static const int defaultManualMode = 0;
	static const int defaultState = 0;
public:
	Heater(int pin, int ID, bool ManualMode = false, double StartTemp = 25, double EndTemp = 30);
	Heater(int pin, int ID);
	Heater(int ID);

	void LoadFromParams(std::vector<String> params, std::vector<String> values);

	void OnTemperatureChange(double val) override;
	String OnWebRequest(String address, std::vector<String> &params, std::vector<String> &values) override;

	void TurnOn();
	void TurnOff();

	void SetManualMode(bool mode);
	bool GetManualMode();

	void SetStartTemp(int value);
	int GetStartTemp();

	void SetEndTemp(int value);
	int GetEndTemp();

	bool GetState();
	String GetJson();

	~Heater();
};

