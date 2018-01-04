#ifndef VAR_H
#define VAR_H
#include <string>
#include <iostream>
#include <vector>
#include "term.h"

using std::string;

class Variable : public Term{ 
	public:
		Variable(string s):Term(s), _termValue(0) {}
		
		string value() const{
            if (_termValue) 
                return _termValue->value();
			return Term::value();
		}

		bool isVar(){
			return true;
		}

	    //find the variable relationships that x match y and y match z
	    void findValue(Variable* v,Term *t){
			for(unsigned int i = 0;i < v->have_match.size();i++){
				if(v->have_match[i]->assignable == false)
					break;
				else{
                    v->have_match[i]->_termValue = t;
					v->have_match[i]->assignable = false;
					
				}	
				findValue(v->have_match[i],t);   
			}
		}
		
		bool match(Term &t){
			Variable *var = dynamic_cast<Variable*> (&t); 
			//if the term is variable build relationships
			if(var){
				have_match.push_back(var);
				var->have_match.push_back(this);
				if(assignable && !var->assignable){
					findValue(var,var);
				}
				if(!assignable && var->assignable){
					findValue(this,this);
				}
				if(!assignable && !var->assignable){
					return value() == t.value();
				}
				return true;		
			}
			if(assignable && !var){
				if(t.isList()){
					if(t.match(*this)){
						_termValue = &t;
						assignable = false;
						findValue(this,&t);
						return t.match(*this);
					}
					return t.match(*this);
				}
				_termValue = &t;
				assignable = false;
				findValue(this,&t);
				return true;
			}else{
                return value() == t.value();
			}
		}
		

	private:
		bool assignable = true;
		std::vector <Variable *> have_match;
		Term * _termValue;
};

#endif
