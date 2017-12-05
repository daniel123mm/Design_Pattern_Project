#ifndef LIST_H
#define LIST_H

#include "term.h"
#include <vector>
#include <string>
using std::vector;
using std::string;


class List : public Term {
public:
	string symbol() const;
	string value() const;
	bool isList(){return true;}
	bool match(Term & term);
	Iterator<Term*> *createIterator();
	Iterator<Term*> *createBFSIterator();
	Iterator<Term*> *createDFSIterator();
public:
  List (): _elements() {}
  
  List (vector<Term *> const & elements):_elements(elements){}
  
  Term * head() const;
 
  List * tail() const;
  
  Term * args(int index);
  
  int arity() const;

private:
  vector<Term *> _elements;

};

#endif
