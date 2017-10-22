#include "../std_lib_facilities.h"
//#include "ImageIOBase.h"
#include "ImageIOFactory.h"
#include <array>
//#include "MhdIO.h""
//#include "PipIO.h"
//using namespace std;

int main()
{
	//string pipfile = "../../brain.pip";
	string pipfile = "C:/Users/Hui Shan/Desktop/PMI/PMI-repo/Code/Assignments/data/brain.pip";
	string mhdfile = "C:/Users/Hui Shan/Desktop/PMI/PMI-repo/Code/Assignments/data/brain.mhd";

	const array<int, N_DIM>& dimensions = { 1,2,3,4,5 };
	
	try {
		PipIO pipimg(pipfile);
		MhdIO mhdimg(mhdfile);

		vector<short> pipvec = pipimg.read();
		vector<short> mhdvec = mhdimg.read();
		//pipimg.write(pipvec,);
	}
	catch (exception &e) {
		cout << e.what();
	}

	string filename;
	cout << "Please enter a PIP or MHD filename: " << endl;
	cin >> filename;

	ImageIOBase* io = ImageIOFactory::getIO(filename);
	auto image = io->read();
	delete io; io = nullptr;
	

	return 0;
}



