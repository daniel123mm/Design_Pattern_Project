#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;

class Atom {
	public:
		Atom (string s):_symbol(s) {}
		bool match(Atom a){return _symbol == a.symbol;}
	
};

#endif