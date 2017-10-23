#include "ImageIOBase.h"
#include "PipIO.h"
#include "MhdIO.h"

namespace hmc {
	class ImageIOFactory
	{
	public:
		static ImageIOBase* getIO(const string& filename);
	};

	ImageIOBase* ImageIOFactory::getIO(const string& filename)
		// Function returns pointer to image object of .pip or .mhd file
	{
		// find extension of filename
		int index = filename.find_last_of(".");
		std::string ext = filename.substr(index);

		// create new PipIO or MhdIO images on heap accordingly
		// and return pointer to image
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
}

