#include "solicitacoes.h"

const char arquivoSolicitacoes[] = "binarios/solicitacoes.bin";

void trocar_sol(Solicitacoes* heap, int indexA, int indexB);

void construir_heap_sol(Solicitacoes* heap, int (*ordenar)(Solicitacoes*, int, int), int n, int i);

int sol_novoUsuario() {
	FILE* fp = fopen(arquivoSolicitacoes, "rb+");
	Solicitacoes sol;
	char buff; //caso esteja vazio arquivo 
	if (fp == NULL)
		fp = fopen(arquivoSolicitacoes, "wb+");
	fseek(fp, 0, SEEK_END);
	sol.nroSolicitacoes = 0; //Numero de Solicitacoess
	for (int i = 0; i < 100; i++){
		sol.pendencias[i].id = 0; //id
		sol.pendencias[i].pontos = 0; //pontos
	}
	fwrite(&sol, sizeof(Solicitacoes), 1, fp);
	fclose(fp);
	return 0;
}

int sol_escreverSolicitacoes(Solicitacoes* sol, int id){
	FILE* fp = fopen(arquivoSolicitacoes, "rb+");
	if (fp == NULL) return 1;
	fseek(fp, (id-1)*sizeof(Solicitacoes), SEEK_SET);
	fwrite(sol, sizeof(Solicitacoes), 1, fp);
	fclose(fp);
	return 0;
}

int sol_lerSolicitacoes(Solicitacoes* sol, int id){
	FILE* fp = fopen(arquivoSolicitacoes, "rb");
	if (fp == NULL) return 1;
	fseek(fp, (id-1)*sizeof(Solicitacoes), SEEK_SET);
	fread(sol, sizeof(Solicitacoes), 1, fp);
	fclose(fp);
	return 0;
}

/**
*
*@return 1: Erro de abertura de arquivo
*@return 2: Numero máximo de amigos excedido
**/
int sol_addSolicitacao (Solicitacoes* sol, int id, int idAmigo, int pontosAmigo){
	//if(sol_lerSolicitacoes(sol, id)) return 1;
//	printf("num %d", sol->nroSolicitacoes);
	if(sol->nroSolicitacoes >= 99) return 2;
	sol->pendencias[sol->nroSolicitacoes].id = idAmigo;
	sol->pendencias[sol->nroSolicitacoes].pontos = pontosAmigo;
	
	// heapsort_solicitacoes pelos pontos
	heapsort_solicitacoes(sol, maiorPontosSolicitado);
	if(sol_escreverSolicitacoes(sol, id)) return 1;
	return 0;
}

/**
*@function: Essa funcao exclui um idAmigo do arquivo de solicitacoes
*@Param id: Posicao na lista de solicitacoes para o usuario   
*@return 1: Erro de abertura de arquivo
*@return 2: Nao ha amigos
**/
int sol_recusarSolicitacao (Solicitacoes* sol, int id, int idAmigo){
	if(sol_lerSolicitacoes(sol, id)) return 1;
	if(sol->nroSolicitacoes <= 0) return 2;
	int pos;
	
	heapsort_solicitacoes(sol, maiorIdSolicitado); //heapsort_solicitacoes pelo id

	if(pos = busca_binaria_solicitacoes(sol, maiorIdSolicitado, idAmigo), pos != -1) //remove
	{
		sol->pendencias[pos].id = 0;
		sol->pendencias[pos].pontos = 0;
	}
	heapsort_solicitacoes(sol, maiorPontosSolicitado); // heapsort_solicitacoes pelos pontos
	sol->nroSolicitacoes--;

	if(sol_escreverSolicitacoes(sol, id)) return 1; // reescrita
	return 0;
}

/* heapesort Solicitacoes ===================================================================================== */

int maiorIdSolicitado(Solicitacoes* heap, int indexA, int indexB) {
    return (heap->pendencias[indexA].id > heap->pendencias[indexB].id)? indexA : indexB;
}

int maiorPontosSolicitado(Solicitacoes* heap, int indexA, int indexB) {
    return (heap->pendencias[indexA].pontos > heap->pendencias[indexB].pontos)? indexA : indexB;
}

void trocar_sol(Solicitacoes* heap, int indexA, int indexB) {
    NoSolicitacoes aux;
    aux.id = (heap->pendencias[indexA].id);
    aux.pontos = (heap->pendencias[indexA].pontos);
    (heap->pendencias[indexA].id) = (heap->pendencias[indexB].id);
    (heap->pendencias[indexA].pontos) = (heap->pendencias[indexB].pontos);
    (heap->pendencias[indexB].id) = aux.id;
    (heap->pendencias[indexB].pontos) = aux.pontos;
    return;
}

void construir_heap_sol(Solicitacoes* heap, int(*ordenar)(Solicitacoes*, int, int), int n, int i) {
    int maior = i;
    int esq = (2*i) + 1;
    int dir = (2*i) + 2;

    if(esq < n && ordenar(heap, esq, maior) == esq) maior = esq;
    
    if(dir < n && ordenar(heap, dir, maior) == dir) maior = dir;
     
    if(maior != i) {
        trocar_sol(heap, i, maior); 
        construir_heap_sol(heap, ordenar, n, maior); 
    }
}

void heapsort_solicitacoes(Solicitacoes* heap, int(*ordenar)(Solicitacoes*, int, int)) 
{ 

    const int n =  heap->nroSolicitacoes;

    // Construir heap 
    for (int i = ( n / 2 ) - 1; i >= 0; --i) 
        construir_heap_sol(heap, ordenar, n, i); 
  
    // Montar heap sem o maior elemento
    for (int i= n-1; i >=0 ; --i) { 
        trocar_sol(heap, 0, i); 
  
        // reconstruir heap
        construir_heap_sol(heap, ordenar, i, 0); 
    } 
} 

void print_heap_solicitacoes(Solicitacoes* heap) {
    for(int i = 0; i < heap->nroSolicitacoes; ++i) {
        printf("id: %d pontos: %d ", heap->pendencias[i].id, heap->pendencias[i].pontos);
    }
}

/* busca binaria ================================================================================ */

int busca_binaria_solicitacoes(Solicitacoes* solicitacoes, int(*ordenar)(Solicitacoes*, int, int),  int valor) {
	int inicio = 0, fim, meio;
    fim = solicitacoes->nroSolicitacoes;
    while(inicio < fim) {
        meio = (inicio + fim) / 2;
        int u = ordenar(solicitacoes, meio, valor);
        if(u == meio) return meio; 
        else if(u < valor) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

