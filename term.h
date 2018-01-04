#ifndef TERM_H
#define TERM_H
#include <string>
#include <sstream>



using std::string;
template<class T>
class Iterator ;

class Term{
	public:
		virtual string symbol() const {return _symbol;}
		virtual string value() const {return symbol();}
		virtual bool match(Term &t);
		virtual bool isVar(){return false;} 
		virtual bool isList(){return false;}
		virtual Iterator<Term*> *createIterator();
		virtual Iterator<Term*> *createBFSIterator();
		virtual Iterator<Term*> *createDFSIterator();

	protected:
		Term (string s = ""):_symbol(s) {}
		string _symbol;
};
#endif