#include "../../std_lib_facilities.h"

using namespace std;

const int ar_size = 10;
int ga[ar_size] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };

void f(int array_in[], const int ar_size) {
	int la[ar_size]; 	

	for (int* p = &array_in[0]; p != &array_in[ar_size - 1]; ++p) {
		cout << *p << " ";		
	}

}

int main() {
	
	//#int ga[10];
	for (int i = 0; i < 10; ++i) {
		cout << ga[i] << " "; 
	}
	f(ga, ar_size);

	return 0;
}