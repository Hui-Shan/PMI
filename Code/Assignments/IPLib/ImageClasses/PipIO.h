#ifndef PIPIO_H
#define PIPIO_H

#include "ImageIOBase.h"

namespace hmc {
	// Define constant values for data types
	const unsigned char uchar_type = 1;
	const unsigned char short_type = 2;
	const unsigned char int_type = 3;
	const unsigned char double_type = 4;

	// Derived class PipIO
	class PipIO : public ImageIOBase
	{
	public:
		PipIO(string file_in) : ImageIOBase(file_in) { 
			filename = file_in; 
		};
		
		Image read() override;		
		void write(const Image&) override;
		string get_filename() { return filename; };

	protected:
		string filename;	

	};

	// Functions for PipIO class	
	Image PipIO::read()
		// Function that reads in the file specified by filename and returns an
		// Image object
	{
		// Opens the ifstream 
		ifstream ifs{ filename, ios_base::binary };
		if (!ifs) error("Could not open the input file ", filename);

		// Reads in the datatype of the file
		unsigned char datatype;
		ifs.read(as_bytes(datatype), sizeof(unsigned char));

		// Throws error if datatype is not a short
		if (datatype != short_type) error(filename + "has wrong data type");

		// Read in the dimensions of the file
		int Nx, Ny, Nz, Nc, Nt;
		ifs.read(as_bytes(Nx), sizeof(int));
		ifs.read(as_bytes(Ny), sizeof(int));
		ifs.read(as_bytes(Nz), sizeof(int));
		ifs.read(as_bytes(Nc), sizeof(int));
		ifs.read(as_bytes(Nt), sizeof(int));

		Image::dimension pip_dim{ Nx, Ny, Nz, Nc, Nt };

		// Throws error if any dimensions are smaller than 1
		if (Nx < 1 || Ny < 1 || Nz < 1 || Nc < 1 || Nt < 1) {
			error("Negative dimensions error\n");
		}
		
		Image im = Image(pip_dim);

		cout <<  im.begin() << im.end() << "\n";

		// Reads in the values of the image into a vector of shorts
		Image::iterator pip_data_it = im.begin();
		for (Image::T val; ifs.read(as_bytes(val), sizeof(short));) {
			*pip_data_it = val;			
			pip_data_it++;
		}
		cout << "iterated over image";

		// Throws error if the number of voxels is not the same as the product of the 
		// dimensions
		int dim_product = Nx * Ny * Nz * Nc * Nt;
		int num_voxels_read = im.num_voxels();
		if (num_voxels_read != dim_product) error("Number of voxels incorrect\n");

		return im;
	}

	void PipIO::write(const Image& im)
		// Function writes pip image to filename
	{
		ofstream ofs{ filename, ios_base::binary };
		if (!ofs) error("Could not open the output file ", filename);

		// Write data type
		ofs.write(as_bytes(short_type), sizeof(unsigned char));

		Image::dimension dims = im.size();
		
		// Write image dimensions		
		for (int dim : dims) {
			ofs.write(as_bytes(dim), sizeof(int));
		}
		
		// and the intenstiy values
		for (Image::const_iterator i = im.begin(); i != im.end(); ++i) {									
			ofs.write(as_bytes(*i), sizeof(short));
		}
	}

}

#endif /* PIPIO_H */