#include "../../std_lib_facilities.h"

int main()
{
	cout << "Max int value is " << INT32_MAX << '\n';
	cout << "Please enter the number of values you want to sum:\n";
	int num_to_sum;
	cin >> num_to_sum;

	//cout << "Please enter some integers (press '|' to stop):\n";
	cout << "Please enter some integers (press [Enter] and [Ctrl-Z] to stop):\n";
	vector <int> values;	
	
	string num_string = "";
	int sum = 0;
	bool error_found = false;

	try {
		for (int cur_val; cin >> cur_val;)
		{
			values.push_back(cur_val);
		}		
		for (int i = 0; i < num_to_sum; ++i)
		{
			
			if ((INT32_MAX - sum) < values[i])
			{
				error_found = true;
				error("Error to store sum in int type.\n");				
			}
			else {
				sum += values[i];
				num_string += to_string(values[i]);
			}
			
			if (error_found!=0) {
				cout << "The sum of the first " << num_to_sum << " numbers ( " 
					 << num_string << ") is " << sum << ".\n";
			}
			
		}
	}
	catch (runtime_error& e) {
		cerr << "runtime error: " << e.what() << '\n';
	
	}
	catch (out_of_range) {
		cerr << "Out of range error!\n";		
	}





	keep_window_open();

	return 0;
}