# include "my.h"
# include "../../std_lib_facilities.h"

void swap_v(int a, int b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void swap_r(int& a, int& b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}

// does not compile, const references cannot be edited
/* 
void swap_cr(const int& a, const int& b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}
*/ 

void drill1() {
	int foo = 7;
	print_foo();
	print(99);
}

namespace X {
	int var;
	void print() {
		cout << var << '\n';
	}
}

namespace Y {
	int var;
	void print() {
		cout << var << '\n';
	}
}

namespace Z {
	int var;
	void print() {
		cout << var << '\n';
	}
}

void drill2() {
	X::var = 7;
	X::print();

	using namespace Y;
	var = 9;
	print();
	{
		using Z::var;
		using Z::print;
		var = 11;
		print();
	}
	print();
	X::print();
}


int main() {
	char cc;
	cin >> cc;

	//drill1();
	drill2();

	keep_window_open("~~");
	return 0;
}