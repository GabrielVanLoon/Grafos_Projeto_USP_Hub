#include "heapsort.h"

int maiorId(Relacionamento* heap, int indexA, int indexB) {
    return (heap->amizades[indexA].id > heap->amizades[indexB].id)? indexA : indexB;
}

int maiorPontos(Relacionamento* heap, int indexA, int indexB) {
    return (heap->amizades[indexA].pontos > heap->amizades[indexB].pontos)? indexA : indexB;
}

void trocar(Relacionamento* heap, int indexA, int indexB) {
    NoRelacionamento aux;
    aux.id = (heap->amizades[indexA].id);
    aux.pontos = (heap->amizades[indexA].pontos);
    (heap->amizades[indexA].id) = (heap->amizades[indexB].id);
    (heap->amizades[indexA].pontos) = (heap->amizades[indexB].pontos);
    (heap->amizades[indexB].id) = aux.id;
    (heap->amizades[indexB].pontos) = aux.pontos;
    return;
}

void construir_heap(Relacionamento* heap, int(*ordenar)(Relacionamento*, int, int), int n, int i) {
    int maior = i;
    int esq = (2*i) + 1;
    int dir = (2*i) + 2;

    if(esq < n && ordenar(heap, esq, maior) > 0) maior = esq;
    
    if(dir < n && ordenar(heap, dir, maior) > 0) maior = dir;
     
    if(maior != i) {
        trocar(heap, i, maior); 
        construir_heap(heap, ordenar, n, maior); 
    }
}

void heapSort(Relacionamento* heap, int(*ordenar)(Relacionamento*, int, int)) 
{ 
    const int n =  heap->nroRelacionamento;

    // Construir heap 
    for (int i = ( n / 2 ) - 1; i >= 0; --i) 
        construir_heap(heap, ordenar, n, i); 
  
    // Montar heap sem o maior elemento
    for (int i= n-1; i >=0 ; --i) { 
        trocar(heap, 0, i); 
  
        // reconstruir heap
        construir_heap(heap, ordenar, i, 0); 
    } 
} 

void print_heap(Relacionamento* heap) {
    for(int i = 0; i < heap->nroRelacionamento; ++i) {
        printf("id: %d pontos: %d\n", heap->amizades[i].id, heap->amizades[i].pontos);
    }
}