#ifndef UTTERM_H
#define UTTERM_H
#include "term.h"
#include "atom.h"
#include "struct.h"
//#include "variable.h"
//#include "number.h"
#include <iostream>


//test struct.name()
TEST (Atom,test) {
	Atom tom ("tom");
	ASSERT_EQ("tom", tom.symbol());
}

//test struct.name()
TEST (Struct,symbol) {
	Atom tom ("tom");
	Atom fish("fish");
	std::vector<Term *> vec = {&tom, &fish};
	Struct like(Atom("like"),vec);
	ASSERT_EQ("like(tom, fish)", like.symbol());
}

TEST (Struct,match1) {
	Atom tom ("tom");
	Atom fish("fish");
	std::vector<Term *> vec = {&tom, &fish};
	Struct like(Atom("like"),vec);
	Struct like2(Atom("like1"),vec);
	ASSERT_FALSE(like.match(like2));
}

TEST (Struct,match2) {
	Atom tom ("tom");
	Atom fish("fish");
	std::vector<Term *> vec = {&tom, &fish};
	std::vector<Term *> vec1 = {&tom};
	Struct like(Atom("like"),vec);
	Struct like2(Atom("like"),vec1);
	ASSERT_FALSE(like.match(like2));
}

TEST (Struct,match3) {
	Atom tom ("tom");
	Atom fish("fish");
	std::vector<Term *> vec = {&tom, &fish};
	std::vector<Term *> vec1 = {&fish, &fish};
	Struct like(Atom("like"),vec);
	Struct like2(Atom("like"),vec1);
	ASSERT_FALSE(like.match(like2));
}

TEST (Struct,match4) {
	Atom tom ("tom");
	Atom fish("fish");
	std::vector<Term *> vec = {&tom, &fish};
	Struct like(Atom("like"),vec);
	ASSERT_FALSE(like.match(tom));
}

TEST (Struct,match5) {
	Atom tom ("tom");
	Atom fish("fish");
	std::vector<Term *> vec = {&tom, &fish};
	Struct like(Atom("like"),vec);
	Struct like2(Atom("like"),vec);
	ASSERT_TRUE(like.match(like2));
}
/*
TEST (Struct,match) {
	Atom tom ("tom");
	Atom fish("fish");
	std::vector<Term *> vec = {&tom, &fish};
	std::vector<Term *> vec1 = {&tom, &tom};
	Struct like(Atom("like"),vec);
	Struct like1(Atom("like"),vec);
	ASSERT_TRUE(like.match(like1));
}

TEST (Struct, variable){
	Atom tom ("tom");
	Atom fish("fish");
	std::vector<Term *> vec = {&tom, &fish};
	Struct like(Atom("like"),vec);
	Variable X("X");
	ASSERT_TRUE(like.match(X));
	ASSERT_EQ("like(tom, fish)", X.value());

}

TEST (Struct, inVariable){
	Atom tom ("tom");
	Atom fish("fish");
	std::vector<Term *> vec = {&tom, &fish};
	Struct like(Atom("like"),vec);
	Variable X("X");
	ASSERT_TRUE(X.match(like));
	ASSERT_FALSE(X.match(tom));
	ASSERT_EQ("like(tom, fish)", X.value());

}

TEST (Struct, Number){
	Number num1(123);
	Atom tom ("tom");
	Atom fish("fish");
	std::vector<Term *> vec = {&tom, &fish};
	Struct like(Atom("like"),vec);
	ASSERT_FALSE(num1.match(like));
	//ASSERT_EQ("like(tom, fish)", X.value());

}
*/

#endif
