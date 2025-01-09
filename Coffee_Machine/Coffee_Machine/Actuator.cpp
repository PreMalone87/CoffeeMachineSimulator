#pragma once
#include "Actuator.h"

bool Boiler::getStatus() {
	return this->is_Boiler_On;
}

void Boiler::turn_on() {
	cout << "Boiler has been turned ON";
}

void Boiler::turn_off() {
	cout << "Boiler has been turne OFF";
}

bool PlateHeater::getStatus() {
	return this->is_plateheater_on;
}

void PlateHeater::turn_on() {
	cout << "PlateHeater has been turned ON, ";
}

void PlateHeater::turn_off() {
	cout << "PlateHeater has been turned OFF, ";
}

bool Light::getStatus() {
	return this->is_light_on;
}

void Light::turn_on() {
	cout << "Light has been turned ON, ";
}

void Light::turn_off() {
	cout << "Light has been turned OFF, ";
}

bool Valve::getStatus() {
	return this->is_valve_open;
}

void Valve::open() {
	cout << "Valve has been OPENED, ";
}

void Valve::close() {
	cout << "Valve has been CLOSED, ";
}


Open_Close_Valve_Adapter::Open_Close_Valve_Adapter(Valve* valve) {
	this->valve = valve;
}

bool Open_Close_Valve_Adapter::getStatus() {
	return valve->getStatus();
}

void Open_Close_Valve_Adapter::turn_on() {
	valve->close();
}

void Open_Close_Valve_Adapter::turn_off() {
	valve->open();
}

Actuator* Actuator_Factory::get_actuator(string actuator_type) {

	for (int i = 0; i < actuator_type.length(); i++) {
		actuator_type[i] = tolower(actuator_type[i]);
	}

	Actuator* actuator = NULL;

	if (actuator_type == "plate_heater") {
		actuator = new PlateHeater();
	}
	else if (actuator_type == "light") {
		actuator = new Light();
	}
	else if (actuator_type == "boiler") {		
		actuator = new Boiler();
	}
	else if (actuator_type == "valve") {
		Valve* valve = new Valve();
		actuator = new Open_Close_Valve_Adapter(valve);
	}
	else {
		cout << "The actuator provided is not a valid actuator. Please choose a valid actuator from the list : [plate_heater, light, boiler, valve]";
		//throw runtime_error("Invalid actuator name provided");
	}

	return actuator;
}