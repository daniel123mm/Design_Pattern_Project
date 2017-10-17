#ifndef STRUCT_H
#define STRUCT_H
#include <vector>
#include "term.h"
#include "atom.h"

class Struct : public Term{
	public:
		Struct (Atom const &name, std::vector<Term *> v)
			:_name(name), _argc(v){}
		Atom const & name() {
			return _name;			
		}	
		Term* args(int index){
			return _argc[index];
		}
		
		bool match(Term &t){
			Struct *st = dynamic_cast<Struct *> (&t);
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
			return false;
			
		}
		
		string symbol() const{
			string sym = "";
			for(unsigned int i = 0;i < _argc.size() - 1;i++){
				sym += (_argc[i]->symbol() + ", ");
			}
			return _name.symbol() + "(" + sym  + _argc[_argc.size() - 1]->symbol() + ")";
		}
		string value() const{
			string sym = "";
			for(unsigned int i = 0;i < _argc.size() - 1;i++){
				sym += (_argc[i]->value() + ", ");
			}
			return _name.symbol() + "(" + sym  + _argc[_argc.size() - 1]->value() + ")";
		}
	private:
		Atom _name;
		std::vector<Term *> _argc;
};

#endif