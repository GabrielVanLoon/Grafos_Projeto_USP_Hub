build:
	gcc -c *.c
	rm *.o

all:
	gcc -o exec usuarios.c dados.c relacionamento.c solicitacoes.c telas.c main.c

run:
	./exec

usuarios:
	hexdump -Cv binarios/usuarios.bin

dados:
	hexdump -Cv binarios/dados.bin

relacionamento:
	hexdump -Cv binarios/relacionamento.bin

solicitacoes:
	hexdump -Cv binarios/solicitacoes.bin