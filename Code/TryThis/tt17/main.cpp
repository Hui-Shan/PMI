#include "../../std_lib_facilities.h"

void sizes(char ch, int i, int* p, bool b, double d, bool* pb, double* pd, 
		   long double ld, long double* pld) {
	cout << "the size of char is " << sizeof(char) << ' ' << sizeof(ch) << '\n';
	cout << "the size of int is " << sizeof(int) << ' ' << sizeof(i) << '\n';
	cout << "the size of int* is " << sizeof(int*) << ' ' << sizeof(p) << '\n';
	cout << "the size of bool is " << sizeof(bool) << ' ' << sizeof(b) << '\n';
	cout << "the size of bool* is " << sizeof(bool*) << ' ' << sizeof(pb) << '\n';
	cout << "the size of double is " << sizeof(double) << ' ' << sizeof(d) << '\n';
	cout << "the size of double* is " << sizeof(double*) << ' ' << sizeof(pd) << '\n';
	cout << "the size of long double is " << sizeof(long double) << ' ' << sizeof(ld) << '\n';
	cout << "the size of long double* is " << sizeof(long double*) << ' ' << sizeof(pld) << '\n';
}

int main() {
	char a = 'a';
	int b = 2;
	int* c = &b;
	bool d = true;	
	double e = 5.0;
	bool* f = &d;
	double* g = &e;
	
	long double h = 394200419020312;
	long double* i = &h;

	// call function
	sizes(a, b, c, d, e, f, g, h, i);
	
	keep_window_open();
	return 0;
}