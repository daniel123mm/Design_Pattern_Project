#hw2 makefile
INC_DIR = include

all: hw2

hw2: main.o 
ifeq (${OS}, Windows_NT)
	g++ -o hw2 main.o -lgtest
else
	g++ -o hw2 main.o -lgtest -lpthread
endif
	
main.o: main.cpp  utTerm.h $(INC_DIR)/Number.h $(INC_DIR)/Term.h $(INC_DIR)/Atom.h
	g++ -std=gnu++0x -c main.cpp
clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif