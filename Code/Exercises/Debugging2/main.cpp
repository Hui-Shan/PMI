#include "../../std_lib_facilities.h"

int main() {
	int a, b;
	cout << "Enter two integers >";
	cin >> a >> b;

	if (a == b) {
		cout << "They are Equal!" << endl;
	}
	else if (a > b) {
		cout << "The first one is bigger!" << endl;
	}
	else {
		cout << "The second one is bigger!" << endl;
	}

	a = a; b = b; // Dummy code for extra pause
	keep_window_open();
}