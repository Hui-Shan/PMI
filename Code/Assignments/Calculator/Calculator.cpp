/*
	Calculator.cpp (adapted from Stroustrup's calculator08buggy.cpp)
	Author Hui Shan Chan

	This program implements a basic expression calculator executable.
	Input from cin; output to cout.

	Revision history:
	Initial version from calculator08buggy.cpp
		Functions: +, -, *, /

	Revised by HMC October 2017			
		Added math functions: 
			!	: factorial
			%	: modulo
			^	: power
			sin : sine function
		Other functions:
			declare : declare new variables (can also be constant)
			set		: set new value for variable
			help	: display help message
			showvar : show the variables which have been stored
			quit	: exit the calculator
			
	The main function calls the calculate function while input is given, and 
	the calculate function deals with declarations statements or expression
	statements, where the grammar of an expression is given by the grammar as
	described below.

	Statement:
		Declaration
		Expression		

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
		{ Expression }
		- Primary
		+ Primary
	Number:
		floating-point literal
	
*/

#define _USE_MATH_DEFINES

#include "std_lib_facilities.h"
#include <cmath>

struct Token {
	char kind;		// kind of token
	double value;	// value (for number tokens)
	string name;	// name (for name tokens)
	
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
	bool full;		// true if the buffer is filled
	Token buffer;	// the Token in the buffer
};

const char let = 'L';
const char helpchar = 'H';
const char name = 'a';
const char number = '8';
const char quitchar = 'Q';
const char pchar = 'p';
const char print = ';';
const char showvarchar = '$';
const char schar = 's';
const char vchar = 'v';

const string ans = "ans";
const string e_string = "e";
const string pi_string = "pi";
const string sin_string = "sin";
const string sqrt_string = "sqrt";

const string const_string = "const";
const string declkey = "let";
const string help = "help";
const string prompt = "> ";
const string quit = "quit";
const string showvar = "showvar";
const string starting_message = "Please enter an expression, or \'help\' if you don't know what to do:\n";

const string help_message =
	"This executable is a simple calculator implementation, based on the\n"
	"calculator08buggy.cpp file from Chapter 7 of \'Programming Principles and\n" 
	"Practice using c++\' by Bjarne Stroustrup.\n"
	"\n"
	"Implemented operations of this calculator are : + , - , *, /, ! (factorial),"
	" % (modulo), ^ (taking the power), sin (taking the sine) and sqrt (taking "
	"the square root).\n" 
	"\n"
	"For % and !, double values will be converted to integers."
	"\n"
	"Pressing [Enter] yields evaluation of the expression on the current line.\n"
	"Multiple expression can be separated by ';' if needed. The result of the last\n"
	"successful evaluation is stored in a variable called \"ans\".\n"
	"\n"
	"Users can also define variables themselves, using the command "
	"\"let <var_name> = <var_value\" for modifiable variables, and "
	"\"let const <var_name> = <var_value>\" for constant variables.\n"
	"\n"
	"Display stored variables with \"" + showvar + "\" followed by [Enter].\n"
	"Display help with \""+ help + "\" followed by[Enter].\n"
	"To exit, type \"" + quit + "\" followed by [Enter].\n"
	"\n"
	"If an exception occurs or no new prompt is displayed, type a random "
	"expression followed by ';' and [Enter] to continue entering input.\n";


Token Token_stream::get()
	// handles which functions to call for characters from the Token_stream
{
	
	// if buffer is full, first return stored Token
	if (full) { 
		full = false; 
		return buffer; 
	}	
	
	// otherwise go on and read characters in
	char ch;
	ch = cin.get();	
	
	// skipping whitespaces that are not '\n'
	while (isspace(ch)) {
		if (ch == '\n')			
			return Token(print);
		ch = cin.get();
	}
	
	// handles wat should be done
	switch (ch) {	 
		// for Tokens representing themselves
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
	case '^':	
		return Token(ch);				
		// for value Tokens
	case '.':
	case '0': case '1': case '2': case '3': case '4': 
	case '5': case '6': case '7': case '8': case '9':		
	{
		// read in the entire number for these cases
		cin.unget();
		double val;
		cin >> val;
		return Token(number, val);
	}	
		// in the default case, for all string commands
	default:
		if (isalpha(ch) || ch=='_') {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch=='_')) s += ch;
			cin.unget();
			if (s == declkey) return Token(let);		
			else if (s == quit) return Token(quitchar);
			else if (s == help) return Token(helpchar);			
			else if (s == showvar) return Token(showvarchar);			
			else if (s == sqrt_string) return Token(vchar);
			else if (s == sin_string) return Token(schar);
			else return Token(name, s);			
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
	// function to ignore all Tokens until char c is found
{
	// look if the buffer is full, if so return
	if (full && c == buffer.kind) {
		full = false;
		return;
	}	

	// otherwise keep reading until c is read in
	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

struct Variable {
	string name;	// variable name
	double value;	// variable value
	bool constant;	// true if the variable's value is constant and cannot 
					// be edited, false otherwise
	
	Variable(string n, double v) :name(n), value(v), constant(false) { }
	Variable(string n, double v, bool c) :name(n), value(v), constant(c) { }
};

class Symbol_table {
	// class to hold table of variables, with functions to add, edit and return 
	// the variable values
public:
	double get(string var_name);
	void set(string s, double d, bool b=false);
	bool is_declared(string s);
	void declare(string s, double d, bool b=false);
	void print_vars();
	
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

void Symbol_table::print_vars()
	// function prints out the constant and modifiable variables stored
{
	cout << "Constant variables: \n";
	for (Variable v : var_table) {
		if (v.constant) {
			cout << v.name << " = " << v.value << "\n";
		}
	}

	cout << "\nModifiable variables: \n";
	for (Variable v : var_table) {
		if (!v.constant) {
			cout << v.name << " = " << v.value << "\n";
		}
	}

}

double factorial(double n)
	// Recursive function computing the factorial for a given an double value n. 
	// The factorial computation is defined with double, so that you run into 
	// over less quickly
{
	double fact = (n == 1.0 || n == 0.0) ? 1 : factorial(n - 1.0) * n;
	return double(fact);
}

Token_stream ts;
Symbol_table symtab; 

double expression();
double postprimary();
double statement();

double primary()
{
	// Function for evaluating primary's in the grammar
	// Includes:
	//		expressions between brackets, () or {}, 
	//		+ or - times a primary
	//		the calling or setting of a named variable
	Token t = ts.get();		
	switch (t.kind) {		
	case '(':
	{	
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected.");
		return d;		
	}
	case '{':
	{	
		double d = expression();
		t = ts.get();
		if (t.kind != '}') error("'}' expected.");
		return d;
	}
	case '-':
		return -primary();
	case '+':
		return +primary();
	case number:		
		return t.value;
	case schar:
		return sin(primary());
	case vchar:
	{	
		double arg = primary();				
		if (arg < 0) {
			error("sqrt: cannot take the square root of a negative number.");			
		}		
		return sqrt(arg);
	}
	case name:
	{
		// check for assignment operator '='; 
		// if check is true, set variable name to value d
		Token next = ts.get();
		if(next.kind == '=') {
			double d = expression();
			symtab.set(t.name, d);
			return d;
		}
		else {
			ts.unget(next);
			return symtab.get(t.name);
		}		
	}
	default:
		error("primary expected");
	}
}

double term()
{
	// function for evaluating terms in the grammar
	// operators include *, / , % and ^
	double left = postprimary();		
	Token t = ts.get();
	
	while (true) {		
		switch (t.kind) {
		case '*':
			{
				left *= postprimary();			
				left *= primary();
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
				int i1 = narrow_cast<int>(left);
				int i2 = narrow_cast<int>(postprimary());
				if (i2 == 0) error("%: modulo of zero");				
				left = i1%i2;
				t = ts.get();
				break;
			}
		case '^':
		{
			double p = postprimary();			
			left = pow(left, p);
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
	// function for evaluating postprimary's in the grammar:
	// made explicitly for the factorial case when evaluating terms
	double left = primary();
	Token t = ts.get();

	while (true) {
		switch (t.kind) {
		case '!':
			// give input argument as integer type
			left = factorial(narrow_cast<int>(left));
			t = ts.get();		
			break;
		default:			
			ts.unget(t);
       		return left;		
		}
	}
}

double expression()
	// function for evaluating expressions in the grammar
	// operations include + and - 
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

double declaration()
// Function that handles the declaration of (possibly constant) variables named 
// "name" with their inital values "expression()". The name and value are read 
// in from the Token_stream.
{
	Token t = ts.get();

	string var_name;
	double value;
	bool is_constant = false;

	// if the Variable is declared to be constant
	if (t.name == const_string) {
		Token next = ts.get();
		
		// check if a correct name is read
		if (next.kind != name && next.kind != '_') 
			error("error in declaration syntax");
		else var_name = next.name;

		// throw error if variable already exists
		if (symtab.is_declared(var_name)) error(var_name, " declared twice");

		Token next2 = ts.get();
		if (next2.kind == '=') {
			value = expression();
			is_constant = true;
		}
		else {
			error("error in declaration syntax for ", var_name);
		}		
		// and declare the variable's value
		symtab.declare(var_name, value, is_constant);
	} 
	// otherwise, Variable can be edited
	else {
		// check if a correct name is read
		if (t.kind != name && t.kind != '_')
			error("error in declaration syntax");		
		var_name = t.name;

		// throw error if variable already exists
		if (symtab.is_declared(var_name)) error(var_name, " declared twice");

		// keep reading declaration
		Token next = ts.get();
		if (next.kind == '=') {
			value = expression();
		}
		else {
			error("error in declaration syntax for ", var_name);
		}
		// and declare the variable's value
		symtab.declare(var_name, value, is_constant);
	}

	return value;
	
}

double statement()
	// Function for evaluating statements for declaring or setting variables
	// Returns the value of the statement or declared variable
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
	// Function for ignoring all input until print character
{	
	ts.ignore(print);
}

void calculate()
	// Function that calls for calculations unless help/showvar/quit is chosen
{
	while (cin)
	try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();		
		if (t.kind == helpchar){
			cout << help_message;
		}
		else if (t.kind == showvarchar) {
			symtab.print_vars();
		}		
		else if (t.kind == quitchar) {
			return;
		}
		else {
			ts.unget(t);
			// get result of computation
			double stat = statement();			

			// set ans to result, and output
			symtab.set(ans, stat);			
			cout << stat << endl;
		}				
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
};

int main()
	// main function
{
	// Initialize standard stored values "pi" and "e", "ans" is set to 0.0
	symtab.declare(ans, 0.0);
	symtab.declare(e_string, M_E, true);
	symtab.declare(pi_string, M_PI, true);	

	// print out starting message
	cout << starting_message;

	try {
		// keep calculating until errors are caught or user wants to quit
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
