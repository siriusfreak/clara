#pragma once

#include <DHT_sensor_library/DHT.h>
#include "Sensor.h"
#include "EventMaster.h"
#include "AnalogValueHolder.h"

class SensorDHT22: Sensor {
private:
	DHT dht;
	AnalogValueHolder holder;
public:
	SensorDHT22(int pin, int window_size);

	void UpdateData();

	~SensorDHT22();
};

