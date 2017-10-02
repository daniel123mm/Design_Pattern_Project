#ifndef UTTERM_H
#define UTTERM_H
#include "include/Number.h"

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
	ASSERT_TRUE(num1.match(num2));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
	Number num1(25);
	Number num2(0);
	ASSERT_FALSE(num1.match(num2));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
	//Number num1(25);
	//Atom tom("tom");
	//ASSERT_TRUE(num1.match(tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
	///Number num1(25);
	//Variable X("X");
	//ASSERT_TRUE(num1.match(X));
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
	//Atom tom("tom");
	//Number num1(25);
	//ASSERT_TRUE(num1.match(X));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
	//Atom tom("tom");
	//Variable X("X");
	//ASSERT_TRUE(num1.match(X));
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {

}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {

}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
 
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {

}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {

}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {

}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){

}
#endif
