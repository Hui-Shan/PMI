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

		// Set the input image for this filter
		virtual void setInput(const vector<T>& i) {
			// The input should be const. However, we cannot store it that way in our
			// base class. Therefor we cast away the const and store a pointer to the
			// original data. Upon using the input data in update(), we cast it back.
			_input = const_cast<vector<T>*>(&i);			
		}
		
		// Returns the number of voxels of the vector _input
		double getNumVoxels() {
			return double(_input->size());
		}

		// Returns the minimum value of the vector _input
		T getMin() {
			T min_val = +999;
			vector<T>::iterator it;
			for (it = _input->begin(); it != _input->end(); ++it) {
				if (*it < min_val) {
					min_val = *it;
				}
			}
			return min_val;
		}

		// Returns the maximum value of the vector _input
		T getMax() {
			T max_val = -1;
			vector<T>::iterator it;
			for (it = _input->begin(); it != _input->end(); ++it) {
				if (*it > max_val) {
					max_val = *it;
				}
			}
			return max_val;
		}
		
		// Returns the mean of the intensity values of vector _input
		double getMean() { 
			double sum = getSum();			
			double num = getNumVoxels();			
			return double(sum/num);
		};

		// Returns the sum of the intensity values of vector _input
		double getSum() {
			double sum = 0;
			vector<T>::iterator it;
			for (it = _input->begin(); it != _input->end(); ++it) {
				sum += *it;
			}
			return sum;
		}

		// Returns the median of the vector _input (average of middle elements
		// in case of even-valued vector size)
		T getMedian() { 
			T median;
			vector<T> sorted = *_input;
			std::sort(sorted.begin(), sorted.end());
			int num =  int(getNumVoxels());
			if (1 == (num % 2)) {				
				median = sorted[num / 2];
			}				
			else {			
				median = 0.5*(sorted[num / 2] + sorted[num / 2 - 1]);				
			}			
			return median;
		}

	protected:
		// Container for the output image
		// vector<T> _output;

		// This method should be overloaded in your derived class and implement the
		// image filter that fills _output
		void execute(const vector<T>& i) {

		};

	private:
		// Temporary storage of a pointer to the image data. Because we do some
		// const-magic, we keep it private.
		vector<T>* _input;
	};

}

#endif /* STATISTICSIMAGEFILTER_H */