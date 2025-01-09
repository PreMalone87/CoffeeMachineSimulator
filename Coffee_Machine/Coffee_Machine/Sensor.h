#pragma once
#include<iostream>

using namespace std;

class Sensor {
	bool isActivated;
public:
	virtual bool getActivationStatus()=0;

	//updates the isActivated var by communicating with the hardware (1 is returned if successfully updated)
	virtual bool getStatus()=0;
};


class Pressure_Sensor{
	float pressure;
	float full_threshold;
	float empty_threshold;
public:
	Pressure_Sensor();

	//void setThreshold(float threshold);

	//tells wheather if a pot is detected or not
	bool getActivationStatus();

	//tells wheather if pot is full or not
	bool isFull();
	
	bool isNotEmpty();
	
	bool getStatus();
};

class On_Off_Button : public Sensor {
	float isActivated;

public:
	On_Off_Button();

	bool getStatus();

	bool getActivationStatus();

};

class Water_Sensor : public Sensor {
	float isActivated;

public:
	Water_Sensor();

	bool getStatus();

	bool getActivationStatus();

};


class Sensor_Factory {
public:
	static Sensor* getSensor(string sensor_type);
};