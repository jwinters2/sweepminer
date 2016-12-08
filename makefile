CC=g++
CFLAGS=-Wall
LDFLAGS=-lncurses

all: sweepminer

sweepminer: main.cpp board.o cell.o
	$(CC) main.cpp board.o cell.o -o sweepminer $(LDFLAGS)

board.o: board.cpp
	$(CC) $(CFLAGS) -c board.cpp $(LDFLAGS)

cell.o: cell.cpp
	$(CC) $(CFLAGS) -c cell.cpp $(LDFLAGS)

clean:
	rm *.o sweepminer
