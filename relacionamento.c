#include "relacionamento.h"
#include "heapsort.h"
#include "busca_binaria.h"

const char arquivoDados[] = "binarios/relacionamento.bin";
const int tamanhoRelacionamento = 804;

int rel_novoUsuario(){
	FILE* fp = fopen (arquivoDados, "rb+");
	if (fp == NULL)
		fp = fopen (arquivoDados, "wb+");
	fseek(fp, 0, SEEK_END);
	fwrite("0", sizeof(int), 1, fp); //Numero de relacionamentos
	for (int i = 0; i < 100; i++){
		fwrite("0", sizeof(int), 1, fp); //id
		fwrite("0", sizeof(int), 1, fp); //pontos
	}
	fclose(fp);
	return 0;
}

int rel_escreverRelacionamento(Relacionamento* rel, int id){
	FILE* fp = fopen (arquivoDados, "rb+");
	if (fp == NULL) return 1;
	fseek(fp, (id-1)*tamanhoRelacionamento, SEEK_SET);
	fwrite(&rel->nroRelacionamento, sizeof(int), 1, fp);
	for (int i = 0; i < rel->nroRelacionamento; i++){
		fwrite(&rel->amizades[i].id, sizeof(int), 1, fp);
		fwrite(&rel->amizades[i].pontos, sizeof(int), 1, fp);
	}
	fclose(fp);
	return 0;
}

int rel_lerRelacionamentos(Relacionamento* rel, int id){
	FILE* fp = fopen (arquivoDados, "rb");
	if (fp == NULL) return 1;
	fseek(fp, (id-1)*tamanhoRelacionamento, SEEK_SET);
	fread(&rel->nroRelacionamento, sizeof(int), 1, fp);
	for (int i = 0; i < rel->nroRelacionamento; i++){
		fread(&rel->amizades[i].id, sizeof(int), 1, fp);
		fread(&rel->amizades[i].pontos, sizeof(int), 1, fp);
	}
	fclose(fp);
	return 0;
}

/**
*
*@return 1: Erro de abertura de arquivo
*@return 2: Numero máximo de amigos excedido
**/
int rel_addAmizade (Relacionamento* rel, int id, int idAmigo, int pontosAmigo){
	if(rel_lerRelacionamentos(rel, id)) return 1;
	if(rel->nroRelacionamento >= 99) return 2;
	rel->amizades[rel->nroRelacionamento].id = idAmigo;
	rel->amizades[rel->nroRelacionamento].pontos = pontosAmigo;
	rel->nroRelacionamento++;
	
	//heapsort pelos pontos
	heapsort(rel, maiorPontos);
	if(rel_escreverRelacionamento(rel, id)) return 1;
	return 0;
}

/**
*
*@return 1: Erro de abertura de arquivo
*@return 2: Nao ha amigos
**/
int rel_removeAmizade (Relacionamento* rel, int id, int idAmigo){
	if(rel_lerRelacionamentos(rel, id)) return 1;
	if(rel->nroRelacionamento <= 0) return 2;
	int pos;
	//heapsort pelo id
	heapsort(rel, maiorId);
	if(pos = busca_binaria(rel, maiorId), pos != -1) //remove
	{
		rel->amizades[pos].id = 0;
		rel->amizades[pos].pontos = 0;
	}
	heapsort(rel, maiorPontos);
	rel->nroRelacionamento--;
	if(rel_escreverRelacionamento(rel, id)) return 1;
	return 0;
}