#pragma warning(default:4996)

#include "ImageIOFactory.h"
#include "ThresholdImageFilter.h"
#include "StatisticsImageFilter.h"
#include "MaskImageFilter.h"
#include "ConvolutionImageFilter.h"

using namespace hmc;

void test_statistics_filter(string imfile) {
	unique_ptr<ImageIOBase> io = ImageIOFactory::getIO(imfile);
	auto image = io->read();
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
	unique_ptr<ImageIOBase> io = ImageIOFactory::getIO(imfile_in);
	auto image_in = io->read();
	
	ThresholdImageFilter f;
	f.setInput(image_in);
	f.setThreshold(threshold);
	f.update();
	auto image_out = f.getOutput();
	
	unique_ptr<ImageIOBase> io2 = ImageIOFactory::getIO(imfile_out);
	io2->write(image_out); // image, dimensions			
	
	cout << "Saved thresholded image to " << imfile_out << "\n";
}

void test_mask_filter(string imfile_in, string maskfile_in, string imfile_out) {	
	cout << "\nMasking away half the image of " << imfile_in << "\n";
	unique_ptr<ImageIOBase> io2 = ImageIOFactory::getIO(imfile_in);
	auto image2 = io2->read();

	unique_ptr<ImageIOBase> iom = ImageIOFactory::getIO(maskfile_in);
	auto imagem = iom->read();

	// 	

	MaskImageFilter mif;
	mif.setInput(image2);
	mif.setInputMask(imagem);
	mif.update();
	auto masked_image = mif.getOutput();

	io2 = ImageIOFactory::getIO(imfile_out);
	io2->write(masked_image);	
	
	cout << "Saved masked image to " << imfile_out << "\n";
}

void test_convolution_filter(string imfile_in, string imfile_out, int rad_in = 3) {
	cout << "\nConvolution the image " << imfile_in << " with gaussian kernel of size " << rad_in << "\n";
	unique_ptr<ImageIOBase> io2 = ImageIOFactory::getIO(imfile_in);
	auto image2 = io2->read();

	ConvolutionImageFilter cif(5);
	cif.setInput(image2);
	cif.update();

	auto conv_im = cif.getOutput();

	unique_ptr<ImageIOBase> io3 = ImageIOFactory::getIO(imfile_out);
	io3->write(conv_im);

	cout << "Saved convolved image to " << imfile_out << "\n";

}

int main()
{
	string file = "..//..//data//brain";
	string ext;
	string mhd = ".mhd";
	string pip = ".pip";
	ext = mhd;
	
		
	string filename;
	string outfilename; 

	// Reading and writing image files
	try {
		
		filename = file + ext;		

		
		unique_ptr<ImageIOBase> io = ImageIOFactory::getIO(filename);
		Image image = io->read();
		cout << "Read in " << filename << "\n";
				
		// Test statistics filter				
		test_statistics_filter(filename);
		
		// Test threshold filter	
		outfilename = file + "_out_thresholded" + ext;		
		test_threshold_filter(filename, 60, outfilename);
		
		// Test mask image filter
		string masked_file = file + "_masked" + ext;
		string maskfile = "..//..//data//halfmask.pip";
		
		test_mask_filter(filename, maskfile, masked_file);
		
		// Test convolution filter
		for (int conv_rad = 0; conv_rad < 2; ++conv_rad) {
			outfilename = file + "_out_convolved_" + to_string(conv_rad) + ext;
			test_convolution_filter(filename, outfilename, conv_rad);
		}
		
		

	}
	catch (exception &e) {
		cout << e.what() << "\n";
	}	

	keep_window_open();

	return 0;
}


