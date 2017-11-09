#ifndef MHDIO_H
#define MHDIO_H

#include "ImageIOBase.h"

namespace hmc {
	// Define constant values
	const string ndims_str = "NDims";
	const string eldatfile_str = "ElementDataFile";
	const string dimsize_str = "DimSize";
	const string eltype_str = "ElementType";
	const string equals_str = " = ";

	const string MET_SHORT = "MET_SHORT";
	const string int16 = "int16";
	const string path_separator = "/";

	// Derived class MhdIO	
	class MhdIO : public ImageIOBase
	{
	public:
		// Constructor
		MhdIO(string file_in) : ImageIOBase(file_in) { filename = file_in; };
				
		// declaration of read and write functions
		Image read() override;		
		void write(const Image&) override;
		
	protected:
		string filename;

	private:
		string get_relative_filepath();
	};

	// Functions for MhdIO
	string MhdIO::get_relative_filepath()
		// Get relative folder path of filename if present
	{
		string path_out; // default value for path_out = ""
		bool folder_in_filename = (filename.find(path_separator) != -1);
		if (folder_in_filename) {
			int path_idx = filename.find_last_of(path_separator) + 1;
			path_out = filename.substr(0, path_idx);
		}
		return path_out;
	}

	Image MhdIO::read()
		// Reads in the image voxel values for the Mhd file named filename
	{		
		// declare helper variables
		int ndims;		
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
		file_path = get_relative_filepath();

		// Initialize all dimensions to be of at least size 1
		Image::dimension mhd_dim = { 1,1,1,1,1 };

		// Read in the number of dimensions, the dimension sizes, the element type
		// and the name of the .raw file
		while (!ifs_mhd.eof()) {
			// read in line
			getline(ifs_mhd, line);
			if (line.size() > 0) {
				// find parameter name and values
				int equals_idx = line.find_first_of(" = ");
				param = line.substr(0, equals_idx);
				remainder = line.substr(equals_idx + 3);				
				
				// check if there are values for the parameter
				if (remainder.size() == 0) error("No value for parameter " + param + "\n");

				// check which parameter name is read, and handle values accordingly
				if (param == ndims_str) {
					ndims = stoi(line.substr(equals_idx + 3));					
				}
				if (param == dimsize_str) {
					stringstream ss;
					ss << remainder;
					int dim_idx = 0;
					for (int dim; ss >> dim;) {
						if (dim < 0) error("Negative dimension found\n");						
						mhd_dim[dim_idx] = dim;
						dim_idx++;
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

		// Initialize image 
		Image im_mhd = Image(mhd_dim);
		
		// and read in the image intensity values
		Image::iterator mhd_data_it = im_mhd.begin();
		for (Image::T val; ifs_raw.read(as_bytes(val), sizeof(short));) {
			*mhd_data_it = val;
			mhd_data_it++;
		}

		// Throw error if the number of dimensions does not concur with the dimension
		// vector read		
		if (ndims != im_mhd.nr_dims()) error("Number of dimensions incorrect\n");

		// Throw error if the dimensions were not specified correctly to get the right
		// amount of voxels read
		int num_voxels_read = im_mhd.num_voxels();
		int dim_product = 1;
		for (int dim : mhd_dim) dim_product *= dim;		
		if (num_voxels_read != dim_product) error("Number of voxels incorrect\n");		
		
		return im_mhd;
	}

	void MhdIO::write(const Image& im)
	{
		// Open .mhd output filestream
		ofstream ofs_mhd{ filename };
		if (!ofs_mhd) error("Could not open " + filename + "for output\n");
		Image::dimension dimensions = im.size();
		
		// Make string listing dimension sizes		
		stringstream dimensions_in;
		for (int dim : dimensions) {
			dimensions_in << dim << " ";
		}		

		// Get full and short filenames for .raw file 
		string raw_filename = filename.substr(0, filename.size() - 4) + ".raw";
		int last_slash_index = raw_filename.find_last_of(path_separator);
		string short_raw_filename = raw_filename.substr(last_slash_index + 1);

		// Write (basic) .mhd file
		ofs_mhd << "MHD:\n";
		ofs_mhd << ndims_str << equals_str << im.nr_dims() << "\n";
		ofs_mhd << dimsize_str << equals_str << dimensions_in.str() << "\n";
		ofs_mhd << eltype_str << equals_str << MET_SHORT << "\n";
		ofs_mhd << eldatfile_str << equals_str << short_raw_filename << "\n";

		// Open .raw output filestream	
		ofstream ofs_raw{ raw_filename, ios_base::binary };
		if (!ofs_raw) error("Could not open " + raw_filename + "for output\n");
		
		// and write image values to .raw file
		for (Image::const_iterator i = im.begin(); i != im.end(); ++i) {
			ofs_raw.write(as_bytes(*i), sizeof(short));
		}
	}

}

#endif /* MHDIO_H */