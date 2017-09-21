// Ch3nameandage.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../../../std_lib_facilities.h"


int name_age_months()
{
	cout << "Please enter your first name and age\n";
	string first_name = "???"; // string variable
							   // ("???” means “don’t know the name”)
	double age = -1.0; // integer variable (–1 means “don’t know the age”)
	cin >> first_name >> age; // read a string followed by an integer
	cout << "Hello, " << first_name << " (age in months " << age*12.0 << ")\n";
	
	return 0;
}

int n_calcs()
{
	cout << "Please enter an integer value: ";
	int n;
	cin >> n;
	cout << "n == " << n
		<< "\nn+1 == " << n + 1
		<< "\nthree times n == " << 3 * n
		<< "\ntwice n == " << n + n
		<< "\nn squared == " << n*n
		<< "\nhalf of n == " << n / 2
		<< "\nsquare root of n == " << sqrt(double(n))
		<< '\n'; // another name for newline (“end of line”) in output
	
	return 0;
}

int repeated_words()
{
	string previous = " "; // previous word; initialized to “not a word”
	string current; // current word
	while (cin >> current) { // read a stream of words
		if (previous == current) // check if the word is the same as last
			cout << "repeated word: " << current << '\n';
		previous = current;
	}
	return 0;
}

int main()
{
	// name_age_months();
	// n_calcs();
    //repeated_words();
	int a;
	cin >> a;
	char c = a; // try to squeeze a large int into a small char
	int b = c;
	if (a != b) // != means “not equal”
		cout << "oops!: " << a << "!=" << b << '\n';
	else
		cout << "Wow! We have large characters\n";

	return 0;
}

