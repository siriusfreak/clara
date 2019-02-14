#include "SensorDHT22.h"



SensorDHT22::SensorDHT22(int pin, int window_size): dht(pin, DHT22), holder(window_size) {
	dht.begin();
}

void SensorDHT22::UpdateData() {
	double curValue = dht.readTemperature();
	if (!isnan(curValue))
		holder.AddValue(curValue);

	EventMaster::getInstance().OnTemperatureChange(holder.GetAvg());
}


SensorDHT22::~SensorDHT22() {
}
