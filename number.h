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
			_symbol = ss.str();
		} 
};

#endif
