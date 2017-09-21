// ex10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../../std_lib_facilities.h"

int main()
{
	string operation;
	double val1;
	double val2;
	double outcome;

	cout << "Input operand and two values:\n";

	cin >> operation;
	cin >> val1;
	cin >> val2;

	if (operation == "+" | operation == "plus")
		outcome = val1 + val2;
	if (operation == "-" | operation == "minus")
		outcome = val1 - val2;
	if (operation == "*" | operation == "mul")
		outcome = val1 * val2;
	if (operation == "/" | operation == "div")
		outcome = val1 / val2;

	cout << val1 << " " << operation << " " << val2 << " = " << outcome << 
			"\n";
	return 0;
}

