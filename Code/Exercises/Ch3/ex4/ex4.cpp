// ex4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../../std_lib_facilities.h"

int get_smallest_value(int val1, int val2)
{
	int smallest_value = val1;
	
	if (val1 > val2) 
	{
		smallest_value = val2;
	}
	return smallest_value;
}

int get_largest_value(int val1, int val2)
{
	int largest_value = val1;
	if (val1 < val2)
	{
		largest_value = val2;
	}
	return largest_value;
}

int get_sum(int val1, int val2)
{
	return (val1 + val2);
}

int get_difference(int val1, int val2) 
{
	return (val1 - val2);
}

int get_product(int val1, int val2)
{
	return (val1 * val2);
}

int get_ratio(int val1, int val2)
{
	return (val1 / val2);
}

int main()
{
	int value1 = 0;
	int value2 = 0;

	cout << "Enter first integer value:\n";
	cin >> value1;

	cout << "Enter second integer value:\n";
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

