CXX = g++
CFLAGS = -std=c++17 -Wall

main: main.o networking.o
	$(CXX) $(CFLAGS) -o main main.o networking.o -lncurses -pthread -lcurl

main.o: main.cpp curses.h
	$(CXX) $(CFLAGS) -c main.cpp -I/Users/nathanklundt/code/cpp/rapidjson/include

networking.o: networking.cpp networking.h
	$(CXX) $(CFLAGS) -c networking.cpp
