#ifndef VAR_H
#define VAR_H
#include <string>




using std::string;
using std::to_string;

class Var :public Term{ 
	public:
		Var (string s) : Term(s),assignValue(s){}
		
		string symbol(){
			return assignValue;
		}
		bool isVar(){
			return true;
		}
		bool match(Term *t){
			if(assignable){
				assignValue = t->symbol();
				assignable = false;
				return true;
			}else{
				if(assignValue == t->symbol())
					return true;
				else
					return false;
			}
		}
		
	private:
		bool assignable = true;
		string assignValue;	
};

#endif