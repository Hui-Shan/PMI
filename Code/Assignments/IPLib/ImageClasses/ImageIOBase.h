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

		virtual string get_filename() { return filename; };
		// pure virtual read and write functions
		virtual Image read() const = 0;		
		virtual void write(const Image&) const = 0;

		// don't 'copy construct'
		ImageIOBase(const ImageIOBase&) = delete;

		// don't 'copy assign'
		ImageIOBase& operator=(const ImageIOBase&) = delete;

	protected:
		// protected constructor
		ImageIOBase(string file_in) : filename(file_in) { };
		string filename;
	
	};
	
}

#endif /* IMAGEIOBASE_H */