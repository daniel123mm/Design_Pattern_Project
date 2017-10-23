#ifndef LIST_H
#define LIST_H

#include "term.h"

#include <vector>
using std::vector;

class List : public Term {
public:
  List (): _elements() {}
  
  List (vector<Term *> const & elements):_elements(elements){}
  
  Term * head() const{
	if(_elements.empty()){
		throw "Accessing head in an empty list";
	}
	return _elements[0];
  }
  
  List * tail() const{
	if(_elements.empty()){
		throw "Accessing tail in an empty list";
	}
	std::vector<Term *> v;
	for(unsigned int i = 1;i < _elements.size();i++){
		v.push_back(_elements[i]);
	}
	List *ls = new List(v);
	return ls;
  }

  string symbol() const{
	 string sym = "";
	 if(_elements.empty())
		 return "[]";
	 for(unsigned int i = 0;i < _elements.size() - 1;i++){
		sym += (_elements[i]->symbol() + ", ");
	 }
	 return "[" + sym + _elements[_elements.size() - 1]->symbol() + "]"; 
  }
  
  string value() const{
	 string sym = "";
	 if(_elements.empty())
		 return "[]";
	 for(unsigned int i = 0;i < _elements.size() - 1;i++){
		sym += (_elements[i]->value() + ", ");
	 }
	 return "[" + sym + _elements[_elements.size() - 1]->value() + "]"; 
  }
  
  bool isList(){
	return true;
  }
  
  bool match(Term & term){
	List *ls = dynamic_cast<List *> (&term);
	if(ls){
		if(_elements.size() != ls->_elements.size())
			return false;
		for(unsigned int i = 0;i < _elements.size();i++){
			if(!(_elements[i]->match(*(ls->_elements[i]))))
					return false;
		}
		return true;
	}
	if(term.isVar()){
		for(unsigned int i = 0;i < _elements.size();i++){
			if(_elements[i]->value() == term.value())
				return false;
		}
		return true;
	}
	return value() == term.value();
  }


private:
  vector<Term *> _elements;

};

#endif
