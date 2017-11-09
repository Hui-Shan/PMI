#ifndef THRESHOLDIMAGEFILTER_H
#define THRESHOLDIMAGEFILTER_H

#include "ImageFilter.h"

namespace hmc {
	class ThresholdImageFilter : public ImageFilter
	{
		typedef short T;
	public:
		// Constructor that initializes the threshold at 0
		ThresholdImageFilter() : _t(0) {}

		// Destructor
		~ThresholdImageFilter() { };

		// Get and set functions for the threshold value
		T getThreshold() const { return _t; }
		void setThreshold(T threshold) { _t = threshold; }

	protected:		
		// Override the execute function
		virtual void execute(const Image& im) override
		{
			// Clear and resize the output
			_output = Image(im.size());

			// Bring the threshold parameter within scope, so it can be given to
			// the lambda initializer
			const auto t = _t;

			// Do the thresholding with an std::transform, see Chapter 21			
			transform(im.begin(), im.end(), _output.begin(),
				[t](T value) {return value > t ? T(1) : T(0); }
			);
		}

	private:
		// The threshold
		T _t;
	};

}

#endif /* THRESHOLDIMAGEFILTER_H */