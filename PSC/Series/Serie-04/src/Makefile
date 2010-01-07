all: test

test: test.o myLib.o
	gcc -o test test.o myLib.o

test.o: test.c myLib.h
	gcc -c -Wall -pedantic -o test.o test.c
	
myLib.o: myLib.c myLib.h
	gcc -c -Wall -pedantic -o myLib.o myLib.c

clean:
	rm -f test *.so *.o *~
	
