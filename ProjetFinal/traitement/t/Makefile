all : exect

main.o : main.c main.h
	@gcc -c main.c
avl.o : avl.c avl.h
	@gcc -c avl.c
exect : main.o avl.o
	@gcc main.o avl.o -o exect

clean : 
	@rm main.o avl.o