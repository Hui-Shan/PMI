#ifndef IMAGE_H
#define IMAGE_H

#include "../std_lib_facilities.h"
#include "ImageIOBase.h"

namespace hmc {
	class Image
	{
	public:
		// Internally used data types
		typedef short T;
		typedef std::array<int, N_DIM> dimension;

		// STL container and iterator typedefs
		typedef T         value_type;
		typedef T*        iterator;
		typedef const T*  const_iterator;
		typedef T&        reference;
		typedef const T&  const_reference;

		// Constructors and destructor
		Image(dimension);
		Image(const Image&);
		Image(Image&&);

		virtual ~Image();

		// Assignment operators
		Image& operator=(const Image&);
		Image& operator=(Image&&);

		// Basic iterators, this generates a C4996 error in Visual Studio.
		// Disable that in main.cpp with: #pragma warning(default:4996) 
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;

		// Size and resize
		dimension size() const;                 // the dimension object
		unsigned int dim(unsigned int d) const; // get the size of a dimension
		unsigned int nr_dims() const;           // number of dimensions > 1
		void resize(const dimension& d);        // resize this image

												// Pixel value lookup, should support out-of-image coordinates by clamping to 0..dim
		value_type operator()(int x = 0, int y = 0, int z = 0, int c = 0, int t = 0) const;
		reference operator()(int x = 0, int y = 0, int z = 0, int c = 0, int t = 0);

	private:
		dimension _dimensions;
		T* _data;
	};

}

#endif /* IMAGE_H */