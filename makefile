#hw2 makefile
INC_DIR = include

all: hw4

hw4: main.o 
ifeq (${OS}, Windows_NT)
	g++ -Wall -o hw4 main.o -lgtest
else
	g++ -Wall -o hw4 main.o -lgtest -lpthread
endif
	
main.o: main.cpp  utList.h term.h atom.h struct.h variable.h number.h 
	g++ -Wall -std=gnu++0x -c main.cpp 
clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw4
endif
