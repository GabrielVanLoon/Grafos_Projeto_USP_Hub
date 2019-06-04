#include "dados.h"

/**
*	
**/
const char arquivoDados[] = "binarios/dados.bin";
const int tamanhoDados = 71;

typedef struct dados{
	int 	id;
	char 	nome[60];
	int 	idade;
	char 	genero;
	char 	orientacao;
	char 	relacionamento;
} Dados;

int dad_escreverDados (Dados* dados){
	FILE* fp = fopen(arquivoDados, "wb");
	if (fp == NULL) return 1;
	fseek(fp, 0, SEEK_END);
	fwrite(&id, sizeof(int), 1, fp);
	fwrite(nome, sizeof(char), 60, fp);
	fwrite(&idade, sizeof(int), 1, fp);
	fwrite(&genero, sizeof(char), 1, fp);
	fwrite(&orientacao, sizeof(char), 1, fp);
	fwrite(&relacionamento, sizeof(char), 1, fp);
	fclose(fp);
	return 0;
}

int dad_buscaDados (Dados* dados, int id){
	FILE* fp = fopen(arquivoDados, "rb");
	if (fp == NULL) return 1;
	fseek(fp, (id-1)*tamanhoDados, SEEK_SET);
	fread(&id, sizeof(int), 1, fp);
	fread(nome, sizeof(char), 60, fp);
	fread(&idade, sizeof(int), 1, fp);
	fread(&genero, sizeof(char), 1, fp);
	fread(&orientacao, sizeof(char), 1, fp);
	fread(&relacionamento, sizeof(char), 1, fp);
	fclose(fp);
	return 0;
}

