#ifndef NUMBER_H
#define NUMBER_H
#include <iostream>
#include <string>
#include <sstream>
#include "term.h"



using std::string;
using std::to_string;

class Number :public Term{ 
	public:
		Number (double value){
			std::stringstream ss ;
			ss << value;
			_num = ss.str();
		} //: _num((std::stringstream() << value).str()){}
		
		string symbol() const {return _num;}
		
		bool match(Term &t){
			if(t.isVar()){
				return t.match(*this);
			}
			return value() == t.value();
			 
		}
	
	private:
		string _num;
};

#endif
