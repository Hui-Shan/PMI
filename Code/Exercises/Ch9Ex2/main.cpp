#include "../../std_lib_facilities.h"
#include <string>
#include <iostream>

class Name_pairs {
private:
	vector<string> name;
	vector<double> age;

public:
	void read_names();
	void read_ages();	
	std::ostream& operator<<(std::ostream& os);
	void print();
	void sort();
};

void Name_pairs::read_names()
	// Function handles in the input of the names entered via command
	// line until [Enter]
{
	cout << "Type in the names and end input with [Enter]:\n";

	string new_name;
	while (cin.peek() != '\n') {
		cin >> new_name;
		name.push_back(new_name);
	}
}

void Name_pairs::read_ages() {
	// Function handles in the input of the ages entered via command
	// line by prompting for all names
	double new_age;
	for (int i = 0; i < name.size(); ++i) {
		cout << "How old is " << name[i] << "?\n";
		cin >> new_age;
		age.push_back(new_age);
	}
}

std::ostream& Name_pairs::operator<<(ostream& os, const Point& p)
	// Function prints out the name, age pairs
{
	cout << "So, you mean:\n";
	for (int i = 0; i < name.size(); ++i) {
		cout << name[i] << " is " << age[i] << "\n";
	}
	return os << "(" << p.x << "," << p.y << ")";
}

void Name_pairs::print()
// Function prints out the name, age pairs
{
	cout << "So, you mean:\n";
	for (int i = 0; i < name.size(); ++i) {
		cout << name[i] << " is " << age[i] << "\n";
	}
}


void Name_pairs::sort() 
	// Function sorts the name and age vectors by name (alphabetically)
{
	vector<string> sorted_name = name;
	vector<double> sorted_age = age;

	// sort name vector
	std::sort(sorted_name.begin(), sorted_name.end());

	// get corresponding ages to sorted_age vector
	for (int i = 0; i < sorted_name.size(); ++i) {
		for (int j = 0; j < name.size(); ++j) {
			if (sorted_name[i] == name[j]) {
				sorted_age[i] = age[j];
			}
		}
	}	
	
	// set sorted vectors in place of original vectors
	name = sorted_name;
	age = sorted_age;

}

int main() {
	Name_pairs np = Name_pairs();	
		
	np.read_names();
	np.read_ages();

	np.sort();
	cout << np;

	keep_window_open();
	
	return EXIT_SUCCESS;
}