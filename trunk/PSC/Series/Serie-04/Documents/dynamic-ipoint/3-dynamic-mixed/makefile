all: ptest PointImpl.so PolarPoint.so

ptest: ptest.o
	gcc -o ptest ptest.o -ldl

PointImpl.so: PointImpl.o
	gcc -shared -o PointImpl.so PointImpl.o -lm

PolarPoint.so: PolarPoint.o
	gcc -shared -o PolarPoint.so PolarPoint.o -lm

ptest.o: ptest.c IPoint.h
	gcc -c -Wall -pedantic -o ptest.o ptest.c

PointImpl.o: PointImpl.c IPoint.h
	gcc -c -Wall -pedantic -fPIC -o PointImpl.o PointImpl.c

PolarPoint.o: PolarPoint.c IPoint.h
	gcc -c -Wall -pedantic -fPIC -o PolarPoint.o PolarPoint.c

clean:
	rm -f ptest *.so *.o *~

