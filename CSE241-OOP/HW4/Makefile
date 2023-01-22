FLAGS = -std=c++11
CC = g++

target: hw4

lib: hw4_lib.cpp hw4.h
	$(CC) -c hw4_lib.cpp  $(FLAGS) 
	
main: hw4_main.cpp hw4.h
	$(CC) -c hw4_main.cpp  $(FLAGS)

hw4: hw4_lib.o hw4_main.o
	$(CC)   $(FLAGS) hw4_main.o hw4_lib.o -o hw4  

clean :
	rm *.o hw4