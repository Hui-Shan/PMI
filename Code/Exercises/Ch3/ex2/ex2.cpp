// ex2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../../std_lib_facilities.h"

double conversion_factor = 1.609;

double get_kilometers(double miles) 
{
	return (miles * conversion_factor);
}

int main()
{
	double miles_in = 0.0;
	double km_out = 0.0;
	cout << "Enter the number of miles:\n";
	cin >> miles_in;
	if (miles_in > 0.0)
	{
		km_out = get_kilometers(miles_in);				
	}
	cout << miles_in << " miles is equal to " << km_out << " km.\n";
	return 0;
}

