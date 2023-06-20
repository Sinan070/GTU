GCCPARAMS = -pthread

objects = hw5.o

%.o: %.c
	gcc $(GCCPARAMS) -o $@ -c $<

run: $(objects)
	gcc  $(GCCPARAMS) $(objects) -o HW5

clean:
	rm -rf $(objects) HW5