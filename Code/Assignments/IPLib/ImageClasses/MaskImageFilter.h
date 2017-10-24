#ifndef MASKIMAGEFILTER_H
#define MASKIMAGEFILTER_H

#include "ImageFilter.h"

namespace hmc {
	class MaskImageFilter : public ImageFilter {
		typedef short T; // all we do is short
	public:
		// Constructor.
		MaskImageFilter() {};

		// Destructor. This class does not own any free store allocated objects; 
		// but derived classes might, so it's virtual and empty
		virtual ~MaskImageFilter() {};



	protected:

	private:
	};
}

#endif
