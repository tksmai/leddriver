CC=g++

main:main.cpp number.cpp number.h strprocess.cpp
	$(CC) -g --std=c++11 main.cpp -o main -lwiringPi
	./main