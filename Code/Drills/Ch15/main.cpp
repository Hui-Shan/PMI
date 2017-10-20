#include "../../std_lib_facilities.h"
using namespace std;

struct Person {
public:
	Person(string name_in, int age_in);
	Person() {};
	
	const string name() { return nam; };
	const int age() const { return ag; };
private:
	string nam;
	int ag;
};

Person::Person(string name_in, int age_in) : nam{ name_in }, ag{ age_in } {	
	if (age_in >= 150 || age_in < 0)
		error("Age not in range [0, 150)\n");
		
	char bad_chars[] = { ';', ':', '"', '\'' , '[', ']', '*', '&', '^' , '%', 
						 '$', '#', '@', '!' };	

	for (char ch : bad_chars) {		
		int ch_ind = name_in.find(ch);		
		if (ch_ind != -1) // hard-coded, not so pretty
			error("Found forbidden character in name\n");		
	}
}

ostream& operator<<(ostream& os, Person p) {
	os << p.name() << " (age: " << p.age() << ")\n";
	return os;
}

istream& operator>>(istream& is, Person p) {
	string nam_in;
	int ag_in;
	is >> nam_in >> ag_in;
	Person p1 = Person(nam_in, ag_in);
	return is;
}


int main() {
	vector<Person> persons;
		
	Person dummy_person;
	string dummy_name; 
	int dummy_age;
	try{
		while (cin >> dummy_name >> dummy_age) {
			dummy_person = Person(dummy_name, dummy_age);
			persons.push_back(dummy_person);
		}		
	}
	catch (const std::exception &e) {
		cout << e.what();
	}

	for (Person p : persons) {
		cout << p; 
	}
	

//	cout << p1;

	keep_window_open();
	return 0;
}