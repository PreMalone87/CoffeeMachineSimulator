#pragma once

/*
#include<iostream>
#include "Controller.h"
#include"Sensor.h"
using namespace std;



class Monitor{

//protected:
	//static Controller* controller;
	bool test;
public:
	//Monitor();
	virtual void trigger() = 0;
	virtual void updateController() = 0;
};




class Pot_Monitor : public Monitor {

	Pressure_Sensor* pressure_sensor;
	POT_STATUS pot_status;

public:

	
	Pot_Monitor(Pressure_Sensor* pressure_sensor);

	//fetches the pressure sensor value from Pressure Sensor and sets the pot status
	void trigger();

	//calls the setPotStatus() in Controller 
	void updateController();
};

class Water_Monitor : public Monitor {
	Sensor* water_sensor;
	bool water_sensor_status;
public:

	Water_Monitor(Sensor* water_sensor);

	//fetches the water sensor status from Water Sensor and sets the pot status
	void trigger();

	void updateController();
};

class Button_Monitor : public Monitor {
	Sensor* button_sensor;
	bool button_sensor_status;
public:

	Button_Monitor(Sensor* button_sensor);

	void trigger();
	void updateController();
};

class Monitor_Factory_Interface {

public:
	
	virtual Monitor* get_Monitor(string monitor_type)=0;
	
};

class Monitor_Factory_Regular_Sensors{

public:
	Monitor* get_Monitor(string monitor_type);
};

*/


#pragma once
#include<iostream>
#include "Controller.h"
#include "Sensor.h"

using namespace std;

class Monitor {
protected:
	//bool test;
	static Controller* controller;
public:
	static void setController(Controller* controller);
	virtual void trigger() = 0;
	virtual void updateController() = 0;

	friend class Scheduler;
};

class Pot_Monitor : public Monitor {
	Pressure_Sensor* pressure_sensor;
	POT_STATUS pot_status;

public:
	Pot_Monitor(Pressure_Sensor* pressure_sensor);

	//fetches the pressure sensor value from Pressure Sensor and sets the pot status
	void trigger();

	//calls the setPotStatus() in Controller 
	void updateController();
};

class Water_Monitor : public Monitor {
	Sensor* water_sensor;
	bool water_sensor_status;

public:
	Water_Monitor(Sensor* water_sensor);

	//fetches the water sensor status from Water Sensor and sets the pot status
	void trigger();

	void updateController();
};

class Button_Monitor : public Monitor {
	Sensor* button_sensor;
	bool button_sensor_status;

public:
	Button_Monitor(Sensor* button_sensor);

	void trigger();
	void updateController();
};

class Monitor_Factory_Interface {
public:
	virtual Monitor* get_Monitor(string monitor_type) = 0;
};

class Monitor_Factory_Regular_Sensors : public Monitor_Factory_Interface {
public:
	Monitor* get_Monitor(string monitor_type);
};
