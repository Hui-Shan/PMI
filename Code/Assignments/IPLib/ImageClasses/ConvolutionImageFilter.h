#define _USE_MATH_DEFINES
#include <cmath>

#ifndef CONVOLUTIONIMAGEFILTER_H
#define CONVOLUTIONIMAGEFILTER_H

#include "ImageFilter.h"

#include "math.h"
namespace hmc {
	class ConvolutionImageFilter : public ImageFilter
	{

	public:
		// Constructor.
		ConvolutionImageFilter() : _rad(0) {};
		ConvolutionImageFilter(int rad) : _rad(rad) {};

		// Destructor. This class does not own any free store allocated objects; 
		// but derived classes might, so it's virtual and empty
		virtual ~ConvolutionImageFilter() {};

		
		/*// Set the input image for this filter
		void setInput(const vector<T>& i) {
			// The input should be const. However, we cannot store it that way in our
			// base class. Therefor we cast away the const and store a pointer to the
			// original data. Upon using the input data in update(), we cast it back.
			_input = const_cast<vector<T>*>(&i);
		}

		// Get the input back as a const ref
		const vector<T>& getInput() const {
			// Didn't touch _input, cast it back to const;
			return const_cast<const vector<T>&>(*_input);
		}*/

		// Sets the radius of the Gaussian 
		void setRadius(const int radius) { _rad = radius; };


/*		// Get the output image result of this filter; 
		// available after calling update()
		vector<T> getOutput() const { return _output; };
		// Update the image filter and compute the output
		virtual void update()
		{
			// Didn't touch _input, cast it back to const; then execute()
			execute(getInput());
		}
*/
	protected:		

		// This method should be overloaded in your derived class and implement the
		// image filter that fills _output		
		virtual void execute(const Image& im) {			
			// Clear and resize the output
			_output = Image(im);
			
			unsigned int min_x;
			unsigned int max_x;
			unsigned int min_y;
			unsigned int max_y;
			unsigned int min_z;
			unsigned int max_z;
			unsigned int dimx = im.dim(0);
			unsigned int dimy = im.dim(1);
			unsigned int dimz = im.dim(2);
			unsigned int dimc = im.dim(3);
			unsigned int dimt = im.dim(4);
			T vox_val; 
			T gauss_val; 
			T vox_sum;
			int num_in_range;

			for (unsigned int t{ 0 }; t < dimt; ++t) {
				for (unsigned int c{ 0 }; c < dimc; ++c) {
					for (unsigned int z{ 0 }; z < dimz; ++z) {
						cout << im(0, 0, z, c, t) << " " << _output(0, 0, z, c, t) << " ";
						for (unsigned int y{ 0 }; y < dimy; ++y) {
							for (unsigned int x{ 0 }; x < dimx; ++x) {
								num_in_range = 0;
								vox_sum = 0.0;
								min_x = (0 < x - _rad) ? 0 : (x - _rad);
								max_x = (x + _rad > dimx - 1) ? (dimx - 1) : (x + _rad);
								min_y = (0 < y - _rad) ? 0 : (y - _rad);
								max_y = (y + _rad > dimy - 1) ? (dimy - 1) : (y + _rad);
								min_z = (0 < z - _rad) ? 0 : (z - _rad);
								max_z = (z + _rad > dimz - 1) ? (dimz - 1) : (z + _rad);
								
								for (unsigned int it_x = min_x; it_x < max_x; ++it_x) {
									for (unsigned int it_y = min_y; it_y < max_y; ++it_y) {
										for (unsigned int it_z = min_z; it_z < max_z; ++it_z) {
											vox_val = im(it_x, it_y, it_z, c, t);
											gauss_val = gauss3D(it_x, x, it_y, y, it_z, z, _rad);
											vox_sum += vox_val * gauss_val;
											num_in_range += 1; 
										}
									}
									
								}
								_output(x, y, z, c, t) = vox_sum/T(num_in_range);
								//*/
								//_output(x, y, z, c, t) = im(x, y, z, c, t);
							}
						}
					}
				}
			}


		};

		//T get_pixel_value(int x, int y, int z, int xDim, int yDim) {
		//	return (*_input)[(z * xDim + yDim) + (y * xDim) + x];
		//}

	private:
		// Temporary storage of a pointer to the image data. Because we do some
		// const-magic, we keep it private.		
		int _rad;
		
		// Function to return the Gaussian kernel value for voxel (xi, yi, zi) wrt
		// center voxel (x0, y0, z0)
		T gauss3D(int xi, int x0, int yi, int y0, int zi, int z0, double sigma=1.0) {
			T coord_sum = T(pow(xi - x0, 2) + pow(yi - y0, 2) + pow(zi - z0, 2));
			T g =  1 / (2 * M_PI * sigma) * exp(- coord_sum / pow(sigma, 2)); 
			return g;
		}
	};
}

#endif /* CONVOLUTIONIMAGEFILTER_H */

