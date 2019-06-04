build:
	gcc -c *.c
	rm *.o
all:
	gcc -o exec usuarios.c dados.c main.c
run:
	./exec