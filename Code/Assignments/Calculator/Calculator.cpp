
/*
	Calculator.cpp

	Revision history:
		Initial version from buggy...

	This program implements a basic expression calculator. 
	Input from cin; output to cout.
	The grammar for input is:

	Statement:
		Expression
		Print
		Quit

	Print:
		variable print

	Quit:
		variable quit

	Expression:
		Term 
		Expression + Term
		Expression - Term
	Term:
		Postprimary
	Postprimary:
		Primary factorial
		Primary
	Primary:
		Number
		( Expression )
		- Primary
		+ Primary
	Number:
		floating-point literal

	Input comes from cin through the Token_stream called ts.
*/

#define _USE_MATH_DEFINES

#include "std_lib_facilities.h"
#include <cmath>

struct Token {
	char kind;		// kind of token
	double value;	// value of number tokens
	string name;	// name of token
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string str) :kind(ch), name(str) { }
};

class Token_stream {
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();			         					// gets Token
	void unget(Token t) { buffer = t; full = true; };	// unget Token to stream
	void ignore(char c);								// ignore non c Tokens

private:
	bool full;		// returns true if the buffer is filled
	Token buffer;	// the Token in the buffer
};

const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const string declkey = "let";
const string pi_string = "pi";
const string e_string = "e";

Token Token_stream::get()
{
	if (full) { 
		full = false; 
		return buffer; 
	}
	char ch;
	cin >> ch;
/*	if (isspace(ch)) {
		cout << "lala\n";
		if (ch == '\n') return Token(print);
		cin.unget();
	}*/
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
	case '=':	
		return Token(ch);
	case '.':
	case '0': case '1': case '2': case '3': case '4': 
	case '5': case '6': case '7': case '8': case '9':
	{	
		cin.unget();
		double val;
		cin >> val;
		return Token(number, val);
	}
	default:
		//std::cout << "in default" << std::endl;		
		if (isalpha(ch) || ch=='_') {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch=='_')) s += ch;
			cin.unget();
			if (s == declkey) return Token(let);		
			if (ch == quit) return Token(quit);
			
			return Token(name, s);			
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
	// c represents the kind of Token
{
	// look if the buffer is full, if so return
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	// otherwise keep reading until c is read in
	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

struct Variable {
	string name;
	double value;
	bool constant;
	Variable(string n, double v) :name(n), value(v), constant(false) { }
	Variable(string n, double v, bool c) :name(n), value(v), constant(c) { }
};

class Symbol_table {
	
public: 
	double get(string var_name);
	void set(string s, double d, bool b=false);
	bool is_declared(string s);
	void declare(string s, double d, bool b=false);
	
private:
	vector<Variable> var_table;

};

double Symbol_table::get(string s)
// returns the value of the Variable with name s
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) return var_table[i].value;
	error("get: undefined name ", s);
}

void Symbol_table::set(string s, double d, bool b)
	// sets the value of the Variable named s to d
{	
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) {
			if (var_table[i].constant == false) {
				var_table[i].value = d;
			}
			else {
				cout << "Cannot change value of constant variable.\n";				
			}
			return;
		}
	error("set: undefined name ", s);
}

bool Symbol_table::is_declared(string s)
	// checks if a Variable with name s has been declared before, 
	// returns true if so, otherwise returns false
{
	for (int i = 0; i<var_table.size(); ++i)
		if (var_table[i].name == s) return true;
	return false;
}

void Symbol_table::declare(string s, double d, bool b)
{
	if (is_declared(s)) {
		return;
	}
	else {
		var_table.push_back(Variable(s, d, b));
	}
	
}

double factorial(int n)
	// Recursive function computing the factorial for a given an integer value n
{
	int fact = (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
	return double(fact);
}

Token_stream ts;
Symbol_table symtab; 

double expression();
double postprimary();

double primary()
{
	Token t = ts.get();	
	Token next = Token('+');
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
		next = ts.get();
		if (next.kind == '=') {
			double d = expression();
			symtab.set(t.name, d);
			return d;
		}
		else {
			ts.unget(next);
			return symtab.get(t.name);
		}
			
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
	// function that handles the declaration of variables
	// handle: name = expression
	// declare a variable called "name" with the inital value "expression"
{	
	Token t = ts.get();	
	
	if (t.kind != name && t.kind != '_') error("name expected in declaration");
	string var_name = t.name;
	
	if (symtab.is_declared(var_name)) error(var_name, " declared twice");
	
	Token t2 = ts.get();	
	if (t2.kind != '=') error("= missing in declaration of ", var_name);
	
	double d = expression();		
	if (symtab.is_declared(var_name))
		symtab.set(var_name, d);
	else
		symtab.declare(var_name, d);
		symtab.set(var_name, d);
	
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
		cout << statement() << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main() {

	// add constant values
	symtab.declare(pi_string, M_PI, true);
	symtab.declare(e_string, M_E, true);

	try {
		calculate();
		keep_window_open("~~");
		return 0;
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << endl;
		char c;
		while (cin >> c&& c != quit);
		return 1;
	}
	catch (...) {
		cerr << "exception\n";
		char c;
		while (cin >> c && c != quit);
		return 2;
	}
}

