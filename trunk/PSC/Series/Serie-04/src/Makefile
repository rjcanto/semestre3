all: Examvalidator MinDistValidator.so NoRepValidator.so MinDistDependentValidator.so

ExamValidator: ExamValidator.o myLib.o DataLoader.o ProgramCourse.o Exam.o
	gcc -o ExamValidator ExamValidator.o myLib.o DataLoader.o ProgramCourse.o Exam.o -ldl

ExamValidator.o: ExamValidator.c ExamValidator.h
	gcc -c -g -Wall -pedantic -o ExamValidator.o ExamValidator.c
	
myLib.o: myLib.c myLib.h
	gcc -c -g -Wall -pedantic -o myLib.o myLib.c
	
DataLoader.o: DataLoader.c DataLoader.h
	gcc -c -g -Wall -pedantic -o DataLoader.o DataLoader.c

ProgramCourse.o: ProgramCourse.c ProgramCourse.h
	gcc -c -g -Wall -pedantic -o ProgramCourse.o ProgramCourse.c

Exam.o: Exam.c Exam.h
	gcc -c -g -Wall -pedantic -o Exam.o Exam.c
	
MinDistValidator.so: MinDistValidator.o
	gcc -shared -g -Wall -o MinDistValidator.so MinDistValidator.o -lm

NoRepValidator.so: NoRepValidator.o
	gcc -shared -g -Wall -o NoRepValidator.so NoRepValidator.o -lm
	
MinDistDependentValidator.so: MinDistDependentValidator.o
	gcc -shared -g -Wall -o MinDistDependentValidator.so MinDistDependentValidator.o -lm
	
MinDistValidator.o: MinDistValidator.c MinDistValidator.h
	gcc -c -g -Wall -pedantic -fPIC -o MinDistValidator.o MinDistValidator.c

NoRepValidator.o: NoRepValidator.c NoRepValidator.h
	gcc -c -g -Wall -pedantic -fPIC -o NoRepValidator.o NoRepValidator.c

MinDistDependentValidator.o: MinDistDependentValidator.c MinDistDependentValidator.h
	gcc -c -g -Wall -pedantic -fPIC -o MinDistDependentValidator.o MinDistDependentValidator.c
	
clean:
	rm -f ExamValidator *.so *.o *~
	
