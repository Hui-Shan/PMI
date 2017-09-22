#include "../../std_lib_facilities.h"

int main()
{
	double val1;
	double val2;
	char oper;

	cout << "Enter two operands and a operator (double, double, char):\n";
	
	while (cin >> val1 >> val2 >> oper)
	{
		switch (oper)
		{
			case '+':
				cout << "The sum of " << val1 << " and " << val2 << " is " << val1 + val2 
					<< '\n';
				break;
			case '-':
				cout << val1 << " minus " << val2 << " is " << val1 - val2 << '\n';					
				break;
			case '*':
				cout << "The product of " << val1 << " and " << val2 << " is " 
					 << val1 * val2 << '\n';
				break;
			case '/':
				cout << "The ratio of " << val1 << " and " << val2 << " is "
					<< val1 / val2 << '\n';
				break;
		}
		cout << "Enter two operands and a operator (double, double, char):\n";
	}
	
	keep_window_open();

	return 0;
}