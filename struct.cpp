#include "struct.h"
#include "iterator.h"


string Struct::symbol() const{
	if(_argc.empty()){
		return _name.symbol() + "()";
	}
	string sym = "";
	for(unsigned int i = 0;i < _argc.size() - 1;i++){
		sym += (_argc[i]->symbol() + ", ");
	}
	return _name.symbol() + "(" + sym  + _argc[_argc.size() - 1]->symbol() + ")";
}

string Struct::value() const{
    if(_argc.empty()){
        return _name.symbol() + "()";
    }
	string sym = "";
	for(unsigned int i = 0;i < _argc.size() - 1;i++){
		sym += (_argc[i]->value() + ", ");
	}
	return _name.symbol() + "(" + sym  + _argc[_argc.size() - 1]->value() + ")";
}

bool Struct::match(Term &term){
	Struct *st = dynamic_cast<Struct *> (&term);
		if(st){
			if(!_name.match(st->_name))
				return false;
			if(_argc.size() != st->_argc.size())
				return false;
			for(unsigned int i = 0;i < _argc.size();i++){
				if(_argc[i]->symbol() != st->_argc[i]->symbol())
					return false;
			}
			return true;
		}
		return Term::match(term);
}
		
Iterator<Term*> * Struct::createIterator(){
   return new StructIterator<Term*>(this);
}

Iterator<Term*> * Struct::createBFSIterator(){
  return new BFSIterator<Term*>(this);
}

Iterator<Term*> * Struct::createDFSIterator(){
  return new DFSIterator<Term*>(this);
}
