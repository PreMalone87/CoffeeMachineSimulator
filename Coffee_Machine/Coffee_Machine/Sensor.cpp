#pragma once
#include"Sensor.h"
#include "Sensor_Status.h"
#include "nlohmann\json.hpp"
#include <fstream>
using json = nlohmann::json;

Pressure_Sensor::Pressure_Sensor() {
	cout << "Pressure Sensor created"<<endl;
}

/*
void Pressure_Sensor::setThreshold(float threshold) {
	cout << "Setting threshold of pressure sensor to " << threshold << "that determines if the pot is full "<<endl;
}
*/

bool Pressure_Sensor::getStatus() {
	cout << "Getting Pressure Sensor Status" << endl;

	string json_file_name = "config.json";
	ifstream json_file(json_file_name);

	try {
		json_file.open(json_file_name);

		if (!json_file.is_open()) {
			throw "Error Opening file and hence exiting\n";
		}
	}
	catch (string err) {
		cout << err;
		exit(0);
	}

	json config = json::parse(json_file);
	json_file.close();

	
	float pressure_sensor_status = stof(string(config["pressure_sensor_status"]));
	float full_threshold = stof(string(config["full_pressure_sensor_threshold"]));
	float empty_threshold = stof(string(config["empty_pressure_sensor_threshold"]));


	this->pressure = pressure_sensor_status;
	this->empty_threshold = empty_threshold;
	this->full_threshold = full_threshold;

	return 1;
}

bool Pressure_Sensor::isFull() {
	getStatus();

	if (this->pressure > this->full_threshold) {
		return true;
	}

	return false;
}

bool Pressure_Sensor::isNotEmpty() {
	getStatus();

	if (this->pressure > this->empty_threshold) {
		return true;
	}

	return false;
}


bool Pressure_Sensor::getActivationStatus() {
	getStatus();

	if (this->pressure > this->empty_threshold) {
		return true;
	}

	return false;

}


On_Off_Button::On_Off_Button() {
	cout << "On_Off_Button created"<<endl;
}

bool On_Off_Button::getStatus() {
	cout << "Getting button status" << endl;

	string json_file_name = "config.json";
	ifstream json_file(json_file_name);

	try {
		json_file.open(json_file_name);

		if (!json_file.is_open()) {
			throw "Error Opening file and hence exiting\n";
		}
	}
	catch (string err) {
		cout << err;
		exit(0);
	}


	json config = json::parse(json_file);
	json_file.close();

	string val = string(config["button_status"]);

	if (val == "true") {
		this->isActivated = true;
	}
	else if (val == "false") {
		this->isActivated = false;
	}
	else {
		cout << "please enter a right value for water sensor satus : true or false, currently exiting";
		exit(0);
	}

	return 1;
}

bool On_Off_Button::getActivationStatus() {
	getStatus();
	return this->isActivated;
}


Water_Sensor::Water_Sensor() {
	cout << "Water Sensor created"<<endl;
}


bool Water_Sensor::getStatus() {
	cout << "Getting Water Sensor status" << endl;

	string json_file_name = "config.json";
	ifstream json_file;
	try {
		json_file.open(json_file_name);

		if (!json_file.is_open()) {
			throw "Error Opening file and hence exiting\n";
		}
	}
	catch(string err){
		cout << err;
		exit(0);
	}
	
	json config = json::parse(json_file);
	json_file.close();

	string val = string(config["water_sensor_status"]);

	if (val == "true") {
		this->isActivated = true;
	}
	else if (val == "false") {
		this->isActivated = false;
	}
	else {
		cout << "please enter a right value for water sensor satus : true or false, currently exiting";
		exit(0);
	}
	
	return 1;
}

bool Water_Sensor::getActivationStatus() {
	getStatus();
	return this->isActivated;
}

Sensor* Sensor_Factory::getSensor(string sensor_type) {
	for (int i = 0; i < sensor_type.length(); i++) {
		sensor_type[i] = tolower(sensor_type[i]);
	}

	Sensor* sensor=NULL;

	if (sensor_type == "water_sensor") {
		sensor = new Water_Sensor();
	}
	else if (sensor_type == "button_sensor") {
		sensor = new On_Off_Button();
	}
	else {
		cout << "Please Enter a valid sensor : water_sensor, button_sensor, pressure_sensor";
	}

	return sensor;
}


