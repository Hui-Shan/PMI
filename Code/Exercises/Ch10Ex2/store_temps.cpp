#include <iostream>
#include "../../std_lib_facilities.h"
#include "../Ch10Files/Reading.h"

void write_readings_to_file(vector<Reading> vec, string ofile) {
	ofstream ofs{ ofile };
	// check if open
	if (!ofs) error("Could not open ", ofile);

	for (int i = 0; i < vec.size(); ++i) {
		ofs << vec[i].hour << "\t" << vec[i].temperature << "\t" << vec[i].unit << "\n";
	}
	// ofs will be close automatically when disappearing from scope
}

int main() {
	
	// Make vector of Readings
	const int hours = 24;
	int N_readings = 50;

	vector<Reading> temps;
	
	for (int i = 0; i < N_readings; ++i) {
		int h = i % hours;
		// Get random temperature value in the range [0.0, 100.0]
		double temp = (rand() % 1000)/10.0;		
		char u = (rand() % 10 > 5) ? 'C' : 'F';
		temps.push_back(Reading{ h, temp, u });
		//cout << "hour: " << i << "\t temp: " << temp << "\n";
	}
	
	// And write to output text file
	// declare name of outputfile
	string outfilename = "../Ch10Files/raw_temps.txt";
	// call function to write
	write_readings_to_file(temps, outfilename);
	cout << "Readings written to " << outfilename << '\n';
	keep_window_open();
	
	return 0;
}