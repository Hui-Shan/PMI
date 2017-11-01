#ifndef IMAGE_H
#define IMAGE_H

#include "../std_lib_facilities.h"
#include "ImageIOBase.h"

#define N_DIM 5

namespace hmc {
	// Internally used data types
	typedef short T;
	typedef std::array<int, N_DIM> dimension;

	class Image
	{
	public:
		// STL container and iterator typedefs
		typedef T         value_type;
		typedef T*        iterator;
		typedef const T*  const_iterator;
		typedef T&        reference;
		typedef const T&  const_reference;

		// Constructors and destructor
		Image() :_dimensions{}, _data{} {};
		Image(dimension di) :_dimensions(di), _data{} {};
		Image(dimension di, T* da) :_dimensions(di), _data{da} {};
		Image(const Image& im) : _dimensions(im._dimensions), _data(im._data) {};
		Image(Image&& im) : _dimensions(im._dimensions), _data(im._data) {};

		virtual ~Image() {};

		// Assignment operators
		Image& operator=(const Image& im) { 
			_dimensions = im._dimensions; 
			_data = im._data;
		};
		
		Image& operator=(Image&& im) {
			_dimensions = im._dimensions;
			_data = im._data;
		};

		// Basic iterators, this generates a C4996 error in Visual Studio.
		// Disable that in main.cpp with: #pragma warning(default:4996) 
		iterator begin() { return _data; };
		iterator end() { return _data + num_voxels(); };
		const_iterator begin() const { return _data; };
		const_iterator end() const { return _data; }; // BUG!!! WRONG

		// Size and resize
		dimension size() const { return _dimensions; }; // the dimension object
		unsigned int dim(unsigned int d) const { return _dimensions[d]; }; // get the size of a dimension
		unsigned int nr_dims() const { 
			int count = 0;
			for (int x : _dimensions) if (x > 1) count++;
			return count ; 
		};           // number of dimensions > 1
		void resize(const dimension& d) { _dimensions = d; };        // resize this image
		int num_voxels() {
			int num = 1;
			for (int x : _dimensions) num *= x;
			return num;
		};

		// Pixel value lookup, should support out-of-image coordinates by clamping to 0..dim
		value_type operator()(int x = 0, int y = 0, int z = 0, int c = 0, int t = 0) const;
		reference operator()(int x = 0, int y = 0, int z = 0, int c = 0, int t = 0);

	private:
		dimension _dimensions;
		T* _data;
	};


}

#endif /* IMAGE_H */