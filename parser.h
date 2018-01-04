#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <stack>
using std::string;
using std::stack;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "number.h"
#include "node.h"
#include "exp.h"
//#include "utParser.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
        Term *variable = new Variable(symtable[_scanner.tokenValue()].first);
        //if meet the COMMA when build the struct should find the repeat variable
        if(_sign == 1){
            for(int i = 0;i < (int)_findTerms.size();i++){
                Struct *st = dynamic_cast<Struct *> (_findTerms[i]);
				List *ls = dynamic_cast<List *> (_findTerms[i]);
                if(st){
                    variable = findStructArgs(st,variable);
                }else if(ls){
					variable = findListArgs(ls,variable);
				}else{
                    if(_findTerms[i]->symbol() == variable->symbol()){
                        variable = _findTerms[i];
                    }
                }
            }
        }
        return variable;
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);        
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else{
		return atom;
	  }
    }
    else if(token == '['){
      return list();
    }
    return nullptr;
  }

  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms(); 
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
	  Struct *structs =  new Struct(structName, args);
      return structs;
    } else {
      throw string("Unbalanced operator");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
	  List *list = new List(args);
      return list;
    } else {
      throw string("Unbalanced operator");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

void matchings(){ 
    while(_scanner.currentChar() != '.') {
     Term * term = createTerm();
     if ( term != nullptr ){
       if(_sign == 2){
         _findTerms.clear();
         _sign = 0;
       }
		Node * n = new Node(TERM, term, nullptr, nullptr);
		_terms.push_back(term);
		_findTerms.push_back(term);
        op_term.push(n);
      }
     if( _scanner.currentChar() == '=' ) {
        Node * n = new Node(EQUALITY);
        op_op.push(n);
     }
     if( _scanner.currentChar() == ',' ) {
		    _sign = 1;
        Node * n = new Node(COMMA);
        Node * temp = makeTree();
		    op_term.push(temp);
		    op_op.push(n);
     }
	  if( _scanner.currentChar() == ';' ) {
		    _sign = 2;
        Node * n = new Node(SEMICOLON);
        Node * temp = makeTree();
		    op_term.push(temp);
		    op_op.push(n);
     }
   }
    Node * temp ;
    while(op_op.size() > 0){
      temp = makeTree();
      op_term.push(temp);
      tree = temp;
    }
  }
  
  //to find the all level of Struct
  Term* findStructArgs(Struct *s, Term *v){
	   for(int j = 0;j < s->arity();j++){
			  if(Struct *st = dynamic_cast<Struct *> (s->args(j))){
				  return findStructArgs(st, v); 
			  }else{
			  	if(s->args(j)->symbol() == v->symbol()){
					  return s->args(j);
          }
			  }
     }  
     return v;
  }
  
  Term* findListArgs(List *s, Term *v){
	   for(int j = 0;j < s->arity();j++){
			if(List *st = dynamic_cast<List *> (s->args(j))){
				return findListArgs(st, v); 
			}else{
				if(s->args(j)->symbol() == v->symbol()){
					return s->args(j);
			}
		}
     }  
     return v;
  }

    //make the small tree
  Node * makeTree() {
    Node * n = op_op.top();
    op_op.pop();
    n->right = op_term.top();
    op_term.pop();
    n->left = op_term.top();
    op_term.pop();
    return n;
  }

  Node * expressionTree(){
    return tree;
  }
  
  //interpreter pattern
  void buildExpression(){
    disjunctionMatch();
    restDisjunctionMatch();
    if (createTerm() != nullptr || _currentToken != '.')
      throw string("Missing token '.'");
  }

  void restDisjunctionMatch() {
    if (_scanner.currentChar() == ';') {
      createTerm();
	  if(_scanner.currentChar() == '.'){
		 throw string("Unexpected ';' before '.'");
	  }
      disjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new DisjExp(left, right));
      restDisjunctionMatch();
    }
  }

  void disjunctionMatch() {
    conjunctionMatch();
    restConjunctionMatch();
  }

  void restConjunctionMatch() {
    if (_scanner.currentChar() == ',') {
	  _sign = 1;
      createTerm();
	  if(_scanner.currentChar() == '.'){
		 throw string("Unexpected ',' before '.'");
	  }
      conjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new ConjExp(left, right));
      restConjunctionMatch();
    }
  }

  void conjunctionMatch() {
    Term * left = createTerm();
	_terms.push_back(left);	
	_findTerms.push_back(left);
	if(_scanner.currentChar() == ';'){
		throw string("Unexpected ';' before '.'");
	}else if(_scanner.currentChar() == '.'){
		throw string("X does never get assignment");
	}else if (_scanner.currentChar() == ','){
		throw string("Unexpected ',' before '.'");
	}else if (createTerm() == nullptr && _currentToken == '=') {
      Term * right = createTerm();
	  _terms.push_back(right);	
	  _findTerms.push_back(right);
      _expStack.push(new MatchExp(left, right));
    }
  }

  Exp* getExpressionTree(){
    return _expStack.top();
  }
  
private:
 // FRIEND_TEST(ParserTest, createArgs);
  //FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  //FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  //FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',' ) {
        _terms.push_back(createTerm());
      }
    }
  }

  vector<Term *> _terms;
  vector<Term *> _findTerms; //to issue the repeat variable
  Scanner _scanner;
  int _currentToken;
  int _sign = 0; //to issue  the COMMA or SEMICOLON
  Node * tree;
  stack<Node*> op_term;
  stack<Node*> op_op;
  stack<Exp*> _expStack;

};
#endif
