cc = gcc
CFLAGS = -Wall  -pedantic -erros
SRCS = main.c part1.c part2.c my_utils.c
OBJS = $(SRCS:.c=.o)

all: program

program: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o appendMeMore

clean:
	rm -f program $(OBJS) f1 f2 test.txt test1.txt appendMeMore