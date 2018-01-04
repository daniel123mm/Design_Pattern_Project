#include "term.h"
#include <vector>
#include "iterator.h"

Iterator<Term*> * Term::createIterator(){
  return new NullIterator<Term*>(this);
}

Iterator<Term*> * Term::createBFSIterator(){
  return new NullIterator<Term*>(this);
}

Iterator<Term*> * Term::createDFSIterator(){
  return new NullIterator<Term*>(this);
}

bool Term::match(Term &t){
  if(t.isVar()){
    return t.match(*this);
  }
  return value() == t.value();
}
