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
#include "utParser.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
		Term *variable = new Variable(symtable[_scanner.tokenValue()].first);
		if(sign == 1){
			if(_findTerms.size() < 3){
				for(int i = (int)_findTerms.size() - 1;i > (int)_findTerms.size() - 3;i--){
					Struct *st = dynamic_cast<Struct *> (_findTerms[i]);
					if(st){
						variable = findStructArgs(st,variable);
					}else{
						if(_findTerms[i]->symbol() == variable->symbol()){
							variable = _findTerms[i];
						}
					}
				}
			}else{
				for(int i = (int)_findTerms.size() - 1;i > (int)_findTerms.size() - 4;i--){
					Struct *st = dynamic_cast<Struct *> (_findTerms[i]);
					if(st){
						variable = findStructArgs(st,variable);
					}else{
						if(_findTerms[i]->symbol() == variable->symbol()){
							variable = _findTerms[i];
						}
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
      else
        return atom;
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
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

void matchings(){ 
    while(_scanner.currentChar() != '.') {
     Term * term = createTerm();
     if ( term != nullptr ){
		 /*
		if(sign == 1){
			for(int i = (int)_terms.size() - 1;i > (int)_terms.size() - 3;i--){
				Struct *st = dynamic_cast<Struct *> (_terms[i]);
				if(st){
					//findStructArgs(st,term);
					for(int j = 0;j < st->arity();j++){
						if(st->args(j)->symbol() == term->symbol()){
							term = st->args(j);
							break;
						}
					}
					
				}else{
					if(_terms[i]->symbol() == term->symbol()){
						term = _terms[i];
					}
				}
			}
		}
		*/
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
		sign = 1;
        Node * n = new Node(COMMA);
        Node * temp = makeTree();
		op_term.push(temp);
		op_op.push(n);
     }
	 if( _scanner.currentChar() == ';' ) {
		sign = 2;
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
	  
  }

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

private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

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
  vector<Term *> _findTerms;
  Scanner _scanner;
  int _currentToken;
  int sign = 0;
  Node * tree;
  stack<Node*> op_term;
  stack<Node*> op_op;

};
#endif
