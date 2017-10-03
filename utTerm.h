#ifndef UTTERM_H
#define UTTERM_H
#include "include/Number.h"
#include "include/Term.h"
#include "include/Atom.h"
#include "include/Variable.h"
#include <iostream>
using namespace std;


//test Number.value()
TEST (Number,ctor) {
	Number num(5);
	ASSERT_EQ("5",num.value());
}
//test Number.symbol()
TEST (Number, symbol) {
	Number num(5);
	ASSERT_EQ("5",num.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
	Number num1(25);
	Number num2(25);
	ASSERT_TRUE(num1.match(&num2));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
	Number num1(25);
	Number num2(0);
	ASSERT_FALSE(num1.match(&num2));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
	Number num1(25);
	Atom tom("tom");
	ASSERT_FALSE(num1.match(&tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
	Number num1(25);
	Var X("X");
	ASSERT_TRUE(num1.match(&X));
	//cout << X.symbol() << endl;
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
	Atom tom("tom");
	Number num1(25);
	ASSERT_FALSE(tom.match(&num1));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
	Atom tom("tom");
	Var X("X");
	//cout << X.symbol() << endl;
	ASSERT_TRUE(tom.match(&X));
	ASSERT_EQ("tom",X.symbol());
	//cout << X.symbol() << endl;
	
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
	Atom tom("tom");
	Var X("X");
	//cout << X.symbol() << endl;
	ASSERT_TRUE(X.match(&tom));
	//cout << X.symbol() << endl;
	ASSERT_TRUE(tom.match(&X));
	//cout << X.symbol() << endl;
	ASSERT_EQ("tom",X.symbol());
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
	Var X("X");
	Atom tom("tom");
	Atom jerry("jerry");
	//cout << X.symbol() << endl;
	ASSERT_TRUE(X.match(&jerry));
	//cout << X.symbol() << endl;
	ASSERT_FALSE(tom.match(&X));
	//cout << X.symbol() << endl;
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
	Var X("X");
	Number num(5);
	ASSERT_TRUE(X.match(&num));
	ASSERT_EQ("5",X.symbol());
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
	Var X("X");
	Number num1(25);
	Number num2(100);
	ASSERT_TRUE(X.match(&num1));
	ASSERT_FALSE(X.match(&num2));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
	Var X("X");
	Atom tom("tom");
	Number num(25);
	//cout << X.symbol() << endl;
	ASSERT_TRUE(X.match(&tom));
	//cout << X.symbol() << endl;
	ASSERT_FALSE(X.match(&num));
	//cout << X.symbol() << endl;
}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
	Var X("X");
	Atom tom("tom");
	Number num(25);
	//cout << X.symbol() << endl;
	ASSERT_TRUE(tom.match(&X));
	//cout << X.symbol() << endl;
	ASSERT_FALSE(X.match(&num));
	//cout << X.symbol() << endl;
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
	Atom tom("tom");
	Var X("X");
	ASSERT_TRUE(X.match(&tom));
	ASSERT_TRUE(X.match(&tom));
}
#endif
