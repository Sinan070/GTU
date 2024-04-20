GCCPARAMS = -lpthread  -lrt 
objectsSv = server.o circular_queue.o my_utils.o  signal_handler.o 
objectsCl = client.o  my_utils.o signal_handler.o

all :	server client

server : $(objectsSv)
	gcc  $(objectsSv) $(GCCPARAMS) -o server 

client : $(objectsCl)
	gcc  $(objectsCl) $(GCCPARAMS) -o client 

%.o : %.c
	gcc $(GPPPARAMS) -o $@ -c $<

clean :
	rm -rf $(objectsCl) $(objectsSv) server client  