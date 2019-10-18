CC=gcc

CFLAGS=-std=gnu99 -Wall -Wextra -pedantic


all: proj2


proj3.o: proj2.c
	$(CC) $(CFLAGS) -c proj2.c -o proj2.o


proj3: proj2.o
	$(CC) $(CFLAGS) proj2.o -o proj2 -lpthread


clean-o:
	rm -f *.o


clean-all:
	rm -f proj2
	rm -f *.o
