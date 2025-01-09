#pragma once
#include "Scheduler.h"
#include <windows.h>
#include <chrono>
#include<thread>


Scheduler::Scheduler(Monitor* pot_monitor, Monitor* water_monitor, Monitor* button_monitor, Consumer_Simulator* consumer_simulator) {
	cout << "Scheduler has been invoked"<<endl;
	this->pot_monitor = pot_monitor;
	this->water_monitor = water_monitor;
	this->button_monitor = button_monitor;
	this->consumer_simulator = consumer_simulator;
}

void Scheduler::schedule() {

	while (true) {

		//Pot monitor fetching and updation
		pot_monitor->trigger();
		pot_monitor->updateController();

		//Water Monitor fetching and updation
		water_monitor->trigger();
		water_monitor->updateController();

		//Button Monitor fetching and updation
		button_monitor->trigger();
		button_monitor->updateController();

		//invoke controller
		Monitor::controller->setState();

		if (Monitor::controller->get_current_state() == "brew_state") {
			consumer_simulator->run();
		}
		

		this_thread::sleep_for(chrono::milliseconds(1000));
	}
	
}
