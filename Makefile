
test: list.o test.o
	gcc -o test test.o list.o

lista.o:list.c list.h
	gcc -c list.c
	
	
test.o:test.c list.h
	gcc -c test.c
	
clean:
	rm list.o test.o test
