#ifndef RELACIONAMENTO_H
#define RELACIONAAMENTO_H
#include <stdio.h>
#include <stdlib.h>

typedef struct no {
	int		id;
	int		pontos; //pontos de afinidade.
} NoRelacionamento;

typedef struct relacionamento {
	NoRelacionamento 	amizades[100];
	int 				nroRelacionamento;
} Relacionamento;

/* Inicializa relacionamentos com pontuacao zero*/
int rel_novoUsuario();

int rel_escreverRelacionamento(Relacionamento* rel, int id);

int rel_lerRelacionamento(Relacionamento* rel);



#endif