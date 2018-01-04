#ifndef STRUCT_H
#define STRUCT_H
#include <vector>
#include "term.h"
#include "atom.h"

class Struct : public Term{
	public:
		bool match(Term &t);
		string symbol() const;
		string value() const;
		Iterator<Term*> *createIterator();
		Iterator<Term*> *createBFSIterator();
		Iterator<Term*> *createDFSIterator();
	public:
	   Struct (Atom const &name, std::vector<Term *> v)
			:_name(name), _argc(v){}

       Struct (Atom const &name)
			:_name(name), _argc(){}
			
		Atom const & name() {
			return _name;			
		}	

		Term* args(int index){
			return _argc[index];
		}

		int arity(){
			return _argc.size();
		}
		
	private:
		Atom _name;
		std::vector<Term *> _argc;
};

#endif
