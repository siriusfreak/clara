#pragma once

#include <Arduino.h>
#include <vector>

class Eventable {
public:
	virtual void OnChangeDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond);
	virtual String OnWebRequest(String address, std::vector<String> &params, std::vector<String> &values);
	virtual String OnSerialCommand(std::vector<String> &values);
	virtual void OnTemperatureChange(double value);
	virtual void OnLoop();
};


