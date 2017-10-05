# include <string>
# include <iostream>
# include "../../std_lib_facilities.h"

void fibonacci(int x, int y, Vector<int>& v, int n) {	
	bool found_largest = false;
	if (n > 0) {		
		v.push_back(x);		
		if (n > 1) {			
			v.push_back(y);			
		}
		if (n > 2) {
			for (int i = 2; i < n; ++i) {
				int new_number = v[i - 1] + v[i - 2];
				if (new_number < 0 && !found_largest) {
					cout << "largest fibonacci number that fits in an int is " << v[i-1] 
						 << '\n';
					found_largest = true;
				}
				v.push_back(new_number);
			}			
		}
	}
}

int main() {
	Vector<int> fibonacci_numbers;
	fibonacci(1, 2, fibonacci_numbers, 100);
	
	keep_window_open();
	return 0;
}