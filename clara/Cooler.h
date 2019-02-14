#pragma once

#include "Eventable.h"
#include "Savable.h"
#include "BinaryStateController.h"

class Cooler : Eventable, Savable {
private:
	BinaryStateController stateController;
	double StartTemp;
	double EndTemp;
	bool ManualMode;

	static const int defaultStartTemp = 30;
	static const int defaultEndTemp = 25;
	static const int defaultManualMode = 0;
	static const int defaultState = 0;
public:
	Cooler(int pin, int ID, bool ManualMode, double StartTemp, double EndTemp);
	Cooler(int pin, int ID);
	Cooler(int ID);

	void LoadFromParams(std::vector<String> params, std::vector<String> values);

	void OnTemperatureChange(double val) override;
	String OnWebRequest(String address, std::vector<String> &params, std::vector<String> &values) override;



	void TurnOn();
	void TurnOff();

	void SetManualMode(bool mode);
	bool GetManualMode();

	void SetStartTemp(double value);
	double GetStartTemp();

	void SetEndTemp(double value);
	double GetEndTemp();

	bool GetState();
	String GetJson();

	~Cooler();
};

