#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;

class Atom : public Term{
	public:
		Atom (string s): Term(s) {}
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
	
};

#endif