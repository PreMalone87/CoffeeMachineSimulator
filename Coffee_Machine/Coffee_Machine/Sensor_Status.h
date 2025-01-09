#pragma once

#include<iostream>

using namespace std;

//Button Sensor(bool), Water Sensor(bool), Pressure Sensor(float)

/*
extern bool button_status;

extern bool water_sensor_status;

extern float pressure_sensor_status;

extern float empty_pressure_sensor_threshold;`

extern float full_pressure_sensor_threshold;
*/

#define ON true
#define OFF false
#define PRESENT true
#define NOT_PRESENT false

enum POT_STATUS {
	POT_NOT_PRESENT,
	POT_PRESENT,
	POT_FULL
};



