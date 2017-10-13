#include "../../std_lib_facilities.h"
#include <string>
#include <iostream>

class Name_pair {
public:
	// constructor declaration
	Name_pair(string na, double ag);

	// non-modifying operations, as inline functions
	string get_name() const { return name; } 
	double get_age() const { return age; }

private:
	string name;
	double age;

};


Name_pair::Name_pair(string na, double ag)
	:name{ na }, age{ ag }
{
}

bool operator==(Name_pair one, Name_pair another)
// Function checks for equality between own and other Name_pair objects
// Returns true if equal
{
	return ((one.get_name() == another.get_name()) && 
			(one.get_age() == another.get_age()));
}

bool operator!=(Name_pair one, Name_pair another)
// Function checks for inequality between own and other Name_pair objects
// Returns true if unequal
{
	return !(one==another);
}

std::ostream& operator<<(std::ostream& os, Name_pair np) 
// Function for adding np to outputstream and returning output stream
{
	return os << np.get_name() << " (" << np.get_age() << ") ";
}


class Name_pairs {
private:
	vector<string> name;
	vector<double> age;

	

public:
	void read_names();
	void read_ages();	
	void sort();	

	vector<string> get_names() { return name; }
	vector<double> get_ages() { return age; }
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

std::ostream& operator<<(ostream& os, Name_pairs nps)
	// Function prints out the name, age pairs
{
	//cout << "So, you mean:\n";
	for (int i = 0; i < nps.get_names().size(); ++i) {
		os << nps.get_names()[i] << " is " << nps.get_ages()[i] << "\n";
	}
	return os;
}

/*void Name_pairs::print()
// Function prints out the name, age pairs
{
	cout << "So, you mean:\n";
	for (int i = 0; i < name.size(); ++i) {
		cout << name[i] << " is " << age[i] << "\n";
	}
}*/


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
	
	/*string n = "Eliza";
	double a = 29.;
	Name_pair np = Name_pair(n, a);
	
	cout << np;*/

	Name_pairs nps = Name_pairs();	
		
	nps.read_names();
	nps.read_ages();

	nps.sort();
	cout << nps;

	keep_window_open();
	
	return EXIT_SUCCESS;
}