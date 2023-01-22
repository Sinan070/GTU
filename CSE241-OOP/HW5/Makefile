FLAGS = -std=c++11
CC = g++

target: HW5

lib: hw5Lib.cpp Klotski.h PegSolitaire.h Puzzle.h
	$(CC) -c hw5lib.cpp  $(FLAGS) 
	
main: hw5Main.cpp Klotski.h PegSolitaire.h Puzzle.h
	$(CC) -c hw5Main.cpp  $(FLAGS)

HW5: hw5Lib.o hw5Main.o
	$(CC)   $(FLAGS) hw5Main.o hw5Lib.o -o HW5  

clean :
	rm *.o HW5