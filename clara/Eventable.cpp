#include "Eventable.h"

void Eventable::OnChangeDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond) {
	return;
}

String Eventable::OnWebRequest(String address, std::vector<String>& params, std::vector<String>& values) {
	return String();
}

String Eventable::OnSerialCommand(std::vector<String>& values) {
}

void Eventable::OnTemperatureChange(double value) {
}

void Eventable::OnLoop() {
}
