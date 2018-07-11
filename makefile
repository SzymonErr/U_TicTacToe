CC = g++

CFLAGS = -g -Wall -std=c++11

all: Tic-tac-toe

clean:
		rm  -f *.o Tic-tac-toe
		
Tic-tac-toe: main.o Board.o Opponent.o
		$(CC) $(CFLAGS) -o Tic-tac-toe main.o Board.o Opponent.o
		
main.o: main.cpp Board.h Opponent.h
		$(CC) $(CFLAGS) -c main.cpp
		
Board.o: Board.cpp
		$(CC) $(CFLAGS) -c Board.cpp

Opponent.o: Opponent.cpp
		$(CC) $(CFLAGS) -c Opponent.cpp
				