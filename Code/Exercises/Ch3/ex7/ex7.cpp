// ex7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../../std_lib_facilities.h"

int main()
{
	string val1 = "";
	string val2 = "";
	string val3 = "";

	cout << "Enter first string:\n";
	cin >> val1;

	cout << "Enter second string:\n";
	cin >> val2;

	cout << "Enter third string:\n";
	cin >> val3;

	vector<string> v;
	v.push_back(val1);
	v.push_back(val2);
	v.push_back(val3);

	sort(v.begin(), v.end());

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}

	return 0;
}


