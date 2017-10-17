#ifndef TERM_H
#define TERM_H
#include <string>


using std::string;

class Term{
	public:
		virtual string symbol() const = 0;
		virtual string value() const{return symbol();}
		virtual bool match(Term &t){return symbol() == t.symbol();}
		virtual bool isVar(){return false;} 
		virtual void setValue(string s){}

};

#endif