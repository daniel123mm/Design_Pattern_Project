#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;

class Atom : public Term{
	public:
		Atom (string s): Term(s) {}
		bool match(Term *t){return symbol() == t->symbol();}
	
};

#endif