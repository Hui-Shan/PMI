#include "ImageIOBase.h"
#include "PipIO.h"
#include "MhdIO.h"

class ImageIOFactory
{
public:
	static ImageIOBase* getIO(const string& filename);
};

/*ImageIOBase* ImageIOFactory::getIO(const string& filename) {	
	//ext + 
	//if (filename=="brain.pip")
	//return (filename);
	return PipIO(filename);
}*/

