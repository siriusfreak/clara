#pragma once

#include <Arduino.h>
#include <vector>
#include "Eventable.h"

class EventMaster {
private:
	std::vector<Eventable> Objects;
	EventMaster();
	~EventMaster();
public:


	void AddObject(Eventable obj);

	void OnChangeDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond);
	String OnWebRequest(String address, std::vector<String> &params, std::vector<String> &values);
	String OnSerialCommand(std::vector<String> &values);
	void OnTemperatureChange(double value);
	void OnLoop();

	EventMaster(EventMaster const&) = delete;
	void operator=(EventMaster const&) = delete;

	static EventMaster& getInstance() {
		static EventMaster instance;
		return instance;
	}


};

