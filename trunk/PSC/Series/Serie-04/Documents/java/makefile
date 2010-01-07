
all : ExamValidator.class validators
validators : MinDistValidator.class NoRepValidator.class SameSemValidator.class


%.class : %.java
	javac $<
	
	
clean :
	rm *.class
