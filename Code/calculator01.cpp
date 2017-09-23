#include "../std_lib_facilities.h"

// -- Token
class Token {
public:
	char kind;       // what kind of Token
	double value;    // for numbers: a value

	Token(char ch)   // Token for a char
		: kind(ch), value(0) {}

	Token(char ch, double val) // Token for a number
		: kind(ch), value(val) {}
};

//------------------------------------------------------------------------------
// -- Token stream
class Token_stream {
public:
	Token_stream();       // make a Token_stream that reads from cin
	Token get();          // get a Token (get() is defined elsewhere)
	void putback(Token t);// put a Token back 
private:
	bool full;    // is there a Token in the buffer?
	Token buffer; // here is where we keep a Token put back using putback()
};

// Construction just sets full to indicate the buffer is empty:
Token_stream::Token_stream()
	: full(false), buffer(0) // be default: no token in buffer
{}

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
	if (full) error("putback() into a full buffer");
	buffer = t;
	full = true;
}

// This returns the first Token, either from the buffer or from cin
Token Token_stream::get()
{
	if (full) { // do we have a Token in the buffer
		// remove and return
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch; // note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch) {
	case '(': case ')': case '+': case '-': case '*':case '/':
		return Token(ch); // let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch); // put the digit back into the input stream
		double val;
		cin >> val;      // have the input stream read the floating-point number, including the previously put-back digit
		return Token('8', val); // let 8 represent a number
	}
	default:
		error("Bad token");
	}
}

// -- Declarations --
Token_stream ts;     // provides get() and putback()

double expression(); // read and evaluate an Expression
double term();       // read and evaluate a Term
double primary();    // read and evaluate a Primary

// -- Main function, calculator starts here
int main()
{
	try {
		while (cin)
			cout << "=" << expression() << '\n';
		keep_window_open();
	}
	catch (exception& e) {
		cerr << e.what() << endl;
		keep_window_open("~1");
		return 1;
	}
	catch (...) {
		cerr << "exception" << endl;
		keep_window_open("~2");
		return 2;
	}

	return 0;
}

// -- Expression
double expression()
{
	double left = term();   // read and evaluate a Term
	Token t = ts.get();     // get the next Token from token stream

	while (true) {
		switch (t.kind) {
		case '+':
			left += term(); // evaluate Term and add
			t = ts.get();
			break;
		case '-':
			left -= term(); // evaluate term and subtract
			t = ts.get();
			break;
		default:
			ts.putback(t);  // put t back into the token stream
			return left;    // finally, no more + or -: return the answer
		}
	}
}

// -- Term
double term()
{
	double left = primary();  
	Token t = ts.get(); // get the next Token from token stream

	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t); // put t back into the token stream
			return left;
		}
	}
}

// -- Primary
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
	case '8':
		return t.value;
	default:
		error("primary expected");
	}
}