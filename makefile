CFLAGS = -Wall
CC = gcc

PROGRAM = myavl

OBJS = main.o libavl.o

DEPS = libavl.h

myavl: $(OBJS)
	$(CC) $(CFLAGS) -o myavl $(OBJS)

main.o: main.c $(DEPS)
	$(CC) $(CFLAGS) -c -o main.o main.c 

libavl.o: libavl.c 
	$(CC) $(CFLAGS) -c -o libavl.o libavl.c

clean:
	rm -f $(OBJS)
	
purge:
	rm -f $(OBJS) $(PROGRAM)