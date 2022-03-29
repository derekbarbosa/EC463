CPP=g++
CFLAGS=-std=c++14 -O1 -fsanitize=address -Wall -pthread -static-libstdc++ 

game: core_functions.cpp game.cpp
	$(CPP) $(CFLAGS) -o game game.cpp core_functions.cpp

clean:
	rm -r game