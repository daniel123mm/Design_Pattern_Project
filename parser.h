#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
using std::string;
using std::vector;

#include "atom.h"
#include "number.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner){}
  
  Term* createTerm(){
    int token = _scanner.nextToken();
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
        Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
        if((token = _scanner.nextToken()) == '(') {
          vector<Term*> terms = getArgs();
          if(_currentToken == ')')
            return new Struct(*atom, terms);
        }
        else if(_currentToken == '('){
			_scanner.fallback(1);
            return new Struct(*atom);
        }else if(_currentToken == ']'){
            throw string("unexpected token");
        }else
            _scanner.fallback(1);
        
        return atom;
    }else if(token == '['){
		vector<Term*> terms = getArgs();
		if(_currentToken == ']'){
			return new List(terms);
        }else if(_currentToken == ')'){
            throw string("unexpected token");
        }else{
            _scanner.fallback(1);
			return new List();
		}
	}
    return NULL;
  }

  vector<Term*> getArgs()
  {
    Term* term = createTerm();
    vector<Term*> args;
    if(term)
      args.push_back(term);
    else
      _scanner.fallback(1);
    while((_currentToken = _scanner.nextToken()) == ',') {
      args.push_back(createTerm());
    }
    return args;
  }


private:
  Scanner _scanner;
  int _currentToken;
};
#endif
