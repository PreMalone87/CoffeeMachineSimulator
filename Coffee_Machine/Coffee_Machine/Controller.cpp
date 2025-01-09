#pragma once
#include "Controller.h"


void Controller::setPotStatus(POT_STATUS potStatus) {
	this->potStatus = potStatus;
}

void Controller::setWaterStatus(bool waterStatus) {
	this->waterStatus = waterStatus;
}

void Controller::setButtonStatus(bool buttonStatus) {
	this->buttonStatus = buttonStatus;
}

void Controller::setBrewState() {
	this->current_state = "brew_state";
	cout << "**************BREW STATE ACTIVATED****************";
	this->boiler->turn_on();
	this->plate_heater->turn_on();
	this->light->turn_off();
	this->valve_adapter->turn_on();
}

void Controller::setWarmerState() {
	this->current_state = "warmer_state";
	cout << "****************WARMER STATE ACTIVATED**************";
	this->boiler->turn_off();
	this->plate_heater->turn_on();
	this->light->turn_off();
	this->valve_adapter->turn_off();
}

void Controller::setOffState() {
	this->current_state = "off_state";
	cout << "******************OFF STATE ACTIVATED*****************";
	this->boiler->turn_off();
	this->plate_heater->turn_off();
	this->light->turn_off();
	this->valve_adapter->turn_off();
}

void Controller::setEmptyBoilerState() {
	this->current_state = "empty_boiler_state";
	cout << "*************EMPTY BOILER STATE ACTIVATED*************";
	this->boiler->turn_off();
	this->plate_heater->turn_on();
	this->light->turn_on();
	this->valve_adapter->turn_off();
}
void Controller::set_valve_adapter(Actuator* valve_adapter) {
	this->valve_adapter = valve_adapter;
}

void Controller::set_light(Actuator* light) {
	this->light = light;
}

void Controller::set_heater(Actuator* plate_heater) {
	this->plate_heater = plate_heater;
}

void Controller::set_boiler(Actuator* boiler) {
	this->boiler = boiler;
}


void Controller::setState() {

	//bool potStatus;
	//bool waterStatus;
	//bool buttonStatus;

	//Higher priority states are at top

	cout << "Current Sensor status : \n";
	cout << "Button : " << this->buttonStatus << ", Pot Status : " << this->potStatus << ", Water Status : " << this->waterStatus << endl;

	if (this->buttonStatus == OFF) {
		cout << "Machine is OFF" << endl;
	}
	else if (this->potStatus == POT_PRESENT && this->waterStatus == PRESENT) {
		this->setBrewState();
	}
	else if (this->waterStatus == NOT_PRESENT) {
		this->setEmptyBoilerState();
	}
	else if (this->potStatus == POT_FULL) {
		this->setWarmerState();
	}
	else if (this->potStatus == POT_NOT_PRESENT) {
		this->setOffState();
	}
	else {
		cout << "Unknown State encountered \n";
		cout << "State Values: \n";
		cout << "pot status : " << potStatus << "water status : " << waterStatus << "button status : " << buttonStatus<<endl;
	}
	

}



Controller_Builder* Controller_Builder::set_valve_adapter(Actuator* valve_adapter) {
	controller->set_valve_adapter(valve_adapter);
	return this;
}

Controller_Builder* Controller_Builder::set_heater(Actuator* plate_heater) {
	controller->set_heater(plate_heater);
	return this;
}

Controller_Builder* Controller_Builder::set_boiler(Actuator* boiler) {
	controller->set_boiler(boiler);
	return this;
}

Controller_Builder* Controller_Builder::set_light(Actuator* light) {
	controller->set_light(light);
	return this;
}



Controller* Controller_Builder::get_Controller() {
	return this->controller;
}

void Controller::set_current_state(string state) {
	this->current_state = state;
}
string Controller::get_current_state() {
	return this->current_state;
}
