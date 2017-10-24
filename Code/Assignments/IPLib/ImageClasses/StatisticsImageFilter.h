#ifndef STATISTICSIMAGEFILTER_H
#define STATISTICSIMAGEFILTER_H

#include "ImageFilter.h"

namespace hmc {
	// Base class for all image filters to be implemented.
	class StatisticsImageFilter : public ImageFilter
	{
		typedef short T; // all we do is short
	public:
		// Constructor.
		StatisticsImageFilter() {};

		// Destructor. This class does not own any free store allocated objects; 
		// but derived classes might, so it's virtual and empty
		virtual ~StatisticsImageFilter() {};

		T getMin() { return im_min; }
		T getMax() { return im_max; }
		T getMedian() { return im_median; }

		double getNumVoxels() { return im_num_voxels; }
		double getSum() { return im_sum; }
		double getMean() { return im_mean; }
		double getVariance() { return im_variance; }
		
		// Set the input image for this filter
		virtual void setInput(const vector<T>& i) {
			// The input should be const. However, we cannot store it that way in our
			// base class. Therefor we cast away the const and store a pointer to the
			// original data. Upon using the input data in update(), we cast it back.
			_input = const_cast<vector<T>*>(&i);			
		}				

	protected:
		// Container for the output image is not applicable for StatisticsImageFilter
		// vector<T> _output;

		// Calculating values of min, max, sum, mean, median and variance
		void execute(const vector<T>& i) {
			
			// Number of voxels of the vector _input
			im_num_voxels = _input->size();

			// Minimum, Maximum and Sum (from same iterator)
			vector<T>::iterator it;
			for (it = _input->begin(); it != _input->end(); ++it) {
				// add to sum
				im_sum += *it;
				
				// check if smaller than current smallest value
				if (*it < im_min) im_min = *it;				
				
				// check if larger than current largest value
				if (*it > im_max) im_max = *it;				
			}

			// Mean
			im_mean = im_sum / im_num_voxels;
			
			// Median
			vector<T> sorted = *_input;
			std::sort(sorted.begin(), sorted.end());
			int num = int(im_num_voxels);
			
			// odd sized vector: middle element
			if (1 == (num % 2)) im_median = sorted[num / 2];			
			// even sized vector: average of middle elements
			else im_median = 0.5*(sorted[num / 2] + sorted[num / 2 - 1]);		

			// the variance
			double var_sum = 0.0;
			vector<T>::iterator it2;
			for (it2 = _input->begin(); it2 != _input->end(); ++it2) {
				var_sum += (*it2 - im_mean) * (*it2 - im_mean);
			}			
			im_variance = var_sum / im_num_voxels;
			
		};

	private:
		// Temporary storage of a pointer to the image data. Because we do some
		// const-magic, we keep it private.
		vector<T>* _input;
		
		T im_min = 999;
		T im_max = -1;
		T im_median;
		
		double im_num_voxels;
		double im_sum;
		double im_mean;
		double im_variance;
	};

}

#endif /* STATISTICSIMAGEFILTER_H */