all : exect

main.o : main.c main.h
	@gcc -c main.c main.h
avl.o : avl.c avl.h
	@gcc -c avl.c avl.h
exect : main.o avl.o
	@gcc main.o avl.o -o exect

clean : 
	@rm main.o avl.o