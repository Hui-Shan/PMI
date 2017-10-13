#include <iostream>
#include "../../std_lib_facilities.h"
#include "../Ch10Files/Reading.h"

const double magic_non_temp_const = -99999.0;

double Celsius_to_Fahrenheit(double temp_in_Celsius)
// Returns the temperature in Celsius in Fahrenheit units
{
	double temp_in_Fahrenheit = (temp_in_Celsius * 9.0 / 5.0) + 32.0;
	return temp_in_Fahrenheit;
}

vector<Reading> readings_from_file(string ifile)
// Function reads in value from ifile for temperatures, where temperatures are 
// converted into Fahrenheit
{
	vector<Reading> vec_out;
	char vec_unit = 'F';
	ifstream ifs{ ifile };
	if (!ifs) error("Could not open ", ifile);
	int hour;
	double temp; 
	char unit; 
	while (ifs >> hour >> temp >> unit) {
		if (unit == 'C') {
			temp = Celsius_to_Fahrenheit(temp);
		}
		vec_out.push_back(Reading{ hour, temp, vec_unit });
	}
	return vec_out;
}

vector<double> get_temps(vector<Reading> reading_vec) 
// Function gathers all temperature values from vector of Readings in a vector
{
	vector <double> temp_vec;
	for (Reading x : reading_vec) {
		temp_vec.push_back(x.temperature);		
	}
	return temp_vec;
}

double mean(vector<double> vec_in) 
// Function returns the mean of the vector values in vec_in
// It sums over all elements and divides by the length of the vector
{
	double sum = 0.0; // start with zero sum 
	for (double x : vec_in) {
		sum += x;
	}
	return (sum / vec_in.size());
}

double median(vector<double> vec_in)
// Function returns the median of the vector values in vec_in
// It sorts the vector's elements, and takes the value of the middle element 
// if the number of elements is uneven, otherwise the average of the two middle
// elements
{
	double median_temp = magic_non_temp_const;
	int n_temps = vec_in.size();
	sort(vec_in.begin(), vec_in.end());
	if (n_temps % 2 == 1){
		median_temp = vec_in[n_temps / 2];
	}
	else {
		median_temp = 0.5 * (vec_in[n_temps / 2] + vec_in[(n_temps / 2) - 1]);
	}
	
	return median_temp;
}


int main() {
	string infilename = "../Ch10Files/raw_temps.txt";
	
	// Read in from infile
	vector<Reading> file_readings = readings_from_file(infilename);
	
	vector<double> temps = get_temps(file_readings);

	double mea = mean(temps);
	double med = median(temps);
	cout << setw(25) << "Mean temperature (F) :" << setw(8) << mea << '\n'
		 << setw(25) << "Median temperature (F) :" << setw(8) << med << '\n';
	
	keep_window_open();

	return 0;
}