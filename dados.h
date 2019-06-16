#ifndef DADOS_H
	#define DADOS_H
	#include <stdlib.h>
	#include <stdio.h>

	/**
	 * Struct que salva os dados com as informações pessoais do usuário
	 */
	typedef struct dados{
		int 	id;
		char 	nome[60];
		int 	idade;
		char 	genero;
		char 	orientacao;
		char 	namorando;
	} Dados;

	/*
		Escreve os dados no final do arquivo binario.
	*/
	int dad_escreverDados (Dados* dados);

	/* 
		Busca os dados de um usuario baseado em seu id
	*/
	int dad_buscaDados (Dados* dados, int id);

	/**
	 *  Retorna se A se interessa por B e vice-versa
	 */ 
	int dad_possuiInteresse(Dados* a, Dados* b);

#endif