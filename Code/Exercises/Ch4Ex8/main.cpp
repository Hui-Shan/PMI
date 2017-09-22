#include "../../std_lib_facilities.h"

int number_of_squares(int num_grains_needed)
{
	int num_grains_so_far = 0;
	int num_squares = 1;
	while (num_grains_so_far < num_grains_needed)
	{
		//cout << p2**(num_squares - 1) << '\n';
		num_grains_so_far += pow(2, num_squares - 1);
		++num_squares;
	}
	cout << "Input number of grains needed " << num_grains_needed << '\n';
	cout << num_squares << " squares : " << num_grains_so_far << " grains.\n";
	
	return (num_squares);
}

int main()
{	
	number_of_squares(1000);
	number_of_squares(1000000);
	number_of_squares(1E9);
		
	double total_in_double = 0.0;
	int total_in_int = 0;

	cout << '\n';
	cout << "Max value for regular int: " << INT16_MAX << '\n';	
	cout << "Max value for regular double: " << DBL_MAX << '\n';
	cout << '\n';

	bool max_num_int_found = false;
	bool max_num_double_found = false;
		
	for (int i = 0; i < 64; ++i)
	{		
		if ((!max_num_int_found) && (INT16_MAX - pow(2,i) < total_in_int))
		{ 
			cout << "Max number of squares for int: " << i << '\n';
			max_num_int_found = true;
		}
		if ((!max_num_double_found) && (DBL_MAX - pow(2, i) < total_in_int))
		{
			cout << "Max number of squares for double: " << i << '\n';
			max_num_double_found = true;
		}
		total_in_int += pow(2, i);
		total_in_double += pow(2.0, i);		
	}
	
	cout << "'Total' number of grains for 64 squares in int: " << total_in_int 
		 << '\n';
	cout << "'Total' number of grains for 64 squares in double: " 
		 << total_in_double << '\n';

	keep_window_open();
	return 0;
}