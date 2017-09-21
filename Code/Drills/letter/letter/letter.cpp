// letter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../../../std_lib_facilities.h"

int main()
{
	cout << "Enter the first name of your friend:\n";
	string first_name = "stranger";
	cin >> first_name;
	
	cout << "Dear " << first_name << ",\n\n";  
	cout << "How have you been? I\'m good, but missing you a lot of course.\n";
	
	cout << "Enter the name of a friend to inquire about: \n";
	string friend_name = "";
	cin >> friend_name;

	cout << "Enter 'm' if this friend is male, otherwise enter 'f':\n";
	char friend_sex = 0;
	cin >> friend_sex;

	if (friend_sex == 'm')
		cout << "If you see " << friend_name << 
				" please ask him to call me.\n";
	else if (friend_sex == 'f')
		cout << "If you see " << friend_name << 
				" please ask her to call me.\n";

	cout << "Enter the age of the friend you're writing to:\n";
	int age = 0; 
	cin >> age;

	if (age <= 0 || age > 110)
	{ 
		simple_error("You're kidding!\n");
	}	
	else
	{
		cout << "I hear you just had a birthday and you are " << age << 
				" years old.\n";
		if (age < 12)
			cout << "Next year you will be " << age + 1 << ".";
		if (age == 17)
			cout << "Next year you will be able to vote.\n";
		if (age > 70)
			cout << "I hope you are enjoying retirement.\n";
	}
	cout << "\nYours sincerely,\n\n\nHui Shan\n"; 
    //keep_window_open();         // wait for a character to be entered
	
    return 0;
}

