#include "../std_lib_facilities.h"
#include <array>

#define N_DIM 5

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

