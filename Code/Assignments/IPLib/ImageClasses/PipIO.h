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
		PipIO(string file_in) : ImageIOBase(file_in) { filename = file_in; };

		vector<short> read() override;
		void write(const vector<short>&, const array<int, N_DIM>&) override;
		string get_filename() { return filename; };

	protected:
		string filename;

	};

	// Functions for PipIO class	
	vector<short> PipIO::read()
		// Function that reads in the file specified by filename and returns the
		// image data into vector
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

	void PipIO::write(const vector<short>& image, const array<int, N_DIM>& dimensions)
		// Function writes pip image to filename
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


}

