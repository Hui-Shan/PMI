#include "../std_lib_facilities.h"
#include <array>

#define N_DIM 5

// Base class for all ImageIO classes, providing the read an write functions.
class ImageIOBase
{
public:	
	// virtual destructor
	virtual ~ImageIOBase() {}; 
	
	// pure virtual read and write functions
	virtual vector<short> read() = 0;
	virtual void write(const vector<short>&, const array<int, N_DIM>&) = 0;

	// don't 'copy construct'
	ImageIOBase(const ImageIOBase&) = delete;				
		
	// don't 'copy assign'
	ImageIOBase& operator=(const ImageIOBase&) = delete;	

protected:	
	// protected constructor
	ImageIOBase(string file_in) { filename = file_in; };	
	string filename;

private:

};

