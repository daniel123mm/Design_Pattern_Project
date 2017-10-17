#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"
using std::string;

class Atom : public Term{
	public:
		Atom (string s):_symbol(s) {}
		
		string symbol() const {return _symbol;}
		
		bool match(Term &t){
			if(t.isVar()){
				return t.match(*this);
			}
			return value() == t.value();
			 
		}
	private:
		string _symbol;
	
};

#endif