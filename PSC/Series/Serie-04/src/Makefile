all: test

test: test.o myLib.o DataLoader.o ProgramCourse.o
	gcc -o test test.o myLib.o DataLoader.o ProgramCourse.o

test.o: test.c myLib.h
	gcc -c -g -Wall -pedantic -o test.o test.c
	
myLib.o: myLib.c myLib.h
	gcc -c -g -Wall -pedantic -o myLib.o myLib.c
	
DataLoader.o: DataLoader.c DataLoader.h
	gcc -c -g -Wall -pedantic -o DataLoader.o DataLoader.c

ProgramCourse.o: ProgramCourse.c ProgramCourse.h
	gcc -c -g -Wall -pedantic -o ProgramCourse.o ProgramCourse.c

exam.o: Exam.c Exam.h
	gcc -c -g -Wall -pedantic -o Exam.o Exam.c
	

clean:
	rm -f test *.so *.o *~
	
