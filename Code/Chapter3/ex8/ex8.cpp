// ex8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../../std_lib_facilities.h"

bool is_even(int value_in)
{
	// return true if value_in is even
	return (value_in % 2 == 0);
}

int main()
{
	
	int value;
	cout << "Enter an integer value:\n";
	
	cin >> value;
	bool even = is_even(value);

	if (even)
	{
		cout << "The value " << value << " is an even number.\n";
	}
	else
	{
		cout << "The value " << value << " is an odd number.\n";
	}

	return 0;
}

