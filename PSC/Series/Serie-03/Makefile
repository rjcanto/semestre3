header: header.o imageFormat.o
		gcc -o header header.o imageFormat.o

header.o: header.c imageFormat.h myLib.h
		gcc -Wall -pedantic -c header.c 
		
imageFormat.o: imageFormat.c imageFormat.h myLib.h
		gcc -Wall -pedantic -c imageFormat.c 
 
