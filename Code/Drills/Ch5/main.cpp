#include "../../std_lib_facilities.h"

void scaffolding()
{


}

int main()
{
	try {

		cout << "Success!\n";
		cout << "Success!\n";
		cout << "Success" << "!\n";
		string success = "Success!"; cout << success << '\n';
		int res = 7; vector<int> v(10); v[5] = res; cout << "Success!\n";
		v[5] = 7; if (v[5] == 7) cout << "Success!\n";
		bool cond = true; 		if (cond) cout << "Success!\n"; else cout << "Fail!\n";
		bool c = false; if (!c) cout << "Success!\n"; else cout << "Fail!\n";
		string s = "ape"; c = "fool">s; if (c) cout << "Success!\n";
		if (s != "fool") cout << "Success!\n";
		if (s != "fool") cout << "Success!\n";
		if ((s + "fool").size()>0) cout << "Success!\n";
		vector<char> v2(5); for (int i = 0; i<v2.size(); ++i); cout << "Success!\n";
		for (int i = 0; i < v2.size(); ++i); cout << "Success!\n";
		s = "Success!\n"; for (int i = 0; i<s.size(); ++i) cout << s[i];
		if (true) cout << "Success!\n"; else cout << "Fail!\n";
		//int x = 2000; char d = x; if (int(d) == 2000) cout << "Success!\n";
		s = "Success!\n"; for (int i = 0; i<9; ++i) cout << s[i];
		for (int i = 0; i < v.size(); ++i); cout << "Success!\n";
		int i = 0; int j = 9; while (i<10) ++i; if (i<j) cout << "Success!\n";
		int xx = 2; double dd = 4.5; if (dd == (2 * xx + 0.5)) cout << "Success!\n";
		string sss = "Success!\n"; for (int i = 0; i < 9; ++i) cout << sss[i];
		i = 0; while (i<10) ++i; cout << "Success!\n";
		int x = 4; double d = 5.0 / (x-2); if (d = 2 * x + 0.5) cout << "Success!\n";
		cout << "Success!\n";

		keep_window_open();
		return 0;
	}
	catch (exception& e) {
		cerr << "error: " << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch (...) {
		cerr << "Oops: unknown exception!\n";
		keep_window_open();
		return 2;
	}
}