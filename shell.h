#ifndef SHELL_H
#define SHELL_H

#include "parser.h"
#include "scanner.h"
#include <string>
#include <iostream>
#include <stdio.h>


class Shell {
	public :
	void start(){
		char input;
		string buffer = " ";
		std::cout << "?-";
		do{
			input = getchar();
			if (input != '\n'){
				buffer += input;
			}
			if (input == '\n' || input == '\r'){
				if (buffer == " halt."){
					break;
				}else if (buffer[buffer.size() - 1] == ';' || buffer[buffer.size() - 1] == ','){
					std::cout << "|";
				}else if (buffer[buffer.size() - 1] == '.' || buffer.size() > 1){
					//cout << "test\n";
					Scanner s(buffer);
					Parser p(s);
					try{
						p.buildExpression();
						string result;
						if (p.getExpressionTree()->evaluate()){
							result = p.getExpressionTree()->getEvaluateResult() + '.';
						}else{
							result = "false.";
						}
						std::cout << result << "\n";
						buffer = " ";
						std::cout << "?-";
					}catch (std::string & msg) {
						std::cout << msg << "\n";
						buffer = " ";
						std::cout << "?-";
					}
				}else{
					std::cout << "?-";
				}
			}
		} while (true);
	}
	
};

#endif