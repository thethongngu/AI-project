all:
	g++ -std=c++14 -O3 -g -Wall -o main Board.h Board.cpp Game.cpp Game.h global.h main.cpp Node.cpp Node.h Player.cpp Player.h
clean:
	rm main
