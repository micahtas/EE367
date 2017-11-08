all: server367 client367

server367: server367.o
	gcc server367.o -o server367

client367: client367.o
	gcc client367.o -o client367

server367.o: server367.c
	gcc -c server367.c

client367.o: client367.c
	gcc -c client367.c

pipe: pipe.o
	gcc pipe.o -o pipe367

pipe.o: pipe.c
	gcc pipe.c

clean:
	rm -f *.o

real_clean: clean
	rm -f server367
	rm -f client367
	rm -f pipe
