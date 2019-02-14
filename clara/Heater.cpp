#include "Heater.h"

Heater::Heater(int pin, int ID, bool ManualMode, double StartTemp, double EndTemp) :
	stateController(pin, true) {
	this->Device = "heater";
	this->ID = ID;
	this->ManualMode = ManualMode;
	this->StartTemp = StartTemp;
	this->EndTemp = EndTemp;
}

Heater::Heater(int pin, int ID) : stateController(pin, true) {
	this->LoadFromJson();
	stateController.SetPin(pin);
}

Heater::Heater(int ID) : stateController(0, true) {
	this->LoadFromJson();
}

void Heater::LoadFromParams(std::vector<String> params, std::vector<String> values) {
	int pin = this->GetOrDefault<int>("pin", params, values, -1);

	this->SetStartTemp(this->GetOrDefault<double>("start_temp", params, values, Heater::defaultStartTemp));
	this->SetEndTemp(this->GetOrDefault<double>("end_temp", params, values, Heater::defaultEndTemp));
	this->SetManualMode(this->GetOrDefault<int>("manual_mode", params, values, Heater::defaultManualMode));

	int state = this->GetOrDefault<int>("state", params, values, Heater::defaultState);

	stateController.SetPin(pin);
	if (state)
		stateController.TurnOn();
	else
		stateController.TurnOff();

}

void Heater::OnTemperatureChange(double val) {
	if (!ManualMode) {
		if (val >= StartTemp && val <= EndTemp)
			this->TurnOn();
		else
			this->TurnOff();
	}
}

String Heater::OnWebRequest(String address, std::vector<String> &params, std::vector<String> &values) {
	String res = "";
	if (address == "heater") {
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
					this->SetStartTemp(value);
				}
			}
			else if (cmd == "set_end_time") {
				int value = this->GetOrDefault<int>("value", params, values, -1);

				if (value != -1) {
					this->SetEndTemp(value);
				}
			}
			else if (cmd == "get_json")
				res += this->GetJson();
		}
	}

	return res;
}


void Heater::TurnOn() {
	this->stateController.TurnOn();
	this->SaveJson();
}

void Heater::TurnOff() {
	this->TurnOff();
}

void Heater::SetManualMode(bool mode) {
	this->ManualMode = mode;
	this->SaveJson();
}

bool Heater::GetManualMode() {
	return this->ManualMode;
}

void Heater::SetStartTemp(int value) {
	this->StartTemp = value;
	this->SaveJson();
}

int Heater::GetStartTemp() {
	return this->StartTemp;
}

void Heater::SetEndTemp(int value) {
	this->EndTemp = value;
	this->SaveJson();
}

int Heater::GetEndTemp() {
	return this->EndTemp;
}

bool Heater::GetState() {
	return this->stateController.GetState();
}

String Heater::GetJson() {
	return String("{ 'device' : '") + this->Device + "', " +
		"'id' : " + String(this->ID) + ", " +
		"'pin' : " + String(this->stateController.GetPin()) + ", " +
		"'start_temp' : " + String(this->GetStartTemp()) + ", " +
		"'end_temp' : " + String(this->GetEndTemp()) + ", " +
		"'manual_mode' : " + String(this->GetManualMode()) + ", " +
		"'state' : " + String(this->GetState()) + ", " +
		"}";
}

Heater::~Heater() {
}
