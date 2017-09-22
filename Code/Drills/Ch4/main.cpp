#include "../../std_lib_facilities.h"

void read_in_ints()
{
	int val1;
	int val2;
	cout << "Enter two integer values:\n";
	while (cin >> val1 >> val2)
	{
		cout << "You entered: " << val1 << " and " << val2 << '\n';

		cout << "The smaller value is: " << min(val1, val2) << '\n';
		cout << "The larger value is: " << max(val1, val2) << '\n';
		if (val1 == val2)
		{
			cout << "The numbers are equal.\n";
		}

		// Prompt for new while loop iteration
		cout << "Enter two integer values:\n";
	}
}

void read_in_doubles()
{
	double val1;
	double val2;
	cout << "Enter two floating point values:\n";
	while (cin >> val1 >> val2)
	{
		cout << "You entered: " << val1 << " and " << val2 << '\n';

		cout << "The smaller value is: " << min(val1, val2) << '\n';
		cout << "The larger value is: " << max(val1, val2) << '\n';
		if (abs(val1 - val2) < 1.0/100)
		{
			cout << "The numbers are equal.\n";
		}

		// Prompt for new while loop iteration
		cout << "Enter two integer values:\n";
	}
}

void read_in_double()
{
	double smallest_value = DBL_MAX;
	double largest_value = -DBL_MAX;
	double cur_value;
	cout << "Enter a floating point number:\n";
	while (cin >> cur_value)
	{
		cout << "Current value: " << cur_value << '\n';
		if (cur_value < smallest_value)
		{
			smallest_value = cur_value;
			cout << "the smallest so far\n";
		}			
		if (cur_value > largest_value)
		{
			largest_value = cur_value;
			cout << "the largest so far\n";
		}					

		// Prompt for new while loop iteration
		cout << "Enter a floating point number:\n";
	}
}

void read_in_double_unit()
{
	double value;
	string unit;

	string prompt_message = "Enter a floating point length and unit "
		"('cm', 'm', 'in' or 'ft'):\n";
	
	cout << prompt_message;
	
	vector<double> values;
	while (cin >> value >> unit)
	{
		const double in_to_m = 0.254;
		const double ft_to_m = 12 * in_to_m;
		const double cm_to_m = 0.01;
		double value_in_m;

		cout << value << " " << unit << '\n';
		if (unit == "cm")
		{
			value_in_m = value * cm_to_m;
			values.push_back(value_in_m);
		}
		else if (unit == "m")
		{
			values.push_back(value);
		}
		else if (unit == "in")
		{
			value_in_m = value * in_to_m;
			values.push_back(value_in_m);
		}
		else if (unit == "ft")
		{
			value_in_m = value * ft_to_m;
			values.push_back(value_in_m);
		}
		else
		{
			cout << "Unit " << unit << " not recognized\n";
		}

		cout << prompt_message;
	}
	
	sort(values.begin(), values.end());

	cout << "Values stored in vector:\n";
	for (double x : values)
	{
		cout << x << " m\n";
	}

	double sum = 0.0;
	for (double x : values)
		sum += x;

	cout << "Smallest value: " << values[0] << '\n';
	cout << "Largest value: " << values[values.size()-1] << '\n';
	cout << "Sum: " << sum << '\n';

	keep_window_open();

}


int main() 
{		
	read_in_double_unit();
	return 0;
}
