#include "../../std_lib_facilities.h"

struct Point {
	double x;
	double y;
};

void write_points_to_file(string oname, const vector<Point>& v) {
	ofstream ost{ oname };
	if (!ost) error("can't open output file ", oname);

	// Print point coordinate values
	for (Point pp : v) {
		ost << "(" << pp.x << "," << pp.y << ")\n";
	}
}

void fill_vector(string iname, vector<Point>& v, char terminator)
// read integers from ist into v until we reach eof() or terminator
{
	ifstream ist{ iname };
	if (!ist) error("can't open input file ", iname);

	char c1;
	double xcoo;
	char c2;
	double ycoo;
	char c3;
	while (ist >> c1 >> xcoo >> c2 >> ycoo >> c3) v.push_back(Point{ xcoo, ycoo });

	for (Point p : v) {
		cout << p.x << " " << p.y << "\n";
	}
	if (ist.eof()) return;

	// not good() and not bad() and not eof(), ist must be fail()
	ist.clear();

	char c;
	ist >> c;

	if (c != terminator) {
		ist.unget();
		ist.clear(ios_base::failbit);
	}
}

int main() {
	vector<Point> original_points;
	double px;
	double py;

	// Get coordinates for points
	cout << "Enter 7 coordinate pairs for 7 points:\n";
	while (cin >> px >> py) {
		original_points.push_back(Point{ px, py });
	}

	// Write to file
	string filename = "mydata.txt";
	write_points_to_file(filename, original_points);

	// Read point coordinate values
	vector<Point> processed_points;
	char term = '\n';
	fill_vector(filename, processed_points, term);

	for (Point pp : processed_points) {
		cout << "(" << pp.x << "," << pp.y << ")\n";
	}

	bool all_is_well = true;
	if (original_points.size() != processed_points.size()) {
		all_is_well = false;
		cout << "Number of elements differs!\n";
	}
	else {
		for (int i = 0; i < original_points.size(); ++i) {
			double origx = original_points[i].x;
			double origy = original_points[i].y;
			double procx = processed_points[i].x;
			double procy = processed_points[i].y;

			if (origx != procx || origy != procy) {
				cout << "Element differs\n";
				all_is_well = false;
			}
		}
	}
	if (!all_is_well){
		cout << "Something's wrong!\n";
	}
	else {
		cout << "All is well!\n";
	}

	keep_window_open("~~");
}