FLAGS = -std=c++11
CC = g++

target: hw1

lib.o: lib.cpp lib.h
	$(CC) -c lib.cpp  $(FLAGS) 
	
main.o: main.cpp lib.h
	$(CC) -c main.cpp  $(FLAGS)

hw1: lib.o main.o
	$(CC)   $(FLAGS) main.o lib.o -o hw1  

clean :
	rm *.o hw1