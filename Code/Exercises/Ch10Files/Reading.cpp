#include "Reading.h"

double Reading::Celsius_to_Fahrenheit(double temp_in_Celsius) 
	// Returns the temperature in Celsius in Fahrenheit units
{
	double temp_in_Fahrenheit = (temp_in_Celsius * 9.0 / 5.0) + 32.0;	
	return temp_in_Fahrenheit;
}

