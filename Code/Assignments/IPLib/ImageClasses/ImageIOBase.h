#ifndef IMAGEIOBASE_H
#define IMAGEIOBASE_H

#include "../std_lib_facilities.h"
#include "Image.h"

namespace hmc {

	// Base class for all ImageIO classes, providing the read an write functions.
	class ImageIOBase
	{
	public:
		// virtual destructor
		virtual ~ImageIOBase() {};

		// pure virtual read and write functions
		virtual Image read() = 0;
		virtual void write(const Image&) = 0;

		// don't 'copy construct'
		ImageIOBase(const ImageIOBase&) = delete;

		// don't 'copy assign'
		ImageIOBase& operator=(const ImageIOBase&) = delete;

	protected:
		// protected constructor
		ImageIOBase(string file_in) : filename(file_in) {};
		string filename;

	private:
		Image _im;
	};
	
}

#endif /* IMAGEIOBASE_H */