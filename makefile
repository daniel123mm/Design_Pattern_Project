#makefile
INC_DIR = include

all: hw7

hw7: main.o term.o list.o struct.o
ifeq (${OS}, Windows_NT)
	g++ -Wall -o hw7 main.o term.o list.o struct.o -lgtest
else
	g++ -Wall -o hw7 main.o term.o list.o struct.o -lgtest -lpthread
endif
	
main.o: main.cpp  utIterator.h term.h atom.h struct.h variable.h number.h scanner.h parser.h iterator.h list.h
	g++ -Wall -std=gnu++0x -c main.cpp
	
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
	rm -f *.o hw7
endif
