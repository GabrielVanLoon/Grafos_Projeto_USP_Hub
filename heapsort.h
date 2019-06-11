#ifndef HEAPSORT_H
#define HEAPSORT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relacionamento.h"

int maiorId(Relacionamento* heap, int indexA, int indexB);


int maiorPontos(Relacionamento* heap, int indexA, int indexB);

void trocar(Relacionamento* heap, int indexA, int indexB);

void construir_heap(Relacionamento* heap, int (*ordenar)(Relacionamento*, int, int), int n, int i);

/* Ordenar Relacionamento pela funcao (ordenar*), a qual pode ser maiorId ou maiorPontos */
void heapSort(Relacionamento* heap, int (*ordenar)(Relacionamento*, int, int));

/* Exibe vetor */
void print_heap(Relacionamento* heap);

#endif