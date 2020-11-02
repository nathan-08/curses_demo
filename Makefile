main: main.o
	g++ -std=c++17 -o main main.o -lncurses -pthread

main.o: main.cpp curses.h
	g++ -std=c++17 -c main.cpp
