#ifndef TERM_H
#define TERM_H
#include <string>


using std::string;

class Term{
	public:
		Term (string s):_symbol(s){}
		string symbol(){
			return _symbol;
		}
		virtual bool isVar(){
			//return _var;
		}
		virtual bool match(Term &t){
			
		}

	private:
		string _symbol;
};

#endif