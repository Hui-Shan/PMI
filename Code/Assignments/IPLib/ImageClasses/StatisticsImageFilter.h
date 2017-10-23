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
			cout << _input->size() << "\n";
		}

		T getMin() {
			/*T min_val = 999;
			for (int i = 0; i < _input->size(); ++i) {
				cout << (_input[i]);
				if (_input[i] < min_val) {
					min_val = _input[i];
				}
			}*/
			return 0;
		};
		T getMax() { return 0; };
		//T getMean() { return std::sum(_input); };
		/*T getSum() { 
			int num_els = _input->size();
			for (T val : _input) {

			}
		};*/
		T getMedian() { return 0; };

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