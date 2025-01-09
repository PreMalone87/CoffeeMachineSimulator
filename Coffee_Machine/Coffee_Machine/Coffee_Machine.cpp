// Coffee_Machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
#include <iostream>
#include "Actuator.h"
#include "Consumer_Simulator.h"
#include "Controller.h"
#include "Hardware.h"
#include "Monitor.h"
#include "Scheduler.h"
#include "Sensor.h"
#include "Sensor_Status.h"

Controller* Monitor::controller = nullptr;

int main()
{
    std::cout << "Hello World!\n";

    
    Actuator* light = Actuator_Factory::get_actuator("light");
    Actuator* boiler = Actuator_Factory::get_actuator("boiler");
    Actuator* plateHeater = Actuator_Factory::get_actuator("plate_heater");
    Actuator* valve = Actuator_Factory::get_actuator("valve");

    Controller_Builder* controller_builder = new Controller_Builder();
    Controller* controller = controller_builder->set_boiler(boiler)->set_heater(plateHeater)->set_light(light)->set_valve_adapter(valve)->get_Controller();

    Monitor::setController(controller);

    //Pressure_Sensor* pressure_sensor = new Pressure_Sensor();

    //Sensor* button_sensor = Sensor_Factory::getSensor("button_sensor");
    //Sensor* water_sensor = Sensor_Factory::getSensor("water_sensor");


    Monitor_Factory_Regular_Sensors* monitor_factory = new Monitor_Factory_Regular_Sensors();

    Monitor* pressure_monitor = monitor_factory->get_Monitor("pressure_monitor");
    Monitor* button_monitor = monitor_factory->get_Monitor("button_monitor");
    Monitor* water_monitor = monitor_factory->get_Monitor("water_monitor");
      
    Consumer_Simulator* consumer_simulator = new Consumer_Simulator();

    Scheduler* scheduler = new Scheduler(pressure_monitor, water_monitor, button_monitor, consumer_simulator);

    scheduler->schedule();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
