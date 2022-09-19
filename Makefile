CC = g++
CXXFLAGS = -std=c++11
PROGRAM = nQueens

build:
	${CC} ${CXXFLAGS} main.cpp -o output.o

clean:
	rm *.o
	rm *.exe