#include "ImageIOFactory.h"
#include "ThresholdImageFilter.h"

int main()
{
	string pipfile = "..//..//data//brain.pip";
	string mhdfile = "..//..//data//brain.mhd";
		
	string filename;
	string outfilename; 

	// Reading and writing image files
	try {
		filename = pipfile;
		ImageIOBase* io = ImageIOFactory::getIO(filename);
		auto image = io->read();
		cout << "Read in " << filename << "\n";

		ThresholdImageFilter f;
		f.setInput(image);
		f.setThreshold(60);
		f.update();
		image = f.getOutput();

		outfilename = "..//..//data//brain_out_thresholded.pip";
		io = ImageIOFactory::getIO(outfilename);
		io->write(image, { 109, 91, 80, 1, 1 }); // image, dimensions
		delete io; io = nullptr;
		cout << "Written image to " << outfilename << "\n";
		
		filename = mhdfile;
		ImageIOBase* io2 = ImageIOFactory::getIO(filename);
		auto image2 = io2->read();
		cout << "Read in " << filename << "\n";
		
		f.setInput(image2);
		f.setThreshold(60);
		f.update();
		image2 = f.getOutput();

		outfilename = "..//..//data//brain_out_thresholded.mhd";
		io2 = ImageIOFactory::getIO(outfilename);
		io2->write(image2, { 109, 91, 80, 1, 1 }); // image, dimensions
		delete io2; io2 = nullptr;
		cout << "Written image to " << outfilename << "\n";
	}
	catch (exception &e) {
		cout << e.what() << "\n";
	}	

	keep_window_open();

	return 0;
}


