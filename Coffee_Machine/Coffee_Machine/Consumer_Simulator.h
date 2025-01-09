#pragma once
#include <iostream>
#include "nlohmann\json.hpp"
#include<fstream>
#include<string>
//#include <json/value.h>

using namespace std;
using json = nlohmann::json;

class Consumer_Simulator {
	int boiler_water_level_remaining_time;
	float pressure_level;
	int remaining_time_to_fill_pot;
	int boiler_water_total_time;

public:

	Consumer_Simulator();

	void run();
};