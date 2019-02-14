#include "EventMaster.h"



EventMaster::EventMaster() {

}

void EventMaster::AddObject(Eventable obj) {
	Objects.push_back(obj);
}

void EventMaster::OnChangeDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond) {
	for (int i = 0; i < Objects.size(); i++) {
		Objects[i].OnChangeDateTime(year, month, day, hour, minute, second, millisecond);
	}
}

String EventMaster::OnWebRequest(String address, std::vector<String>& params, std::vector<String>& values) {
	String res = "";
	for (int i = 0; i < Objects.size(); i++) {
		res += Objects[i].OnWebRequest(address, params, values);
	}
	return res;
}

String EventMaster::OnSerialCommand(std::vector<String>& values) {
	String res = "";
	for (int i = 0; i < Objects.size(); i++) {
		res += Objects[i].OnSerialCommand(values);
	}
	return res;
}

void EventMaster::OnTemperatureChange(double value) {
	for (int i = 0; i < Objects.size(); i++) {
		Objects[i].OnTemperatureChange(value);
	}
}

void EventMaster::OnLoop() {
	for (int i = 0; i < Objects.size(); i++) {
		Objects[i].OnLoop();
	}
}


EventMaster::~EventMaster() {
}
