#ifndef IMAGE_H
#define IMAGE_H

#include "../std_lib_facilities.h"
#include "ImageIOBase.h"

#define N_DIM 5

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
		Image() {};

		Image(dimension di) : _dimensions(di) {
			int num = 1;
			for (int x : di) num *= x;
			T* _data = new T[num];
		};
		//Image(dimension di, T* da) : _dimensions(di), _data(da) {};
		Image(const Image& im) : _dimensions(im._dimensions), _data(im._data) {};
		Image(Image&& im) : _dimensions(im._dimensions), _data(im._data) {};

		virtual ~Image() {
			delete _data;
		};

		// Assignment operators
		Image operator=(const Image& im) {
			int num = 1;
			for (int x : im._dimensions) num *= x;
			
			T* p = new T[num];
			for (int i = 0; i < num; ++i) {
				p[i] = im._data[i];
			}

			_data = p;
			_dimensions = im._dimensions;

			return *this;
		};
		
		Image& operator=(Image&& im) {
			delete[] _data;
			_data = im._data;
			_dimensions = im._dimensions;

			im._data = nullptr;
			im._dimensions = dimension{};
			
			return *this;
		};

		// Basic iterators, this generates a C4996 error in Visual Studio.
		// Disable that in main.cpp with: #pragma warning(default:4996) 
		iterator begin() { return _data; };
		iterator end() { return _data; };
		const_iterator begin() const { return _data; };
		const_iterator end() const { 
			int num = 1;
			for (int x : _dimensions) num *= x;			
			return _data + num; 
		}; // BUG!!! WRONG

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
		value_type operator()(int x = 0, int y = 0, int z = 0, int c = 0, int t = 0) const {
			int ind = x;
			return _data[ind]; 
		};

		reference operator()(int x = 0, int y = 0, int z = 0, int c = 0, int t = 0) {
			int ind = get_data_index(x, y, z, c, t);
			return _data[ind];
		};

		int get_data_index(int x = 0, int y = 0, int z = 0, int c = 0, int t = 0) {
			int d_ind = x;
			return d_ind;
		}


	private:
		dimension _dimensions;
		T* _data;
	};


}

#endif /* IMAGE_H */