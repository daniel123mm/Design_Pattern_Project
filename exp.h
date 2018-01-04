#ifndef EXP_H
#define EXP_H

#include "atom.h"
#include "global.h"
#include <typeinfo>
#include <iostream>
using std::cout;

class Exp {
public:
	virtual bool evaluate() = 0;
	virtual string getEvaluateResult() = 0;
};


class MatchExp : public Exp {
public:
	MatchExp(Term* left, Term* right) : _left(left), _right(right){

	}

	bool evaluate(){
		return _left->match(*_right);
	}

	string getEvaluateResult(){
		if (_left->symbol() == _right->symbol()){
			return "true";
		}
		if (typeid(*_left) == typeid(Struct) || typeid(*_left) == typeid(List)){
			return  _left->value() + " = " + _right->symbol();
		}
		if (typeid(*_right) == typeid(Struct) || typeid(*_right) == typeid(List)){
			return  _left->symbol() + " = " + _right->value();
		}
		if (!_left->match(*_right)){
			return "false";
		}

		return _left->symbol() + " = " + _right->symbol();
	}

private:
	Term* _left;
	Term* _right;
};

class ConjExp : public Exp {
public:
	ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {

	}

	bool evaluate() {
		return (_left->evaluate() && _right->evaluate());
	}

	string getEvaluateResult(){
		string _strLeft = _left->getEvaluateResult();
		string _strRight = _right->getEvaluateResult();
		MatchExp* _MatchEcp = dynamic_cast<MatchExp*>(_left);

		if (_strLeft == "true")
			return  _strRight;
		if (_strRight == "true")
			return  _strLeft;
		if (!evaluate()){
			return  "";
		}

		if (_strLeft.compare(_strRight) == 0){
			return _strLeft;
		}
		else if (!_MatchEcp){
			string str = "";
			for (int i = 0; i < _strLeft.length(); i++){

				if (_strLeft.at(i) != ','){
					str += _strLeft.at(i);
				}

				if (i == _strLeft.length() - 1 || _strLeft.at(i) == ','){
					i++;
					if (table.empty()){
						table.push_back(str);
					}
					else{
						for (int j = 0; j < table.size(); j++){
							if (str.compare(table[j]) == 0){
								return _strLeft;
							}
						}
						table.push_back(str);
					}
					str = "";
				}
			}
			
			for (int p = 0; p < table.size(); p++){
				if (_strRight.compare(table[p]) == 0){
					return _strLeft;
				}
			}
			return  _strLeft + ", " + _strRight;
		}


		return _strLeft + ", " + _strRight;
	}

private:
	Exp * _left;
	Exp * _right;
};

class DisjExp : public Exp {
public:
	DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {

	}

	bool evaluate() {
		return (_left->evaluate() || _right->evaluate());
	}

	string getEvaluateResult(){
		if (_right->getEvaluateResult() == ""){
			return _left->getEvaluateResult();
		}
		return _left->getEvaluateResult() + "; " + _right->getEvaluateResult();
	}

private:
	Exp * _left;
	Exp * _right;
};
#endif
