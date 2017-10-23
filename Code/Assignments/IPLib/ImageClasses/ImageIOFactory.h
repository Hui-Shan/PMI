#include "ImageIOBase.h"
#include "PipIO.h"
#include "MhdIO.h"

class ImageIOFactory
{
public:
	static ImageIOBase* getIO(const string& filename);
};

ImageIOBase* ImageIOFactory::getIO(const string& filename) 
{	
	int index = filename.find_last_of(".");
	std::string ext = filename.substr(index);
	if (ext == ".pip") {
		PipIO *img_ptr = NULL;
		img_ptr = new PipIO(filename);
		return img_ptr;
	}
	else {
		MhdIO *img_ptr = NULL;
		img_ptr = new MhdIO(filename);
		return img_ptr;
	}
	
}

