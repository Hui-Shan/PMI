#include "../std_lib_facilities.h"
#define N_DIM 5
//#define short_type = 2;

// Definition of const variables
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

// Base class for all ImageIO classes, providing the read an write functions.
class ImageIOBase
{
public:
	virtual ~ImageIOBase() {}

	virtual vector<short> read() = 0;
	virtual void write(const array<int, N_DIM>&, const vector<short>&) = 0;

	// don't 'copy construct'
	ImageIOBase(const ImageIOBase&) = delete;				
		
	// don't 'copy assign'
	ImageIOBase& operator=(const ImageIOBase&) = delete;	

protected:		
	ImageIOBase(string file_in) { filename = file_in; };
	string filename;

private:
};

