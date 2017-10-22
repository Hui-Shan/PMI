#include "ImageIOBase.h"
#include "PipIO.h"
#include "MhdIO.h"

class ImageIOFactory
{
public:
	static ImageIOBase* getIO(const string& filename);
};

ImageIOBase* ImageIOFactory::getIO(const string& filename) {	
	std::size_t found = filename.find_last_of(".");
	string ext = filename.substr(found);
	if (ext == ".pip") {
		PipIO pipimg(filename);
		return (pipimg);
	}
	if (ext == ".mhd") {
		MhdIO mhdimg(filename);
		return mhdimg;
	}	

}

