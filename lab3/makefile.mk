lab3: A.exe B.exe

B.exe: B.o
	gcc B.o -o B.exe
	
B.o: B.c
	gcc -c B.c -o B.o

A.exe: A.o
	gcc A.o -o A.exe
	
A.o: A.c
	gcc -c A.c -o A.o
