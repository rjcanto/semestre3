all: ptest PointImpl.so

ptest: ptest.o
	gcc -o ptest ptest.o -ldl

PointImpl.so: PointImpl.o
	gcc -shared -o PointImpl.so PointImpl.o -lm

ptest.o: ptest.c IPoint.h
	gcc -c -Wall -pedantic -o ptest.o ptest.c

PointImpl.o: PointImpl.c IPoint.h
	gcc -c -Wall -pedantic -fPIC -o PointImpl.o PointImpl.c

clean:
	rm -f ptest *.so *.o *~

