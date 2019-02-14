#pragma once

#include <Arduino.h>
#include <FS.h>
#include "ArduinoJson.h"

class Savable {
private:
	String GetFileName();
	
	static const int maxBufSize = 1024 * 5;
protected:
	String Device;
	template<typename  T> T GetOrDefault(String name, std::vector<String> &param, std::vector<String> &value, T def);
	int ID;
public:
	virtual String GetJson() = 0;
	virtual void LoadFromParams(std::vector<String> params, std::vector<String> values) = 0;
	
	void SaveJson();
	void LoadFromJson();
};

