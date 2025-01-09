#pragma once
#include<iostream>
#include "Monitor.h"
#include "Consumer_Simulator.h"

using namespace std;

class Scheduler {

	Monitor* pot_monitor;
	Monitor* water_monitor;
	Monitor* button_monitor;
	
	Consumer_Simulator* consumer_simulator;
	
public:

	Scheduler(Monitor* pot_monitor, Monitor* water_monitor, Monitor* button_monitor, Consumer_Simulator* consumer_Simulator);

	void schedule();
};
