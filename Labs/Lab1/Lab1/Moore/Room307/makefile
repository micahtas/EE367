CC = gcc
CCFLAGS = -ansi

hello: hello.o hello1.o hello2.o hello3.o
	$(CC) -o hello hello.o hello1.o hello2.o hello3.o

hello.o: hello.h

hello1.o: hello.h

hello2.o: hello.h

hello3.o: hello.h

clean:
	rm -f *.o

real_clean: clean
	rm -f hello
