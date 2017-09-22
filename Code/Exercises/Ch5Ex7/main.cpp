#include "../../std_lib_facilities.h"

int quadratic_formula(double a, double b, double c)
{
	double D = b*b - 4 * a * c;
	if (D < 0.0)
	{
		cout << "b*b - 4ac is smaller than zero, so no square root can be computed.\n";
	}
	else {
		double x_min = (-b - sqrt(D)) / 2 / a;
		double x_plu = (-b + sqrt(D)) / 2 / a;
		cout << "The roots are " << x_min << " and " << x_plu << '\n';
	}
	

	return 0;
}

int main()
{
	double val1;
	double val2;
	double val3;
	string message = "Enter the values for a, b and c, or Ctrl-Z + Enter to exit:\n";
	cout << message;
	while (cin >> val1 >> val2 >> val3)
	{ 
		quadratic_formula(val1, val2, val3);
		
		cout << message;

	}
	

	return 0;
}

