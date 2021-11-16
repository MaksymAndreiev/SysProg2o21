lab5: lab5.exe

lab5.exe: lab5.o
	gcc lab5.o -o lab5.exe
	
lab5.o: lab5.c
	gcc -c lab5.c -o lab5.o
