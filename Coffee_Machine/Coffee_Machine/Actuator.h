#pragma once

#include<iostream>
#include "Hardware.h"
using namespace std;

class Actuator: public Hardware {
public:
	virtual void turn_on() = 0;
	virtual void turn_off() = 0;
};

class Boiler : public Actuator {
	bool is_Boiler_On;
public:
	bool getStatus();
	void turn_on();
	void turn_off();
};

class PlateHeater : public Actuator {
	bool is_plateheater_on;
public:
	bool getStatus();
	void turn_on();
	void turn_off();
};

class Light : public Actuator {
	bool is_light_on;
public:
	bool getStatus();
	void turn_on();
	void turn_off();
};

class Valve {
	bool is_valve_open;
public:
	bool getStatus();
	void open();
	void close();
};

class Open_Close_Valve_Adapter: public Actuator{
	Valve* valve;
public:
	Open_Close_Valve_Adapter(Valve* valve);
	bool getStatus();

	//Closes the valve for brewing
	void turn_on();

	//Opens the valve to stop brewing
	void turn_off();
};

class Actuator_Factory {
public:
	static Actuator* get_actuator(string actuator_type);
};