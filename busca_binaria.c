#include "busca_binaria.h"
#define SIZE_BUF 200

int maiorId(Relacionamento* heap, int indexA, int indexB) {
    if (heap->amizades[indexA].id > indexB) return 1;
    if (heap->amizades[indexA].id < indexB) return -1;
    return 0;
}

int maiorPontos(Relacionamento* heap, int indexA, int indexB) {
    if (heap->amizades[indexA].pontos > indexB) return 1;
    if (heap->amizades[indexA].pontos < indexB) return -1;
    return 0;
}

int busca_binaria_indice(Relacionamento* relacionamento, int(*ordenar)(Relacionamento*, int, int),  int valor) {
  int inicio = 0, fim, meio;
    fim = relacionamento->nroRelacionamento;
    while(inicio <= fim) {
        meio = (inicio + fim) / 2;
        int u = ordenar(relacionamento, meio, valor);
        if(!u) return meio; 
        else if(u < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

