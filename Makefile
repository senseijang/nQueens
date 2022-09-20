CC = g++
CXXFLAGS = -std=c++11 -static
PROGRAM = nQueens

main: main.cpp
	${CC} ${CXXFLAGS} main.cpp -o a.out

clean:
	rm *.o
	rm *.exe