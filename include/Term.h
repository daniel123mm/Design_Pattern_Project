#ifndef TERM_H
#define TERM_H
#include <string>


using std::string;

class Term{
	public:
		Term (string s):_symbol(s){}
		string setSymbol(string s){
			_symbol = s;
		}
		string symbol(){
			return _symbol;
		}

		
	private:
		string _symbol;
};

#endif