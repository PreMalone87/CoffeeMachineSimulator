#pragma once
#include<iostream>
#include "Actuator.h"
#include "Sensor_Status.h"
#include "Consumer_Simulator.h"
using namespace std;

//Multiple fields are present. Not going for composition (making every field compulsory) since controler is aseperate enity and so are the actuators.
//Gonna opt for builder pattern since it gives option o add or neglect any field



class Controller {

	POT_STATUS potStatus;
	bool waterStatus;
	bool buttonStatus;

	Actuator* valve_adapter;
	Actuator* light;
	Actuator* plate_heater;
	Actuator* boiler;

	string current_state;
	//Consumer_Simulator* consumer_simulator;

public:

	Controller() {
		cout << "Controller created\n";
		this->current_state = "None";
	}
	void setBrewState();
	void setOffState();
	void setWarmerState();
	void setEmptyBoilerState();
	void setState();

	void setPotStatus(POT_STATUS potStatus);
	void setWaterStatus(bool waterStatus);
	void setButtonStatus(bool buttonStatus);

	void set_valve_adapter(Actuator* actuator);
	void set_light(Actuator* light);
	void set_heater(Actuator* heater);
	void set_boiler(Actuator* boiler);

	void set_current_state(string state);
	string get_current_state();
	//void setConsumerSimulator(Consumer_Simulator* consumer_simulator);


	//ignoring telescopic constructor and preferring Builders
	//Controller(Actuator* valve_adapter, Actuator* light, Actuator* heater, Actuator* boiler);

};

class Controller_Builder {
	Controller* controller;
public:
	Controller_Builder() {
		controller = new Controller();
		cout << "New controller builder created in controller"<<endl;
	}

	Controller_Builder* set_valve_adapter(Actuator* actuator);
	Controller_Builder* set_light(Actuator* light);
	Controller_Builder* set_heater(Actuator* heater);
	Controller_Builder* set_boiler(Actuator* boiler);
	//Controller_Builder* set_consumer_simulator(Consumer_Simulator* consume_simulator);

	Controller* get_Controller();
};


