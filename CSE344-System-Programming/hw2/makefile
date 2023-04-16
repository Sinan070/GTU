GCCPARAMS = -Wall  -pedantic -errors -std=c11

objects = hw2.o signalsHandler.o

%.o : %.cpp
	gcc $(GCCPARAMS) -o $@ $<
hw2 :  $(objects)
	gcc $(GCCPARAMS) -o $@ $(objects)  

compile: hw1

run : hw1
	valgrind ./hw1
clean : 
	rm -rf $(objects) hw2