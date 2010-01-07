makeAll: header zpipe ppmZip

ppmZip: z-LibraryPNG.o filtersPNG.o
		gcc -Iinclude -o ppmZip z-LibraryPNG.o libz.a imageFormat.o filtersPNG.o
		
z-LibraryPNG.o: z-LibraryPNG.c z-LibraryPNG.h myLib.h zlib.h 
		gcc -g -Wall -pedantic -Iinclude -c z-LibraryPNG.c

header: header.o imageFormat.o
		gcc -Iinclude -o header header.o imageFormat.o

header.o: header.c imageFormat.h myLib.h
		gcc -g -Wall -pedantic -Iinclude -c header.c 
		
imageFormat.o: imageFormat.c imageFormat.h myLib.h
		gcc -g -Wall -pedantic -Iinclude -c imageFormat.c 


zpipe: z-Library.o
		gcc -Iinclude -o zpipe z-Library.o libz.a
		
z-Library.o: z-Library.c z-Library.h myLib.h zlib.h
		gcc -g -Wall -pedantic -Iinclude -c z-Library.c

filtersPNG.o: filtersPNG.c myLib.h imageFormat.h
	gcc -g -Wall -pedantic -Iinclude -c filtersPNG.c


