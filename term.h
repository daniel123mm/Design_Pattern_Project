#ifndef TERM_H
#define TERM_H
#include <string>
#include <sstream>



using std::string;
template<class T>
class Iterator ;

class Term{
	public:
	
		virtual string symbol() const = 0;
		virtual string value() const{return symbol();}
		virtual bool match(Term &t){return symbol() == t.symbol();}
		virtual bool isVar(){return false;} 
		virtual bool isList(){return false;}
		virtual Iterator<Term*> *createIterator();
		virtual Iterator<Term*> *createBFSIterator();
		virtual Iterator<Term*> *createDFSIterator();
    protected:
		string _symbol;
};
#endif