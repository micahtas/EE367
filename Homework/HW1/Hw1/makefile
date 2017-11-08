CC = gcc
CFLAGS = -g -Wall

default = sortednames

sortednames: sortednames.o
	$(CC) $(CFLAGS) -o sortnames sortnames.o

sortednames.o: sortnames.c
	$(CC) $(CFLAGS) -c  sortnames.c

clean:
	rm -f *.o

real_clean:
	rm -f sortednames
