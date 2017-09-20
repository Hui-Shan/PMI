// ex5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../../std_lib_facilities.h"

double get_smallest_value(double val1, double val2)
{
	double smallest_value = val1;

	if (val1 > val2)
	{
		smallest_value = val2;
	}
	return smallest_value;
}

double get_largest_value(double val1, double val2)
{
	double largest_value = val1;
	if (val1 < val2)
	{
		largest_value = val2;
	}
	return largest_value;
}

double get_sum(double val1, double val2)
{
	return (val1 + val2);
}

double get_difference(double val1, double val2)
{
	return (val1 - val2);
}

double get_product(double val1, double val2)
{
	return (val1 * val2);
}

double get_ratio(double val1, double val2)
{
	return (val1 / val2);
}

int main()
{
	double value1 = 0;
	double value2 = 0;

	cout << "Enter first floating point value:\n";
	cin >> value1;

	cout << "Enter second floating point value:\n";
	cin >> value2;

	cout << "Entered values are " << value1 << " and " << value2 << "\n";

	cout << "Largest: " << get_largest_value(value1, value2) << "\n";
	cout << "Smallest: " << get_smallest_value(value1, value2) << "\n";
	cout << "Sum: " << get_sum(value1, value2) << "\n";
	cout << "Difference: " << get_difference(value1, value2) << "\n";
	cout << "Product: " << get_product(value1, value2) << "\n";
	cout << "Ratio: " << get_ratio(value1, value2) << "\n";

	return 0;
}



