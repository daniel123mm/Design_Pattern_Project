#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"
using std::string;

class Atom : public Term{
	public:
		Atom (string s):_symbol(s) {}
		string symbol() const {return _symbol;}
	private:
		string _symbol;
	
};

#endif