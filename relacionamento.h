#ifndef RELACIONAMENTO_H
#define RELACIONAAMENTO_H

typedef struct no {
	int		id;
	int		pontos; //pontos de afinidade.
} NoRelacionamento;

typedef struct relacionamento {
	NoRelacionamento 	amizades[100];
	int 				nroRelacionamento;
} Relacionamento;

int rel_novaUsuario();

int rel_escreveRelacionamento(Relacionamento* rel);

int rel_lerRelacionamento(Relacionamento* rel);

int rel_atualizaRelacionamento(Relacionamento* rel);

#endif