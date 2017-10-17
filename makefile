#hw2 makefile
INC_DIR = include

all: hw2

hw2: main.o 
ifeq (${OS}, Windows_NT)
	g++ -Wall -o hw2 main.o -lgtest
else
	g++ -Wall -o hw2 main.o -lgtest -lpthread
endif
	
main.o: main.cpp  utStruct.h utVariable.h term.h atom.h struct.h variable.h number.h
	g++ -Wall -std=gnu++0x -c main.cpp 
clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif
