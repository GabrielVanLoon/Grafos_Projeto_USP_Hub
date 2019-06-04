build:
	gcc -c *.c
	rm *.o
all:
	gcc -o exec usuarios.c main.c
run:
	./exec