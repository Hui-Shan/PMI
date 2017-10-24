#ifndef MASKIMAGEFILTER_H
#define MASKIMAGEFILTER_H

#include "ImageFilter.h"

namespace hmc {
	
	class MaskImageFilter : public ImageFilter
	{
		typedef short T; // all we do is short
	public:
		// Constructor.
		MaskImageFilter() {};

		// Destructor. This class does not own any free store allocated objects; 
		// but derived classes might, so it's virtual and empty
		~MaskImageFilter() {};

		// Set the input image for this filter
		void setInput(const vector<T>& i) {
			// The input should be const. However, we cannot store it that way in our
			// base class. Therefor we cast away the const and store a pointer to the
			// original data. Upon using the input data in update(), we cast it back.
			_input = const_cast<vector<T>*>(&i);
		}

		void setInputMask(const vector<T>& m) {
			_mask = const_cast<vector<T>*>(&m);
		}

		// Get the input back as a const ref
		const vector<T>& getInput() const {
			// Didn't touch _input, cast it back to const;
			return const_cast<const vector<T>&>(*_input);
		}

		// Get the output image result of this filter; 
		// available after calling update()
		vector<T> getOutput() const { return _output; };

		// Update the image filter and compute the output
		virtual void update()
		{
			// Didn't touch _input, cast it back to const; then execute()			
			execute(getInput());
		}

	protected:
		// Container for the output image
		vector<T> _output;

		// This method should be overloaded in your derived class and implement the
		// image filter that fills _output
		virtual void execute(const vector<T>& i) {
			// Clear and resize the output
			_output.clear();
			_output.resize(i.size());			

			// Do the masking with an std::transform, see Chapter 21
			transform(begin(i), end(i), _mask->begin(), begin(_output), std::multiplies<T>());		
		};

	private:
		// Temporary storage of a pointer to the image data. Because we do some
		// const-magic, we keep it private.
		vector<T>* _input;
		vector<T>* _mask;
	};	

}

#endif /* MASKIMAGEFILTER_H */
