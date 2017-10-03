#ifndef NUMBER_H
#define NUMBER_H
#include <iostream>
#include <string>
#include "term.h"



using std::string;
using std::to_string;

class Number :public Term{ 
	public:
		Number (int n) : Term(to_string(n)), _num(n){}
		string value(){
			//_symbol = to_string(_num);
			return symbol();
		}
		bool isVar(){
			return false;
		}
		
		bool match(Term *t){
			if(t->isVar()){
				return t->match(this);
			}
			return symbol() == t->symbol();
			 
		}
		
	private:
		int _num;
};

#endif
