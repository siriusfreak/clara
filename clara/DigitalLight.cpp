#include "DigitalLight.h"

DigitalLight::DigitalLight(int pin, int ID, bool ManualMode, int StartTime, int EndTime) :
	stateController(pin, true) {
	this->Device = "binary_light";
	this->ID = ID;
	this->ManualMode = ManualMode;
	this->StartTime = StartTime;
	this->EndTime = EndTime;
}

void DigitalLight::OnChangeDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond) {
	if (!ManualMode) {
		int curTime = hour * 60 * 60 + minute * 60 + second;
		if (curTime >= StartTime && curTime <= EndTime)
			this->TurnOn();
		else
			this->TurnOff();
	}
}

String DigitalLight::OnWebRequest(String address, std::vector<String> &params, std::vector<String> &values) {
	String res = "";
	if (address == "light") {
		int requestID = this->GetOrDefault<int>("id", params, values, -1);

		if (requestID == this->ID) {
			String cmd = this->GetOrDefault<String>("cmd", params, values, "");
			cmd.toLowerCase();

			if (cmd == "turn_on")
				this->TurnOn();
			else if (cmd == "turn_off")
				this->TurnOff();
			else if (cmd == "enable_manual")
				this->SetManualMode(true);
			else if (cmd == "disable_manual")
				this->SetManualMode(false);
			else if (cmd == "set_start_time") {
				int value = this->GetOrDefault<int>("value", params, values, -1);

				if (value != -1) {
					this->SetStartTime(value);
				}
			}
			else if (cmd == "set_end_time") {
				int value = this->GetOrDefault<int>("value", params, values, -1);

				if (value != -1) {
					this->SetEndTime(value);
				}
			}
			else if (cmd == "get_json")
				res += this->GetJson();
		}
	}
	return res;
}

void DigitalLight::TurnOn() {
	this->stateController.TurnOn();
	this->SaveJson();
}

void DigitalLight::TurnOff() {
	this->TurnOff();
}

void DigitalLight::SetManualMode(bool mode) {
	this->ManualMode = mode;
	this->SaveJson();
}

bool DigitalLight::GetManualMode() {
	return this->ManualMode;
}

void DigitalLight::SetStartTime(int value) {
	this->StartTime = value;
	this->SaveJson();
}

int DigitalLight::GetStartTime() {
	return this->StartTime;
}

void DigitalLight::SetEndTime(int value) {
	this->EndTime = value;
	this->SaveJson();
}

int DigitalLight::GetEndTime() {
	return this->EndTime;
}

bool DigitalLight::GetState() {
	return this->stateController.GetState();
}

String DigitalLight::GetJson() {
	return String("{ 'device' : '") + this->Device + "', " +
		"'id' : " + String(this->ID) + ", " +
		"'pin' : " + String(this->stateController.GetPin()) + ", " +
		"'start_time' : " + String(this->GetStartTime()) + ", " +
		"'end_time' : " + String(this->GetEndTime()) + ", " +
		"'manual_mode' : " + String(this->GetManualMode()) + ", " +
		"'state' : " + String(this->GetState()) + ", " +
		"}";
}

DigitalLight::~DigitalLight() {
}
