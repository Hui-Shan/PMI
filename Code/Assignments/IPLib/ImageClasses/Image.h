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
		
		// HK: default constructor leaves an invalid _data pointer
		// default constructor
		Image() {			
			_dimensions = {};
			_data = nullptr; 
		};

		// constructor with dimension
		Image(dimension di) : _dimensions(di) {			
			// get number of voxels
			int num = 1;
			for (int x : di) num *= x;			
			
			// allocate space for that number of voxels
			_data = new T[num];
			for (int i = 0; i < num; ++i) _data[i] = 0;
		};		

		// HK: Copy constructor is incorrect: only copies the pointer and not the actual data
		// copy constructor
		Image(const Image& im) : _dimensions(im._dimensions) {			
			int num = im.num_voxels();
			_data = new T[num];									
			for (int i = 0; i < num; ++i) _data[i] = im._data[i];									
		};
		
		// HK: Move constructor is incorrect: doesnt make the other image empty
		// Move constructor
		Image(Image&& im) : _dimensions(im._dimensions), _data(im._data) {			
			// make other image empty		    
			im._dimensions = {};
			im._data = nullptr;			
		};
		

		// HK: Destructor is incorrect doesnt delete[]
		// destructor
		virtual ~Image() { 			
			delete[] _data;			
		};
				
		// Assignment operators
		
		// HK: Copy assignment is partially correct: doesn't delete[] the old data  but does copy the new
		// Copy assignment 
		Image& operator=(const Image& im) {			
			
			int num = num_voxels();
			T* p = new T[num];
			for (int i = 0; i < num; ++i) p[i] = im._data[i];			

			// after copying, delete old data			
			delete[] _data;
			
			// and set
			_data = p;
			_dimensions = im._dimensions;
			
			return *this;
		};

		// HK: Move assignment is almost correct: doesnt reset the dimensions, but does delete the old data
		// Move assignment 
		Image& operator=(Image&& im) {
			T* p = new T[im.num_voxels()];

			delete[] _data;
			_data = im._data;
			_dimensions = im._dimensions;

			im._data = nullptr;
			im._dimensions = {};
			
			return *this;
		};

		// Basic iterators, this generates a C4996 error in Visual Studio.
		// Disable that in main.cpp with: #pragma warning(default:4996) 
		iterator begin() { 
			return _data; 
		};
		iterator end() { 
			return _data + num_voxels(); 
		};
		const_iterator begin() const { 
			return _data; 
		};
		const_iterator end() const { 
			return _data + num_voxels(); 
		}; 		

		// Size and resize
		dimension size() const { 
			return _dimensions; 
		}; // the dimension object
		
		unsigned int dim(unsigned int d) const { 
			return _dimensions[d]; 
		}; // get the size of a dimension

		unsigned int nr_dims() const { 
			int count = 0;
			for (int x : _dimensions) if (x > 1) count++;
			return count ; 
		};           // number of dimensions > 1
		
		// HK: Resize() is incorrect: doesn't update the _data to the new size
		void resize(const dimension& d) { 
			_dimensions = d; 
			int num = 1;
			for (int x : _dimensions) {
				num *= x;
			}
			_data = new T[num]; // Q: set to zeros???
		};        // resize this image
		
		// Returns number of voxels in Image
		int num_voxels() const {
			int num = 1;
			for (int x : _dimensions) num *= x;
			return num;
		};

		// Pixel value lookup, should support out-of-image coordinates by clamping to 0..dim
		value_type operator()(int x = 0, int y = 0, int z = 0, int c = 0, int t = 0) const {			
			x = clamp(x, dim(0)); 
			y = clamp(y, dim(1));
			z = clamp(z, dim(2));
			c = clamp(c, dim(3));
			t = clamp(t, dim(4));

			const int d_ind = get_data_index(x, y, z, c, t);			
			T val = _data[d_ind];
			cout << "value_type " << x << "," << y << "," << z << " : " << val << "\n";
			return val;
		};

		reference operator()(int x = 0, int y = 0, int z = 0, int c = 0, int t = 0) {
			x = clamp(x, dim(0));
			y = clamp(y, dim(1));
			z = clamp(z, dim(2));
			c = clamp(c, dim(3));
			t = clamp(t, dim(4));
			
			int ind = get_data_index(x, y, z, c, t);
			T val = _data[ind];
			cout << "reference " << x << "," << y << "," << z << " : " << val << "\n";
			return val;
		};
		
		// constant data index value
		int get_data_index(int x = 0, int y = 0, int z = 0, int c = 0, int t = 0) const {
			int xDim = _dimensions[0];
			int yDim = _dimensions[1];
			int zDim = _dimensions[2];
			int cDim = _dimensions[3];
			int tDim = _dimensions[4];
			int d_ind = (t * xDim * yDim * zDim * cDim) + (c * xDim * yDim * zDim) + (z * xDim * yDim) + (y * xDim) + x;
			return _data[d_ind];
		}

		// non-constant data index value
		int get_data_index(int x = 0, int y = 0, int z = 0, int c = 0, int t = 0) {
			int xDim = _dimensions[0];
			int yDim = _dimensions[1];
			int zDim = _dimensions[2];
			int cDim = _dimensions[3];
			int tDim = _dimensions[4];
			int d_ind = (t * xDim * yDim * zDim * cDim) + (c * xDim * yDim * zDim) + (z * xDim * yDim) + (y * xDim) + x;
			return _data[d_ind];
		}

	private:
		dimension _dimensions;
		T* _data;
		

		int clamp(int coord, unsigned int max_coord) const {			
			if (coord < 0) coord = 0;
			if (coord > max_coord - 1) coord = max_coord - 1;
			return coord;			
		}

		int clamp(int coord, unsigned int max_coord) {
			if (coord < 0) coord = 0;
			if (coord > max_coord - 1) coord = max_coord - 1;
			return coord;
		}
	};


}

#endif /* IMAGE_H */