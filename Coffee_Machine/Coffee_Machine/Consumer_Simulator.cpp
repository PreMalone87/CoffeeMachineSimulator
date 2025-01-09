#include "Consumer_Simulator.h"

void Consumer_Simulator::run() {

		//Prev values are fetched from config file so that any change user does can also be considered
		string json_file_name = "config.json";

		ifstream json_file(json_file_name);
		json config = json::parse(json_file);
		
		json_file.close();

		float empty_sensor_pressure_threshold = stof(string(config["empty_pressure_sensor_threshold"]));
		float full_pressure_sensor_threshold = stof(string(config["full_pressure_sensor_threshold"]));
		float pressure_sensor_status = stof(string(config["pressure_sensor_status"]));
		int remaining_water_level_time = stof(string(config["remiaining_water_level_time"]));


		//**************************for the enitire calculation 20 seconds is assumed as the time taken to fill the pot*******************************

		//Calculating remaining time to fill pot
		this->remaining_time_to_fill_pot = 4 * (full_pressure_sensor_threshold - pressure_sensor_status);

		//Calculating presure increase due to conffee filling
		this->pressure_level = pressure_sensor_status + 0.25;

		//Calculating remaining time to empty the boiler water
		this->boiler_water_level_remaining_time = remaining_water_level_time - 1;


		cout << "Remaining time to fill pot is : " << this->remaining_time_to_fill_pot << " seconds" << endl;
		cout << "Boiler water can sustain for more : " << this->boiler_water_level_remaining_time << " seconds" << endl;

		//no need to do the below one since it prediction of full state is automatically done by the controller, just adjusting pressure is enough
		//check if pressure level is greater than the full_threshold (pot is full)

		if (this->pressure_level >= full_pressure_sensor_threshold) {

			cout << "Pot is full!!!" << endl;
		}
		if (this->boiler_water_level_remaining_time <= 0) {
			config["water_sensor_status"] = "false";
		}

		//updating the variable
		config["pressure_sensor_status"] = to_string(this->pressure_level);
		config["remiaining_water_level_time"] = to_string(this->boiler_water_level_remaining_time);


		//Update config file with latest value ( calculated for 1 second since scheduler follows 1 second checking)
		ofstream ofs("config.json", ios_base::trunc);

		if (!ofs.is_open()) {
			cout << "Unable to open file \n";
		}

		ofs << std::setw(4) << config << std::endl;
		ofs.close();

	
}

Consumer_Simulator::Consumer_Simulator() {

	cout << "Consumer Simulator created" << endl;
	this->boiler_water_total_time = 40; 
	//JsonObject^ jsonObject = JsonObject::Parse(jsonString);

}