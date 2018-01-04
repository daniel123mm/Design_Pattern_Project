#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "number.h"
#include "iterator.h"

TEST(iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term*> *itStruct = s.createIterator();
    itStruct->first();
    ASSERT_EQ("1", (itStruct->currentItem())->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

TEST(iterator, nested_iterator) {
   Number one(1);
   Variable X("X");
   Variable Y("Y");
   Number two(2);
   Struct t(Atom("t"), { &X, &two });
   Struct s(Atom("s"), { &one, &t, &Y });
   //StructIterator it(&s);
   Iterator<Term*> *it = s.createIterator();
   it->first();
   it->next();
   Struct *s2 = dynamic_cast<Struct *>(it->currentItem());
   //StructIterator it2(s2);
   Iterator<Term*> *it2 = s2->createIterator();
   it2->first();
   ASSERT_EQ("X", it2->currentItem()->symbol());
   ASSERT_FALSE(it2->isDone());
   it2->next();
   ASSERT_EQ("2", it2->currentItem()->symbol());
   ASSERT_FALSE(it2->isDone());
   it2->next();
   ASSERT_TRUE(it2->isDone());
}


TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    Iterator<Term*> *itList = l.createIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}


TEST(iterator, NullIterator){
  Number one(1);
  NullIterator<Term*> nullIterator(&one);
  nullIterator.first();
  ASSERT_TRUE(nullIterator.isDone());
  Iterator<Term*> * it = one.createIterator();
  it->first();
  ASSERT_TRUE(it->isDone());
}

//s(X,2,tom)
TEST(iterator, StructBFSIterator){
  Variable X("X");
  Number two(2);
  Atom tom("tom");
  Struct t(Atom("t"), { &X, &two, &tom });
  Iterator<Term*> * it = t.createBFSIterator();
  it->first();
  ASSERT_EQ("X", it->currentItem()->symbol());
  ASSERT_FALSE(it->isDone());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("tom", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());

}

////s(1,t(1,2,a(3)),z())
//TEST(iterator, StructBFSIterators){
//  Number one(1);
//  Number two(2);
//  Number three(3);
//  Struct z(Atom("z"), { });
//  Struct a(Atom("a"), { &three});
//  Struct t(Atom("t"), { &one, &two, &a });
//  Struct s(Atom("s"), { &one, &t, &z });
//  Iterator<Term*> * it = s.createBFSIterator();
//  it->first();
//  ASSERT_EQ("1", it->currentItem()->symbol());
//  ASSERT_FALSE(it->isDone());
//  it->next();
//  ASSERT_EQ("t(1, 2, a(3))", it->currentItem()->symbol());
//  it->next();
//  ASSERT_EQ("z()", it->currentItem()->symbol());
//  it->next();
//  ASSERT_EQ("1", it->currentItem()->symbol());
//  it->next();
//  ASSERT_EQ("2", it->currentItem()->symbol());
//  it->next();
//  ASSERT_EQ("a(3)", it->currentItem()->symbol());
//  it->next();
//  ASSERT_EQ("3", it->currentItem()->symbol());
//  it->next();
//  ASSERT_TRUE(it->isDone());
//
//}

//[X,2,tom]
TEST(iterator, ListBFSIterator){
  Variable X("X");
  Number two(2);
  Atom tom("tom");
  List t({ &X, &two, &tom });
  Iterator<Term*> * it = t.createBFSIterator();
  it->first();
  ASSERT_EQ("X", it->currentItem()->symbol());
  ASSERT_FALSE(it->isDone());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("tom", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}

//[1,[1,2,[]],3]
TEST(iterator, ListBFSIterator2){
  Number one(1);
  Number two(2);
  Number three(3);
  List a;
  List t({ &one, &two, &a });
  List s({ &one, &t, &three });  
  Iterator<Term*> * it = s.createBFSIterator();
  it->first();
  ASSERT_EQ("1", it->currentItem()->symbol());
  ASSERT_FALSE(it->isDone());
  it->next();
  ASSERT_EQ("[1, 2, []]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("3", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[]", it->currentItem()->symbol());
  it->next();
  //ASSERT_EQ("3", it->currentItem()->symbol());
  //it->next();
  ASSERT_TRUE(it->isDone());

}

//s(X,2,tom)
TEST(iterator, StructDFSIterator){
  Variable X("X");
  Number two(2);
  Atom tom("tom");
  Struct t(Atom("t"), { &X, &two, &tom });
  Iterator<Term*> * it = t.createDFSIterator();
  it->first();
  ASSERT_EQ("X", it->currentItem()->symbol());
  ASSERT_FALSE(it->isDone());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("tom", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}

//s(1,t(1,2,a(3)),3)
TEST(iterator, StructDFSIterator2){
  Number one(1);
  Number two(2);
  Number three(3);
  Struct a(Atom("a"), { &three});
  Struct t(Atom("t"), { &one, &two, &a });
  Struct s(Atom("s"), { &one, &t, &three });  
  Iterator<Term*> * it = s.createDFSIterator();
  it->first();
  ASSERT_EQ("1", it->currentItem()->symbol());
  ASSERT_FALSE(it->isDone());
  it->next();
  ASSERT_EQ("t(1, 2, a(3))", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("a(3)", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("3", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("3", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());

}

//[X,2,tom]
TEST(iterator, ListDFSIterator){
  Variable X("X");
  Number two(2);
  Atom tom("tom");
  List t({ &X, &two, &tom });
  Iterator<Term*> * it = t.createDFSIterator();
  it->first();
  ASSERT_EQ("X", it->currentItem()->symbol());
  ASSERT_FALSE(it->isDone());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("tom", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}

//[1,[1,2,[3]],3]
TEST(iterator, ListDFSIterator2){
  Number one(1);
  Number two(2);
  Number three(3);
  List a({ &three});
  List t({ &one, &two, &a });
  List s({ &one, &t, &three });    
  Iterator<Term*> * it = s.createDFSIterator();
  it->first();
  ASSERT_EQ("1", it->currentItem()->symbol());
  ASSERT_FALSE(it->isDone());
  it->next();
  ASSERT_EQ("[1, 2, [3]]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[3]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("3", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("3", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());

}

#endif
