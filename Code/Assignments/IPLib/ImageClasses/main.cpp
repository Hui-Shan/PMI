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
	cout << "\nConvolution the image " << imfile_in << " with gaussian kernel with radius " << rad_in << "\n";
	unique_ptr<ImageIOBase> io2 = ImageIOFactory::getIO(imfile_in);
	auto image2 = io2->read();

	ConvolutionImageFilter cif(rad_in);
	cif.setInput(image2);
	cif.update();

	auto conv_im = cif.getOutput();

	unique_ptr<ImageIOBase> io3 = ImageIOFactory::getIO(imfile_out);
	io3->write(conv_im);

	cout << "Saved convolved image to " << imfile_out << "\n";

}

double gauss3D(int xi, int x0, int yi, int y0, int zi, int z0, double sigma = 1.0) {
	double coord_sum = T(pow(xi - x0, 2) + pow(yi - y0, 2) + pow(zi - z0, 2));
	double g = 1 / (2 * M_PI * sigma) * exp(-coord_sum / pow(sigma, 2));
	return g;
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

		// test constructors

		// default
/*		{
			Image i1 = Image();
		
			// dimension 
			Image::dimension d2 = { 4,4,4,1,1 };
			Image i2 = Image(d2);
			
			// copy
			Image i3 = Image(i2);

			cout << "i2.begin() " <<  i2.begin() << " i3.begin() " << i3.begin() << "\n";

			// move 
			Image& i4 = Image(i2);
			cout << "i4.begin() " << i4.begin() << " i2.begin() " << i2.begin() << "\n";

			Image i5 = i2;

			cout << "i2.begin() " << i2.begin() << " i5.begin() " << i5.begin() << "\n";

		}
*/		
		filename = file + ext;

		unique_ptr<ImageIOBase> io = ImageIOFactory::getIO(filename);
		Image image = io->read();
		cout << "Read in " << filename << "\n";
		
		T val00000 = image(0, 0, 0, 0, 0);
		cout << val00000 << "\n";
		image(10, 10, 10, 0, 0) = T(200);// *image(-1, 1000, 0, 0, 0);
		image(0, 0, 0, 0, 0);

		string pppfile = "..//..//data//test_write" + ext;
		unique_ptr<ImageIOBase> io_ppp = ImageIOFactory::getIO(pppfile);
		io_ppp->write(image);
		
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
		for (int conv_rad = 1; conv_rad < 2; ++conv_rad) {
			// 
			cout << "Start convolution with radius of " << conv_rad << " ";
			outfilename = file + "_out_convolved_" + to_string(conv_rad) + ext;
			test_convolution_filter(filename, outfilename, conv_rad);
			cout << "Done convolution, written to " << outfilename << "\n";
		}
		

		//cout << convkernel.size(); 
		//Image::const_iterator cit; 
		//for (cit = convkernel.begin(); cit != convkernel.end(); ++cit) {
//			cout << *cit << "\n";
		//}

		
		/*double factor = 1 / pow(sqrt(2 * M_PI) * rad, 3);
		//cout << rad << " " << factor << "\n";
		double sum = 0.0;
		for (int z = -rad; z <= rad; ++z) {
			for (int y = -rad; y <= rad; ++y) {
				for (int x = -rad; x <= rad; ++x) {
					//cout << x << "," << y << "," << z << "\n";					
					coord_sum = double(pow(x, 2) + pow(y, 2) + pow(z, 2)) / (double(pow(rad, 2) * 2));
					cout << factor * exp(-coord_sum) << "\n";
					sum += factor * exp(-coord_sum);
				}
			}		
			//cout << coord_sum << "--> exp " << exp(-coord_sum) << "\n";
		}
		cout << " " << sum << "\n";

		*/
		
		

	}
	catch (exception &e) {
		cout << e.what() << "\n";
	}	

	keep_window_open();

	return 0;
}


