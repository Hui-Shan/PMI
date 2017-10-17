#include "../std_lib_facilities.h"
#include "ImagesIO.h"
#include <iostream>
#define N_DIM 5

/*
PIP:
1 byte  - unsigned char - data type (1 = unsigned char; 2 = short; 3 = int; 4 = double)
4 bytes - int - x dimension size (>= 1)
4 bytes - int - y dimension size (>= 1)
4 bytes - int - z dimension size (>= 1)
4 bytes - int - c dimension size (>= 1)
4 bytes - int - t dimension size (>= 1)
n bytes - T - image data
*/

/*
MHD:
NDims = [int]              - number of dimensions
DimSize = [list of int]    - one int per dimension; empty dimensions are skipped
ElementType = [string]     - MET_SHORT for short / int16
ElementDataFile = [string] - filename of the *.raw file, which is always located in the same
*/

const unsigned char uchar_type = 1;
const unsigned char short_type = 2;
const unsigned char int_type = 3;
const unsigned char double_type = 4;

const string ndims_str = "NDims";
const string eldatfile_str = "ElementDataFile";
const string dimsize_str = "DimSize";
const string eltype_str = "ElementType";
const string equals_str = " = ";

const string MET_SHORT = "MET_SHORT";
const string int16 = "int16";
const string path_separator = "//";

unsigned char getPIPdatatype(ifstream& filestream) 
	// Function reads the unsigned char at the start of a pip file to determine
	// the data type, and returns it
{
	unsigned char PIPdatatype;
	filestream.read(as_bytes(PIPdatatype), sizeof(unsigned char));
	
	return PIPdatatype;
}

string get_relative_filepath(string fullinputfile) 
	// Get relative folder path of fullinputfile if present
{
	string path_out;
	bool folder_in_filename = (fullinputfile.find(path_separator) != -1);
	if (folder_in_filename) {
		int path_idx = fullinputfile.find_last_of(path_separator) + 1;
		path_out = fullinputfile.substr(0, path_idx);
	}
	return path_out;
}

string get_filename(string fullinputfile) 
	// Get filename without path
{
	string short_filename = fullinputfile;
	bool folder_in_filename = (fullinputfile.find(path_separator) != -1);
	if (folder_in_filename) {
		int path_idx = fullinputfile.find_last_of(path_separator) + 1;
		short_filename = fullinputfile.substr(path_idx);
	}
	return short_filename;
}

vector<short> readPIP(const string& filename)
	// Function reads in a .pip file with filename with data type short, checking 
	// for existence of file, correctness in dimensions/number of voxels and data 
	// type
{
	// Opens the ifstream 
	ifstream ifs{ filename, ios_base::binary };
	if (!ifs) error("Could not open the input file ", filename);

	// Reads in the datatype of the file
	unsigned char datatype = getPIPdatatype(ifs);			
	
	// Throws error if datatype is not a short
	if (datatype != short_type) error(filename + "has wrong data type");	
	
	// Read in the dimensions of the file
	int Nx, Ny, Nz, Nc, Nt;
	ifs.read(as_bytes(Nx), sizeof(int));
	ifs.read(as_bytes(Ny), sizeof(int));
	ifs.read(as_bytes(Nz), sizeof(int));
	ifs.read(as_bytes(Nc), sizeof(int));
	ifs.read(as_bytes(Nt), sizeof(int));	
	
	// Throws error if any dimensions are smaller than 1
	if (Nx < 1 || Ny < 1 || Nz < 1 || Nc < 1 || Nt < 1) {
		error("Negative dimensions error\n");		
	}

	// Reads in the values of the image into a vector of shorts
	vector<short> image_vec;	
	for (short val; ifs.read(as_bytes(val), sizeof(short));) {		 
		image_vec.push_back(val);
	}

	// Throws error if the number of voxels is not the same as the product of the 
	// dimensions
	int dim_product = Nx * Ny * Nz * Nc * Nt;
	int num_voxels_read = image_vec.size();
	if (num_voxels_read != dim_product) error("Number of voxels incorrect\n");
		
	return image_vec;
}

//void writePIP(const string & filename, const array<int, N_DIM> &dimensions, const vector<short>& image)
void writePIP(const string & filename, const vector<int>& dimensions, const vector<short>& image)
{
	ofstream ofs{ filename, ios_base::binary };
	if (!ofs) error("Could not open the output file ", filename);

	// Write data type
	ofs.write(as_bytes(short_type), sizeof(unsigned char));

	// Write image dimensions		
	for (int dim : dimensions) {
		ofs.write(as_bytes(dim), sizeof(int));
	}	

	// Write image values
	for (short val : image) {
		ofs.write(as_bytes(val), sizeof(short));
	}
}

vector<short> readMHD(const string& filename) 
	// Function reads in .mhd file with filename with data type short, checking 
	// for existence of file, correctness in dimensions/number of voxels and data 
	// type
{
	// Declare output vector with image data
	vector<short> image_vec;			

	// and helper variables
	int ndims;
	vector<int> dimsize;
	
	string datafile;
	string elementtype;
	string file_path;
	string line;
	string param;
	string remainder;	

	// Open ifstream for .mhd file
	ifstream ifs_mhd{ filename };
	if (!ifs_mhd) error("Could not open ", filename);

	// Get relative folder path of filename if present
	file_path = get_relative_filepath(filename);	
	
	// Read in the number of dimensions, the dimension sizes, the element type
	// and the name of the .raw file
	while (!ifs_mhd.eof()) {
		getline(ifs_mhd, line);
		if (line.size() > 0) {
			int equals_idx = line.find_first_of(" = ");
			param = line.substr(0, equals_idx);
			remainder = line.substr(equals_idx + 3);
			if (remainder.size() == 0) error("No value for parameter " + param + "\n");
			if (param == ndims_str) {
				ndims = stoi(line.substr(equals_idx + 3));	
				cout << param << " " << ndims << "\n";
			}
			if (param == dimsize_str) {
				stringstream ss;
				ss << remainder;
				cout << param << " ";
				for (int dim; ss >> dim;) {
					if (dim < 0) error("Negative dimension found\n");
					dimsize.push_back(dim);					
					cout << dim << " ";
				}				 
			}
			if (param == eltype_str) {
				elementtype = remainder;
				if (elementtype != MET_SHORT & elementtype != int16)
					error(filename + "has wrong data type\n");
			}
			if (param == eldatfile_str) {
				datafile = file_path + remainder;				
			}			
		}		
	}		

	// Open ifstream for the .raw file
	ifstream ifs_raw{ datafile, ios_base::binary };
	if (!ifs_raw) error("Could not open ", datafile);	
	
	// and read in the image intensity values
	for (short val; ifs_raw.read(as_bytes(val), sizeof(short));) {		
		image_vec.push_back(val);
	}	

	// Throw error if the number of dimensions does not concur with the dimension
	// vector read
	if (ndims != dimsize.size()) error("Number of dimensions incorrect\n");
	
	// Throw error if the dimensions were not specified correctly to get the right
	// amount of voxels read
	int num_voxels_read = image_vec.size();
	int dim_product = 1;
	for (int dim : dimsize) {
		dim_product *= dim;
	}
	if (num_voxels_read != dim_product) error("Number of voxels incorrect\n");

	return image_vec;
}

//void writeMHD(const string & filename, const array<int, N_DIM>& dimensions, const vector<short>& image)
void writeMHD(const string & filename, const vector<int>& dimensions, const vector<short>& image)
{
	// Open .mhd output filestream
	ofstream ofs_mhd{ filename };
	if (!ofs_mhd) error("Could not open " + filename + "for output\n");

	int ndims = dimensions.size();
	string raw_filename = filename.substr(0, filename.size() - 4) + ".raw";
	stringstream dimensions_in;
	for (int dim : dimensions) {
		dimensions_in << dim << " ";
	}
	
	// Write .mhd file
	ofs_mhd << "MHD:\n";
	ofs_mhd << ndims_str << equals_str << ndims << "\n";
	ofs_mhd << dimsize_str << equals_str << dimensions_in.str() << "\n";
	ofs_mhd << eltype_str << equals_str << MET_SHORT << "\n";
	ofs_mhd << eldatfile_str << equals_str << get_filename(raw_filename) << "\n";
	
	// Open .raw output filestream	
	ofstream ofs_raw{ raw_filename, ios_base::binary };
	if (!ofs_raw) error("Could not open " + raw_filename + "for output\n");
	
	// and write image values to .raw file	
	for (short val : image) {
		ofs_raw.write(as_bytes(val), sizeof(short));
	}

}

