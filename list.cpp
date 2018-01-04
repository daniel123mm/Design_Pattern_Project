#include "list.h"
#include "iterator.h"

string List::symbol() const{
	 string sym = "";
	 if(_elements.empty())
		 return "[]";
	 for(unsigned int i = 0;i < _elements.size() - 1;i++){
		sym += (_elements[i]->symbol() + ", ");
	 }
	 return "[" + sym + _elements[_elements.size() - 1]->symbol() + "]"; 
}
 
string List::value() const{
	 string sym = "";
	 if(_elements.empty())
		 return "[]";
	 for(unsigned int i = 0;i < _elements.size() - 1;i++){
		sym += (_elements[i]->value() + ", ");
	 }
	 return "[" + sym + _elements[_elements.size() - 1]->value() + "]"; 
}

bool List::match(Term & term){
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
	return Term::match(term);

}

Iterator<Term*> * List::createIterator(){
  return new ListIterator<Term*>(this);
}

Iterator<Term*> * List::createBFSIterator(){
  return new BFSIterator<Term*>(this);
}

Iterator<Term*> * List::createDFSIterator(){
	return new DFSIterator<Term*>(this);
}

Term * List::head() const{
	if(_elements.empty()){
		throw string("Accessing head in an empty list");
	}
	return _elements[0];
}
  
List * List::tail() const{
	if(_elements.empty()){
		throw string("Accessing tail in an empty list");
	}
	std::vector<Term *> v;
	for(unsigned int i = 1;i < _elements.size();i++){
		v.push_back(_elements[i]);
	}
	List *ls = new List(v);
	return ls;
}

Term * List::args(int index) {
    return _elements[index];
}
  
int List::arity() const {
	return _elements.size();
}