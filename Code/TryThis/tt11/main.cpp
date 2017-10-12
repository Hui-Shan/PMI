#include "../../std_lib_facilities.h"
#include <iostream>
#include <string>

using namespace std;

void tt_1() {
	int birth_year = 1989;
	cout << birth_year << "\t(decimal)\n"
		<< hex << birth_year << "\t(hexadecimal)\n"
		<< oct << birth_year << "\t(octal)\n";
}

void tt_2() {
	cin.unsetf(ios::dec);
	int a;
	int b;
	int c;
	int d;
	cin >> a >> hex >> b >> oct >> c >> d;
	cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';
}

void tt_3() {
	double num = 1234567.89;
	cout << num << "\t(default)\n"
		 << fixed << num << "\t(fixed)\n"
		 << scientific << num << "\t(scientific)\n";
}

void tt_4() {
	std::string last_arr[] = { "Chant", "Lensher", "Parker", "Wayne", "Ives" };
	std::string first_arr[] = { "Cat", "Eric", "Peter", "Bruce", "Vanessa" };
	std::string email_arr[] = { "c@bla.nl", "magneto@live.com",
								"friendly_neighborhood@web.com", "the_tumbler@wayne.enterprises.com",
								"miss.ives@hellion.co.uk" };

	// Initialize vector with a string array
	vector<string> last_names(last_arr, 
						last_arr + sizeof(last_arr) / sizeof(string));
	vector<string> first_names(first_arr, 
						first_arr + sizeof(first_arr) / sizeof(string));
	vector<string> emails(email_arr,
						  email_arr + sizeof(email_arr) / sizeof(string));

	for (int i = 0; i < last_names.size(); ++i) {
		string last = last_names[i];
		string first = first_names[i];
		string email = emails[i];

		cout << '|' << setw(10) << last << '|' << setw(8) << first << '|' 
			 << setw(35) << email << '|' << '\n';
	}

}

int main() {
	
	tt_4();

	keep_window_open();
	
	return 0;
}