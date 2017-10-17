#include "../std_lib_facilities.h"

#define N_DIM 5

unsigned char getPIPdatatype(ifstream& filestream);
string get_relative_filepath(string fullinputfile);
string get_filename(string fullinputfile);

vector<short> readPIP(const string& filename);
//void writePIP(const string & filename, 
//			  const array<int, N_DIM>& dimensions, 
//	          const vector<short>& image);
void writePIP(const string & filename,
			  const vector<int> &dimensions,
			  const vector<short>& image);

vector<short> readMHD(const string& filename); 
/*void writeMHD(const string & filename, 
			  const array<int, N_DIM>& dimensions, 
			  const vector<short>& image);
*/
void writeMHD(const string & filename,
		      const vector<int>& dimensions,
			  const vector<short>& image);




