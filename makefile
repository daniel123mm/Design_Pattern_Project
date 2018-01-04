#makefile
INC_DIR = include

all: hw8 shell

hw8: main.o term.o list.o struct.o
ifeq (${OS}, Windows_NT)
	g++ -Wall -o hw8 main.o term.o list.o struct.o -lgtest
else
	g++ -Wall -o hw8 main.o term.o list.o struct.o -lgtest -lpthread
endif

shell: mainShell.o term.o list.o struct.o
ifeq (${OS}, Windows_NT)
	g++ -Wall -o shell mainShell.o term.o list.o struct.o -lgtest
else
	g++ -Wall -o shell mainShell.o term.o list.o struct.o -lgtest -lpthread
endif
	
main.o: main.cpp  expression.h exception.h exp.h term.h atom.h struct.h variable.h number.h scanner.h parser.h iterator.h list.h
	g++ -Wall -std=gnu++0x -c main.cpp
	
mainShell.o: mainShell.cpp shell.h exp.h term.h atom.h struct.h variable.h number.h scanner.h parser.h utParser.h iterator.h list.h
	g++ -Wall -std=gnu++0x -c mainShell.cpp
	
term.o: term.cpp term.h 
	g++ -std=c++11 -c term.cpp

list.o: list.cpp list.h
	g++ -std=c++11 -c list.cpp

struct.o: struct.cpp struct.h
	g++ -std=c++11 -c struct.cpp	
	
clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw8 shell
endif
