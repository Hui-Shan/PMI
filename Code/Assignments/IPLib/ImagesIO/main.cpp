#include "../std_lib_facilities.h"
#include "ImagesIO.h"

int main() {
	
	// For pip file	
	
	string pipFilename;
	pipFilename = "..//..//data//brain.pip";
	// pipFilename = "..//..//data//corrupt_1.pip"; // Wrong datatype (not a short)
	// pipFilename = "..//..//data//corrupt_2.pip"; // Number of voxels incorrect
	// pipFilename = "..//..//data//corrupt_3.pip"; // Negative dimension error
	
	cout << "Read in file: " << pipFilename << "\n"; 

	//cout << _getcwd(NULL, 0) << "\n";	
	//cout << "Please enter a PIP filename: " << endl;
	//cin >> pipFilename;
	
	try {
		auto pipimage = readPIP(pipFilename);
		for (auto& i : pipimage) i *= 2; // double the pixel values
		
		int vv[N_DIM] = { 109, 91, 80, 1, 1 };
		vector<int> dim_array(&vv[0], &vv[0] + N_DIM);
		string rel_path = get_relative_filepath(pipFilename);
		string out_file = rel_path + "brain_out.pip";		
		writePIP(out_file, dim_array, pipimage);
	}
	catch (std::exception &e) {
		cerr << e.what();
	}

	// for mhd file	
	string mhdFilename;
	mhdFilename = "..//..//data//brain.mhd";	
	//mhdFilename = "..//..//data//corrupt_4.mhd"; // Number of dimensions incorrect
	//mhdFilename = "..//..//data//corrupt_5.mhd"; // Number of voxels incorrect
	//mhdFilename = "..//..//data//corrupt_6.mhd"; // wrong datatype (not short)
	cout << "Read in file: " << mhdFilename << "\n";
	try {
		auto mhdimage = readMHD(mhdFilename);
		for (auto& i : mhdimage) i *= 2; // double the pixel values

		string rel_path = get_relative_filepath(mhdFilename);
		string outfile = rel_path + "brain_out.mhd";
		int vv[3] = { 109, 91, 80 };
		vector<int> dim_array(&vv[0], &vv[0] + 3);
		writeMHD(outfile, dim_array, mhdimage);
	}
	catch (std::exception &e) {
		cerr << e.what();
	}

	keep_window_open();
	return 0;
}