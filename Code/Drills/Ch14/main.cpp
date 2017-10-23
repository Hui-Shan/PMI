#include "../../std_lib_facilities.h"

class B1 {
public:
	virtual void vf() {
		cout << "B1::vf()" << "\n";
	};

	void f() {
		cout << "B1::f()" << "\n";
	};

	virtual void pvf() = 0;
};

class D1 : public B1 {
public:
	void vf() override {
		cout << "D1::vf()" << "\n";
	};

	void f() {
		cout << "D1::f()" << "\n";
	}

	virtual void pvf() {
		cout << "D1::pvf()" << "\n";
	};

};

class D2 : public D1 {
public:
	void pvf() override {
		cout << "D2::pvf()" << "\n";
	}
};

class B2 {
public:
	virtual void pvf() = 0;
};

class D21 : public B2 {
public:
	D21(string data_in) { data = data_in; };
	string data;
	void pvf() {
		cout << data << "\n";
	}
};

class D22 : public B2 {
public:
	D22(int int_in) { data = int_in; };
	int data;
	void pvf() {
		cout << data << "\n";
	}
};

void f(B2& b2obj) {
	b2obj.pvf();
}

int main() {
	D1 obj = D1();
	cout << "D1 obj = D1();\n";
	cout << "obj.f()\n";
	obj.f();
	cout << "obj.vf()\n";
	obj.vf();
	cout << "obj.pvf()\n";
	obj.pvf();


	B1& ref = obj;
	cout << "\nB1& ref = obj;\n";
	cout << "ref.f()\n";
	ref.f();
	cout << "ref.vf()\n";
	ref.vf();
	cout << "ref.pvf()\n";
	ref.pvf();

	D21 obj1 = D21("hello");
	cout << "\nD21 obj1 = D21(\"hello\");" << "\n" << "obj1.pvf();" << "\n";
	obj1.pvf();

	cout << "obj1.data " << obj1.data << "\n";
	f(obj1);

	D22 obj2 = D22(5);
	cout << "\nD22 obj2 = D22(5);" << "\n" << "obj2.pvf();" << "\n";
	obj2.pvf();

	cout << "obj2.data " << obj2.data << "\n";
	f(obj2);

	keep_window_open();
	return 0;
}