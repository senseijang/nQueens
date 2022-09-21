CC = g++
CXXFLAGS = -std=c++11 -static -g
PROGRAM = nQueens

run: nQueens.o
	./nQueens.o

nQueens.o: main.cpp
	${CC} ${CXXFLAGS} main.cpp -o nQueens.o

clean:
	rm *.o
	rm *.exe