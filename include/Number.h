#ifndef NUMBER_H
#define NUMBER_H
#include <iostream>
#include <string>


using std::string;
using std::to_string;

class Number{
	public:
		Number (int n):_num(n){}
		string value(){
			_symbol = to_string(_num);
			return _symbol;
		}
		string symbol(){
			_symbol = to_string(_num);
			return _symbol;
		}
		bool match(Number n){return this->symbol() == n.symbol();}
		
	private:
		int _num;
		string _symbol;
};

#endif