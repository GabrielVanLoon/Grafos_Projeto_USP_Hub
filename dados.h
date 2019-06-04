#ifndef DADOS_H
#define DADOS_H
#include <stdlib.h>

/**
*	
**/
const char arquivoDados[] = "binarios/dados.bin";
const int tamanhoDados = 71;

/*
	Modelo para escrever no arquivo. 
*/
typedef struct dados{
	int 	id;
	char 	nome[60];
	int 	idade;
	char 	genero;
	char 	orientacao;
	char 	relacionamento;
} Dados;

/*
	Escreve dados no fim do arquivo
*/
int dad_escreverDados (Dados* dados);

/* 
	Busca os dados de um usuario baseado em seu id
*/
int dad_buscaDados (Dados* dados, int id);

#endif