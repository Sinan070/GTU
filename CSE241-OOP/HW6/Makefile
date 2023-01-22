FLAGS = -std=c++11
CC = g++

target: HW6


main: main.cpp GtuVector.h StlGlobalFunctions.h GtuSet.h GtuArray.h
	$(CC) -c main.cpp  $(FLAGS)

HW6: main.o
	$(CC)   $(FLAGS) main.o -o hw6

clean :
	rm *.o hw6