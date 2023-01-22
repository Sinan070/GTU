FLAGS = -std=c++11
CC = g++

target: hw3

game: game.cpp game.h
	$(CC) -c game.cpp  $(FLAGS) 
	
main: main.cpp game.h
	$(CC) -c main.cpp  $(FLAGS)

hw3: game.o main.o
	$(CC)   $(FLAGS) main.o game.o -o hw3  

clean :
	rm *.o hw3