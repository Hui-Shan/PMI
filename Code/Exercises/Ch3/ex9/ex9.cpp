// ex9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../../std_lib_facilities.h"

string return_string(string input)
{
	string str_out = "Not a number I know!";
	if (input == "zero")
		str_out = "0";
	else if (input == "one")
		str_out = "1";
	else if (input == "two")
		str_out = "2";
	else if (input == "three")
		str_out = "3";
	else if (input == "four")
		str_out = "4";

	return str_out;
}

int main()
{
	string value_in = "";

	cout << "Input a number in spelled out form:\n";	
	cin >> value_in;

	string response = return_string(value_in);

	cout << response << "\n";

	return 0;
}

