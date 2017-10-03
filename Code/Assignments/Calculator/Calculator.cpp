
/*
	Calculator.cpp

	Revision history:
		Initial version from calculator08buggy.cpp
		Revised by HMC October 2017			

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
const char helpchar = 'H';
const char quitchar = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char powchar = 'p';
const char sqrtchar = 'v';
const char sinchar = 's';

const string ans_string = "ans";
const string powstr = "pow";
const string sqrtstr = "sqrt";
const string sinstr = "sin";
const string declkey = "let";
const string pi_string = "pi";
const string e_string = "e";
const string quit = "quit";
const string help = "help";
//const string newline = "\n";
const string prompt = "> ";
//const string result = "= ";

const string help_message =
	"This executable is a simple calculator implementation.\n\n"
	"Supported operations are addition (+), subtraction (-), multiplication (*)\n"
	"division (/), modulo (%) and factorial (!). For % and !, doubles will be \n"
	"converted to integers).\n"
	"Pressing [Enter], and or writing the '\n' newline or ';' characters will \n"
	"yield evaluation of the expressions.\n"
	"\n"
	"Constant variables that are included in the variable list are pi and e.\n"
	"Letters that cannot be used to store variables are 'H', 'L' and 'Q'.\n"
	"Typing \"help\" or \"H\" displays this help message, typing \"quit\" or Q will \n"
	"cause the program to exit.\n";

Token Token_stream::get()
{
	if (full) { 
		full = false; 
		return buffer; 
	}
	
	char ch;
	ch = cin.get();
	
	while (isspace(ch)) {
		if (ch == '\n')
			return Token(print);
		ch = cin.get();
	}
		
	switch (ch) {
	case quitchar : 
	case helpchar : 
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
	case ',':
		return Token(ch);	
	case '.':
	case '0': case '1': case '2': case '3': case '4': 
	case '5': case '6': case '7': case '8': case '9':		
		// read in the entire number for these cases
		cin.unget();
		double val;
		cin >> val;		 
		return Token(number, val);	
	default:
		if (isalpha(ch) || ch=='_') {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch=='_')) s += ch;
			cin.unget();
			if (s == declkey) return Token(let);		
			if (s == quit) return Token(quitchar);
			if (s == help) return Token(helpchar);
			if (s == powstr) return Token(powchar);
			if (s == sqrtstr) return Token(sqrtchar);
			if (s == sinstr) return Token(sinchar);
			
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
	for (int i = 0; i<var_table.size(); ++i) {
		if (var_table[i].name == s) {
			if (var_table[i].constant == false) {
				var_table[i].value = d;
			}
			else {
				cout << "Cannot change value of constant variable.\n";
			}
			return;
		}
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
	// function checks if string s has been declared as name, if not, it adds 
	// a new Variable with that name to the var_table member of the 
	// Symbol_table object
{
	if (is_declared(s)) {
		return;
	}
	else {
		var_table.push_back(Variable(s, d, b));
	}
	
}

double factorial(double n)
	// Recursive function computing the factorial for a given an double value n
	// factorial is defined with double, so that you run into over/underflow 
	// less quickly
{
	double fact = (n == 1.0 || n == 0.0) ? 1 : factorial(n - 1.0) * n;
	return double(fact);
}

Token_stream ts;
Symbol_table symtab; 

double expression();
double postprimary();
double statement();
double sine();
double squareroot();
double power();

double primary()
{
	Token t = ts.get();	
	Token next = Token('+'); // dummy Token
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
		return +primary();
	case number:		
		return t.value;
	case powchar:
		return power();
	case sinchar:
		return sine();
	case sqrtchar:
		return squareroot();
	case name:
		// check for assignment operator '='; 
		// if check is true, set variable name to value d
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
	Token t = ts.get();
	
	while (true) {		
		switch (t.kind) {
		case '*':
			{
				left *= postprimary();			
				t = ts.get();
				break;			
			}			
		case '/':		
			{
				double d = postprimary();			
				if (d == 0) error("divide by zero");
				left /= d;
				t = ts.get();
				break;
			}	
		case '%':
			{
				int i1 = int(left);
				int i2 = int(postprimary());
				if (i2 == 0) error("%: divide by zero");
				left = i1%i2;
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
		case '-':
			left -= term();
			t = ts.get();
			break; 			
		default:
			ts.unget(t);
			return left;
		}
	}
}

double sine()
	// Function computes the sine of a certain value, input in radians
{
	double left = primary();	
	return sin(left);
}

double squareroot()
{
	double left = primary();
	if (left < 0) error("sqrt: value to take square root of is negative.");
	return sqrt(left);
}

double power()
	// Function computes the value of the expression of the type x^i
{
	
	Token t = ts.get();
	if (t.kind != '(') error("no opening parenthesis found in pow(x,i) call.");
		
	double left = statement();
	
	Token t2 = ts.get();
	if (t2.kind != ',') error("no comma found in pow(x,i) call.");
			
	int exppower = int(expression());
	
	Token t3 = ts.get();
	if (t3.kind != ')') error("no closing parenthesis found in pow(x,i) call.");

	return pow(left, exppower);


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



void calculate()
{
	while (cin)
	try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();		
		if (t.kind == helpchar){
			cout << help_message;
		}
		else {
			if (t.kind == quitchar)	return;
			ts.unget(t);
			double stat = statement();
			symtab.set(ans_string, stat);
			cout << stat << endl;
		}		
		
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
};

int main() {

	// add constant values
	symtab.declare(ans_string, 0.0);
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
		while (cin >> c&& c != quitchar);
		return 1;
	}
	catch (...) {
		cerr << "exception\n";
		char c;
		while (cin >> c && c != quitchar);
		return 2;
	}
}


