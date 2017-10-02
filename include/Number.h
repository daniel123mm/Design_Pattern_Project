#ifndef NUMBER_H
#define NUMBER_H
#include <iostream>
#include <string>
//#include "Term.h"



using std::string;
using std::to_string;

class Number { 
	public:
		//Number (int n):Term(_symbol), _num(n){}//_symbol = to_string(_num);}
		Number(string n):_symbol(n){}
		string value(){
			//_symbol = to_string(_num);
			return _symbol;
		}
		string symbol(){
			//_symbol = to_string(_num);
			return _symbol;
		}
		bool match(Number n){return _symbol == n._symbol;}
		
	private:
		int _num;
		string _symbol;
};

#endif
