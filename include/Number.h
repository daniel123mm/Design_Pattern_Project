#ifndef NUMBER_H
#define NUMBER_H
#include <iostream>
#include <string>
#include "Term.h"



using std::string;
using std::to_string;

class Number :public Term{ 
	public:
		Number (int n) : Term(to_string(n)), _num(n){}
		string value(){
			//_symbol = to_string(_num);
			return symbol();
		}
	
		bool match(Term *t){return symbol() == t->symbol();}
		
	private:
		int _num;
};

#endif
