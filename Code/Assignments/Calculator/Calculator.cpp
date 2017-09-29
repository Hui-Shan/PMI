
/*
Calculator.cpp

Helpful comments removed.

We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include "std_lib_facilities.h"

struct Token {
	char kind;		// kind of token
	double value;	// only for certain kinds
	string name;	// st
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string str) :kind(ch), name(str) { }
};

class Token_stream {
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();
	void unget(Token t) { buffer = t; full = true; };
	void ignore(char);

private:
	bool full;		// returns true if the buffer is filled
	Token buffer;	// the Token in the buffer
};

const char let = 'L';
const char quit = 'Q';
const char print = '=';
const char number = '8';
const char name = 'a';

Token Token_stream::get()
{
	if (full) { 
		full = false; 
		return buffer; 
	}
	char ch;
	cin >> ch;
	switch (ch) {
	case quit : 
	case print : 
	case '(':
	case ')':
	case '{':
	case '}':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '!':
		return Token(ch);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	
		cin.unget();
		double val;
		cin >> val;
		return Token(number, val);
	}
	default:
		cout << "in default" << std::endl;		
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s = ch;
			cin.unget();
			if (s == "let") return Token(let);
			if (s == "quit") return Token(name);
			return Token(name, s);
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

struct Variable {
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;

double get_value(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ", s);
}

void set_value(string s, double d)
{
	for (int i = 0; i <= names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

bool is_declared(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

// Recursive function computing the factorial for a given an integer value n
double factorial(int n)
{
	int fact = (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
	return double(fact);
}

Token_stream ts;

double expression();
double postprimary();

double primary()
{
	Token t = ts.get();	
	switch (t.kind) {
	case '(':
	{	
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;		
	}
	case '{':
	{	
		double d = expression();
		t = ts.get();
		if (t.kind != '}') error("'}' expected");
		return d;
	}
	case '-':
		return -primary();
	case '+':
		return -primary();
	case number:
		return t.value;
	case name:
		cout << "name case " << name << "\n";
		t = ts.get();
		cout << get_value(t.name);
		return get_value(t.name);

		//set_value(stri, double d)
	default:
		error("primary expected");		
	}
}

double term()
{
	double left = postprimary();
	//double left = primary();
	Token t = ts.get();
	
	while (true) {		
		switch (t.kind) {
		case '*':
		{
			left *= postprimary();
			//left *= primary();
			t = ts.get();
			break;
			//return left;			
		}			
		case '/':		
		{
			double d = postprimary();
			//double d = postprimary();
			if (d == 0) error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}			
		default:
		{
			ts.unget(t);
			return left;
		}
			
		}
	}
}

double postprimary() {
	double left = primary();
	Token t = ts.get();

	while (true) {
		switch (t.kind) {
		case '!':
			left = factorial(int(left));
			t = ts.get();		
			break;
		default:			
			ts.unget(t);
       		return left;		
		}
	}
}

double expression()
{
	double left = term();
	Token t = ts.get();

	while (true) {		
		switch (t.kind) {
		case '+':
			left += term();
			t = ts.get();
			break;
			//return left;			
		case '-':
			left -= term();
			t = ts.get();
			break; 
			//return left;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double declaration()
{
	Token t = ts.get();
	if (t.kind != 'a') error("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	double d = expression();
	names.push_back(Variable(name, d));
	return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	while (cin)
	try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main() {
	try {
		calculate();
		keep_window_open();
		return 0;
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << endl;
		char c;
		while (cin >> c&& c != ';');
		return 1;
	}
	catch (...) {
		cerr << "exception\n";
		char c;
		while (cin >> c && c != ';');
		return 2;
	}
}

