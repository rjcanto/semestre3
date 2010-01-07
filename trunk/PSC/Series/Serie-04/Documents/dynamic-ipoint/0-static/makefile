ptest: ptest.o PointImpl.o
	gcc -o ptest ptest.o PointImpl.o -lm

ptest.o: ptest.c IPoint.h
	gcc -c -Wall -pedantic -o ptest.o ptest.c

PointImpl.o: PointImpl.c IPoint.h
	gcc -c -Wall -pedantic -o PointImpl.o PointImpl.c

clean:
	rm -f ptest *.o *~

