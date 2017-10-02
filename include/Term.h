#ifndef TERM_H
#define TERM_H
#include <string>


using std::string;

class Term{
	public:
		Term (string s):_symbol(s){}
		bool match(Term n){return _symbol == n._symbol;}

		
	private:
		string _symbol;
};

#endif