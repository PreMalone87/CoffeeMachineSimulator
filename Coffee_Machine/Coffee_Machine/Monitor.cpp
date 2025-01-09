#pragma once
#include "Monitor.h"
//#include "Sensor_Status.h"
#include "Sensor.h"
#include <fstream>
#include "nlohmann\json.hpp"


using json = nlohmann::json;

//NOTE: Pressure Sensor needs to be relooked 

void Monitor::setController(Controller* controller) {
	Monitor::controller = controller;
}

Pot_Monitor::Pot_Monitor(Pressure_Sensor* pressure_sensor) {
	this->pressure_sensor = pressure_sensor;
	cout << "Pot Monitor created and pressure sensor assigned to pressure sensor monitor"<<endl;
}



void Pot_Monitor::trigger() {
	
	if (pressure_sensor->isFull()) {
		pot_status = POT_FULL;
	}
	else if (pressure_sensor->isNotEmpty() == true) {
		pot_status = POT_PRESENT;
	}
	else {
		pot_status = POT_NOT_PRESENT;
	}	

}

void Pot_Monitor::updateController() {
	controller->setPotStatus(pot_status);
}


Water_Monitor::Water_Monitor(Sensor* water_sensor) {
	this->water_sensor = water_sensor;
	cout << "Water Sensor assigned to water monitor\n";
}

void Water_Monitor::trigger() {
	this->water_sensor_status = water_sensor->getActivationStatus();
	cout << "Water Sensor value fetched\n";
}

void Water_Monitor::updateController() {
	controller->setWaterStatus(this->water_sensor_status);
}


Button_Monitor::Button_Monitor(Sensor* button_sensor) {
	this->button_sensor = button_sensor;
	cout << "Button Sensor assigned to button monitor\n";
}

void Button_Monitor::trigger() {
	this->button_sensor_status = button_sensor->getActivationStatus();
}

void Button_Monitor::updateController() {
	controller->setButtonStatus(this->button_sensor_status);
}

Monitor* Monitor_Factory_Regular_Sensors::get_Monitor(string monitor_type) {

	Monitor* monitor = NULL;

	for (int i = 0; i < monitor_type.length(); i++) {
		monitor_type[i] = monitor_type[i];
	}

	if (monitor_type == "button_monitor") {
		Sensor* button = new On_Off_Button();
		monitor = new Button_Monitor(button);
	}
	else if (monitor_type == "water_monitor") {
		Sensor* water_sensor = new Water_Sensor();
		monitor = new Water_Monitor(water_sensor);
	}
	else if (monitor_type == "pressure_monitor") {

		string json_file_name = "config.json";
		ifstream json_file(json_file_name);
		json config = json::parse(json_file);
		json_file.close();

		float full_pressure_sensor_threshold = stof(string(config["full_pressure_sensor_threshold"]));
		float empty_pressure_sensor_threshold = stof(string(config["empty_pressure_sensor_threshold"]));

		Pressure_Sensor* pressure_sensor = new Pressure_Sensor();
		monitor = new Pot_Monitor(pressure_sensor);
	}
	else {
		cout << "Please Enter a Valid monitor type : button_monitor, water_monitor, pressure_monitor\n";
	}

	return monitor;
}
