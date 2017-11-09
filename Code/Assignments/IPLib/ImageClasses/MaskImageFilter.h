#ifndef MASKIMAGEFILTER_H
#define MASKIMAGEFILTER_H

#include "ImageFilter.h"

namespace hmc {
	
	class MaskImageFilter : public ImageFilter
	{
		typedef short T; // all we do is short
	public:
		// Constructor.
		MaskImageFilter() : _mask{} {};

		// Destructor. Removes pointers to _input and _mask
		~MaskImageFilter() { };

		// Set the mask image for the filter
		void setInputMask(const Image& m) {
			_mask = Image(m);
		}

		// Get the output image result of this filter; 
		// available after calling update()
		Image getOutput() const { return _output; };
		
		// Update the image filter and compute the output
		virtual void update()
		{
			// Didn't touch _input, cast it back to const; then execute()			
			execute(getInput());
		}

	protected:
		// Container for the output image
		// Image _output;

		// This method should be overloaded in your derived class and implement the
		// image filter that fills _output
		virtual void execute(const Image& im) {
			// Clear and resize the output
			Image::dimension imdim = im.size();
			_output = Image(imdim);

			if (imdim != _mask.size())
				error("Image and mask size do not match!");
			
			// Do the masking with a predicate function
			try {
				transform(im.begin(), im.end(), _mask.begin(), _output.begin(),
						  [](T imval, T maskval) { return imval * (maskval != 0); });
			}
			catch (exception& e) {
				cout << e.what() << "\n";
			}
		};

	private:
		// Temporary storage of a pointer to the image data. Because we do some
		// const-magic, we keep it private.		
		Image _mask;
	};	

}

#endif /* MASKIMAGEFILTER_H */
