CPP=g++
CFLAGS=-std=c++14 -g -O1 -fsanitize=address -Wall -pthread

game: core_functions.cpp game.cpp
	$(CPP) $(CFLAGS) -o game game.cpp core_functions.cpp

clean:
	rm game