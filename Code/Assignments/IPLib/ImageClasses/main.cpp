#pragma warning(default:4996)

#include "ImageIOFactory.h"
/*#include "ThresholdImageFilter.h"
#include "StatisticsImageFilter.h"
#include "MaskImageFilter.h"*/

using namespace hmc;

Image get_image_vec(string imfile) {
	unique_ptr<ImageIOBase> io = ImageIOFactory::getIO(imfile);
	auto image = io->read();	
	//delete io; io = nullptr;
	return image;
}

/*void test_statistics_filter(string imfile) {	
	auto image = get_image_vec(imfile);
	cout << "\nComputing statistics for " << imfile << " \n"; 
	
	StatisticsImageFilter sf;
	sf.setInput(image);
	sf.update();

	cout << "Number of voxels " << sf.getNumVoxels() << "\n";
	cout << "Min " << sf.getMin() << "\n";
	cout << "Max " << sf.getMax() << "\n";
	cout << "Median " << sf.getMedian() << "\n";
	cout << "Sum " << sf.getSum() << "\n";
	cout << "Mean " << sf.getMean() << "\n";
	cout << "Variance " << sf.getVariance() << "\n";
}

void test_threshold_filter(string imfile_in, T threshold, string imfile_out) {
	cout << "\nThresholding " << imfile_in << " at " << threshold << ":\n";
	auto image_in = get_image_vec(imfile_in);

	ThresholdImageFilter f;
	f.setInput(image_in);
	f.setThreshold(threshold);
	f.update();
	auto image_out = f.getOutput();
	
	unique_ptr<ImageIOBase> io = ImageIOFactory::getIO(imfile_out);
	io->write(image_out, { 109, 91, 80, 1, 1 }); // image, dimensions			
	
	cout << "Saved thresholded image to " << imfile_out << "\n";
}

void test_mask_filter(string imfile_in, string imfile_out) {	
	cout << "\nMasking away half the image of " << imfile_in << "\n";
	unique_ptr<ImageIOBase> io2 = ImageIOFactory::getIO(imfile_in);
	auto image2 = io2->read();

	// 	
	vector<T> mask;
	mask.resize(image2.size());
	for (int i = 0; i < mask.size(); ++i){ 
		if (i < mask.size() / 2) mask[i] = 1;
		else mask[i] = 0;
	}

	MaskImageFilter mif;
	mif.setInput(image2);
	mif.setInputMask(mask);
	mif.update();
	auto masked_image = mif.getOutput();

	io2 = ImageIOFactory::getIO(imfile_out);
	io2->write(masked_image, { 109, 91, 80, 1, 1 });
	//delete io2; io2 = nullptr;
	
	cout << "Saved masked image to " << imfile_out << "\n";
}*/

int main()
{
	string pipfile = "..//..//data//brain.pip";
	string mhdfile = "..//..//data//brain.mhd";
		
	string filename;
	string outfilename; 

	// Reading and writing image files
	try {
		filename = pipfile;
		unique_ptr<ImageIOBase> io = ImageIOFactory::getIO(filename);
		auto image = io->read();
		cout << "Read in " << filename << "\n";

		/*
		// Test statistics filter				
		test_statistics_filter(pipfile);

		// Test threshold filter	
		outfilename = "..//..//data//brain_out_thresholded.pip";
		test_threshold_filter(filename, 60, outfilename);
		
		// Test mask image filter
		filename = mhdfile;
		string masked_file = "..//..//data//brain_masked.pip";
		test_mask_filter(filename, masked_file);

		// Test convolution filter */

	}
	catch (exception &e) {
		cout << e.what() << "\n";
	}	

	keep_window_open();

	return 0;
}


