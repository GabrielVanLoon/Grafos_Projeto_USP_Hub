#include "relacionamento.h"

const char arquivoDados[] = "binarios/relacionamento.bin";
const int tamanhoRelacionamento = 800;

int rel_novaUsuario(){
	FILE* fp = fopen (arquivoDados, "wb");
	if (fp == NULL) return 1;
	fseek(fp, 0, SEEK_END);
	int i;
	for (i = 0; i < 100; i++){
		fwrite("0", sizeof(int), 1, fp);
		fwrite("0", sizeof(int), 1, fp);
	}
	fclose(fp);
	return 0;
}

int rel_escreveRelacionamento(Relacionamento* rel, int id){
	FILE* fp = fopen (arquivoDados, "wb");
	if (fp == NULL) return 1;
	fseek(fp, (id-1)*tamanhoRelacionamento, SEEK_SET);
	for (i = 0; i < 100; i++){
		fwrite("0", sizeof(int), 1, fp);
		fwrite("0", sizeof(int), 1, fp);
	}
	fclose(fp);
}