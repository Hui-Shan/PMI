#ifndef IMAGEIOFACTORY_H
#define IMAGEIOFACTORY_H

#include "ImageIOBase.h"
#include "PipIO.h"
#include "MhdIO.h"
#include <memory>

namespace hmc {
	class ImageIOFactory
	{
	public:
		static unique_ptr<ImageIOBase> getIO(const string& filename);
	};

	//template<ImageIOBase*>
	unique_ptr<ImageIOBase> ImageIOFactory::getIO(const string& filename)
		// Function returns pointer to image object of .pip or .mhd file
	{
		// find extension of filename
		int index = filename.find_last_of(".");
		std::string ext = filename.substr(index);
		unique_ptr<ImageIOBase> upt;
		// create new PipIO or MhdIO images on heap accordingly
		// and return pointer to image
		if (ext == ".pip") {
			PipIO *img_ptr = NULL;
			img_ptr = new PipIO(filename);						
		}
		else {
			MhdIO *img_ptr = NULL;
			img_ptr = new MhdIO(filename);
			
		}
		upt = make_unique{ img_ptr };
	}
	
}

#endif /* IMAGEIOFACTORY_H */