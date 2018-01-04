#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"
#include "atom.h"
#include "term.h"
#include <queue>
#include <iostream>
#include <typeinfo>

template<class T>
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual T currentItem() const = 0;
  virtual bool isDone() const = 0;
};

template<class T>
class NullIterator :public Iterator<T>{
public:
  NullIterator(T n){}
  void first(){}
  void next(){}
  T currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }

};

template<class T>
class StructIterator :public Iterator<T> {
public:
  friend class Struct;
  void first() {
    _index = 0;
  }

  T currentItem() const {
    return _s->args(_index);
  }

  bool isDone() const {
    return _index >= _s->arity();
  }

  void next() {
    _index++;
  }
private:
  StructIterator(Struct *s): _index(0), _s(s) {}
  int _index;
  Struct* _s;
};

template<class T>
class ListIterator :public Iterator<T> {
public:
  friend class List;
 
  void first() {
    _index = 0;
  }

  T currentItem() const {
    return _list->args(_index);
  }

  bool isDone() const {
    return _index >= _list->arity();
  }

  void next() {
    _index++;
  }
private:
  ListIterator(List *list): _index(0), _list(list) {}
  int _index;
  List* _list;
};

template<class T>
class BFSIterator :public Iterator<T>{
  public:
  BFSIterator(T term): _term(term){}

  void first() {
    _element.push(_term);    //init
	  convertToBFS(_term);    //to BFS traversal
  }

  T currentItem() const {
    return _BFS.front();
  }

  bool isDone() const {
    return  _BFS.empty();
  }

  void next() {
    _BFS.pop();
  }
  
  void convertToBFS(T term){
	 _element.pop();
	 Iterator<T> * it = term->createIterator();
	 for(it->first();!it->isDone();it->next()){
		 T currentTerm = it->currentItem();
		 if (typeid(*currentTerm) ==  typeid(Struct) || typeid(*currentTerm) ==  typeid(List)){
			 _element.push(currentTerm);
		 }
		_BFS.push(currentTerm);
	 }
	 if(!_element.empty()){
		convertToBFS(_element.front());
	 }
  }
  
private:
  T _term;
  std::queue <T> _BFS;
  std::queue <T> _element;
  
};

template<class T>
class DFSIterator :public Iterator<T>{
public:
DFSIterator(T term):_index(0), _term(term){}

void first() {
  convertToDFS(_term); //to DFS traversal 
  _index = 0;  
}

T currentItem() const {
  return _DFS[_index];
}

bool isDone() const {
  return _index >= (int)_DFS.size();
}

void next() {
  _index++;
}

void convertToDFS(T term){
	Iterator<T> * it = term->createIterator();
	for(it->first();!it->isDone();it->next()){
		T currentTerm = it->currentItem();
		_DFS.push_back(currentTerm);
		if (typeid(*currentTerm) ==  typeid(Struct) || typeid(*currentTerm) ==  typeid(List)){
			 convertToDFS(currentTerm);
		}
	}
}

private:
int _index;
T _term;
std::vector <T> _DFS;
};


#endif
