// ex6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../../std_lib_facilities.h"

int main()
{
	int val1 = 0;
	int val2 = 0;
	int val3 = 0;

	cout << "Enter first integer value:\n";
	cin >> val1;

	cout << "Enter second integer value:\n";
	cin >> val2;

	cout << "Enter third integer value:\n";
	cin >> val3;

	vector<int> v;
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

