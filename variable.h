#ifndef VAR_H
#define VAR_H
#include <string>
#include <iostream>
#include "term.h"



using std::string;
using std::to_string; 

class Variable : public Term{ 
	public:
		Variable (string s) :_symbol(s),_assignValue(s){}
		
		void setValue (string s){
			_assignValue = s;
		}
		string symbol() const{
			return _symbol;
		}
		
		string value() const{
			return _assignValue;
		}
		bool isVar(){
			return true;
		}
	
	    void findValue(Variable* v,Term &t){
			for(unsigned int i = 0;i < v->have_match.size();i++){
				if(v->have_match[i]->assignable == false)
					break;
				else{
					v->have_match[i]->_assignValue = t.value();
					v->have_match[i]->assignable = false;
					
				}	
				findValue(v->have_match[i],t);
			}

		}
		
		bool match(Term &t){
			Variable *var = dynamic_cast<Variable*> (&t);
			if(var){
				//_symbol = var->symbol();
				have_match.push_back(var);
                var->have_match.push_back(this);
				if(assignable && !var->assignable){
					_assignValue = var->value();
					assignable = false;
					return true;
				}
				if(!assignable && var->assignable){
					var->value() = _assignValue;
					var->assignable = false;
					return true;
					//findValue(var,this);
				}
				if(!assignable && !var->assignable){
					return value() == t.value();
				}
				return true;
					
			}
			if(assignable && !var){
				_assignValue = t.value();
				assignable = false;
				findValue(this,t);
				return true;
			}else{
                return value() == t.value();
			}
		}
		

	private:
		bool assignable = true;
		string _symbol;
		string _assignValue;
		std::vector <Variable *> have_match;
		bool has_var = false;
		
		
		
		
};

#endif
