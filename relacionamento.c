#include "relacionamento.h"

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