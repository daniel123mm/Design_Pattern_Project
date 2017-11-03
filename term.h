#ifndef TERM_H
#define TERM_H
#include <string>


using std::string;

class Term{
	public:
		virtual string symbol() const = 0;
		//virtual Term & termValue() const{return term;}
		virtual string value() const{return symbol();}
		virtual bool match(Term &t){return symbol() == t.symbol();}
		virtual bool isVar(){return false;} 
		virtual bool isList(){return false;} 

		
};

#endif