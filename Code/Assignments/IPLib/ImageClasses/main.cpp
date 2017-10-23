//#include "../std_lib_facilities.h"
#include "ImageIOFactory.h"
//#include "MhdIO.h""
//#include "PipIO.h"

#include <experimental/filesystem>

int main()
{
	string pipfile = "..//..//data//brain.pip";
	string mhdfile = "..//..//data//brain.mhd";
		
	string filename; 

	try {
		filename = pipfile;
		ImageIOBase* io = ImageIOFactory::getIO(filename);
		auto image = io->read();
		delete io; io = nullptr;

		filename = mhdfile;
		ImageIOBase* io2 = ImageIOFactory::getIO(filename);
		auto image2 = io2->read();
		delete io2; io2 = nullptr;
	}
	catch (exception &e) {
		cout << e.what() << "\n";
	}	
	

	return 0;
}


