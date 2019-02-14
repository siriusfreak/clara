#include "Water.h"

Water::Water(int pin, int ID, bool ManualMode, int StartTime, double lInMin, double L) :
	stateController(pin, true) {
	this->Device = "water";
	this->ID = ID;
	this->ManualMode = ManualMode;
	this->StartTime = StartTime;
	this->lInMin = lInMin;
	this->L = L;
}

void Water::OnChangeDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond) {
	double EndTime = StartTime + this->GetL() / this->GetLInMin();
	if (!ManualMode) {
		int curTime = hour * 60 * 60 + minute * 60 + second;
		if (curTime >= StartTime && curTime <= EndTime)
			this->TurnOn();
		else
			this->TurnOff();
	}
}

String Water::OnWebRequest(String address, std::vector<String> &params, std::vector<String> &values) {
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
			else if (cmd == "set_l_in_min") {
				int value = this->GetOrDefault<int>("value", params, values, -1);

				if (value != -1) {
					this->SetLInMin(value);
				}
			}
			else if (cmd == "set_l") {
				int value = this->GetOrDefault<int>("value", params, values, -1);

				if (value != -1) {
					this->SetL(value);
				}
			}
			else if (cmd == "get_json")
				res += this->GetJson();
		}
	}


	return res;
}


void Water::TurnOn() {
	this->stateController.TurnOn();
}

void Water::TurnOff() {
	this->TurnOff();
}

void Water::SetManualMode(bool mode) {
	this->ManualMode = mode;
	this->SaveJson();
}

bool Water::GetManualMode() {
	return this->ManualMode;
}

void Water::SetStartTime(int value) {
	this->StartTime = value;
	this->SaveJson();
}

int Water::GetStartTime() {
	return this->StartTime;
}

void Water::SetLInMin(double value) {
	this->lInMin = value;
	this->SaveJson();
}

double Water::GetLInMin() {
	return this->lInMin;
}

void Water::SetL(double value) {
	this->L = value;
	this->SaveJson();
}

double Water::GetL() {
	return this->L;
}

bool Water::GetState() {
	return this->stateController.GetState();
}

String Water::GetJson() {
	return String("{ 'device' : '") + this->Device + "', " +
		"'id' : " + String(this->ID) + ", " +
		"'pin' : " + String(this->stateController.GetPin()) + ", " +
		"'start_time' : " + String(this->GetStartTime()) + ", " +
		"'l_in_min' : " + String(this->GetLInMin()) + ", " +
		"'l' : " + String(this->GetL()) + ", " +
		"'manual_mode' : " + String(this->GetManualMode()) + ", " +
		"'state' : " + String(this->GetState()) + ", " +
		"}";
}

Water::~Water() {
}
