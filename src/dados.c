#include "dados.h"

const char arquivoDados[] = "binarios/dados.bin";
const int tamanhoDados = 71;

int dad_escreverDados (Dados* dados){
	FILE* fp = fopen(arquivoDados, "rb+");
	if (fp == NULL)
		fp = fopen(arquivoDados, "wb+");
	fseek(fp, 0, SEEK_END);
	fwrite(&dados->id, sizeof(int), 1, fp);
	fwrite(dados->nome, sizeof(char), 60, fp);
	fwrite(&dados->idade, sizeof(int), 1, fp);
	fwrite(&dados->genero, sizeof(char), 1, fp);
	fwrite(&dados->orientacao, sizeof(char), 1, fp);
	fwrite(&dados->namorando, sizeof(char), 1, fp);
	fclose(fp);
	return 0;
}

int dad_buscaDados (Dados* dados, int id){
	FILE* fp = fopen(arquivoDados, "rb");
	if (fp == NULL) return 1;
	fseek(fp, (id-1)*tamanhoDados, SEEK_SET);
	fread(&dados->id, sizeof(int), 1, fp);
	fread(dados->nome, sizeof(char), 60, fp);
	fread(&dados->idade, sizeof(int), 1, fp);
	fread(&dados->genero, sizeof(char), 1, fp);
	fread(&dados->orientacao, sizeof(char), 1, fp);
	fread(&dados->namorando, sizeof(char), 1, fp);
	fclose(fp);
	return 0;
}

// Retorna se A se interessa por B e vice-versa
	int dad_possuiInteresse(Dados* a, Dados* b){
		switch (a->orientacao){
			case 'e': // Hetero
				if(a->genero != b->genero && b->orientacao != 'o')
					return 1;
				else 
					return 0;
				break;

			case 'o': // Homossexual
				if(a->genero == b->genero && b->orientacao != 'e')
					return 1;
				else 
					return 0;
				break;

			case 'b': // Bissexual
				if(a->genero == b->genero && b->orientacao != 'e')
					return 1;
				else if(a->genero != b->genero && b->orientacao != 'o')
					return 1;
				else
					return 0;
				break;

		}
	
	}
