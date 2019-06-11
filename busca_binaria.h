#ifndef BUSCA_BINARIA_H
#define BUSCA_BINARIA_H
#include "relacionamento.h"

/* Retur 1 if heap->amizados em indexA eh maior que B, se menor -1 e se igual 0 */
int maiorId(Relacionamento* heap, int indexA, int indexB);

/* Return 1 se indexA pontos for maior que indexB */ 
int maiorPontos(Relacionamento* heap, int indexA, int indexB);

/* Busca binaria no vetor amizades de relacionamento */
int busca_binaria_indice(Relacionamento* relacionamento, int(*ordenar)(Relacionamento*, int, int),  int valor);

#endif