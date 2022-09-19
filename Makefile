CC = g++
CXXFLAGS = -std=c++11 -static
PROGRAM = nQueens

test: test.cpp
	${CC} ${CXXFLAGS} test.cpp -o test.o

main: main.cpp
	${CC} ${CXXFLAGS} main.cpp -o main.o

clean:
	rm *.o
	rm *.exe