all: execs

execs : main.o avl.o
	@gcc -o execs main.o avl.o

main.o : main.c main.h
	@gcc -c main.c
avl.o : avl.c main.h avl.h
	@gcc -c avl.c
 
clean :
	@rm execs main.o avl.o
