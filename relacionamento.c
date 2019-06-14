#include "relacionamento.h"

const char arquivoRelacionamento[] = "binarios/relacionamento.bin";
const int tamanhoRelacionamento = 804;

/* heapsort ====================================================================== */
int maiorId(Relacionamento* heap, int indexA, int indexB);

int maiorPontos(Relacionamento* heap, int indexA, int indexB);

void trocar(Relacionamento* heap, int indexA, int indexB);

void construir_heap(Relacionamento* heap, int (*ordenar)(Relacionamento*, int, int), int n, int i);


int rel_novoUsuario(){
	FILE* fp = fopen (arquivoRelacionamento, "rb+");
	Relacionamento rel;
	char buff;
	if (fp == NULL)
		fp = fopen (arquivoRelacionamento, "wb+");
		
	if(fread(&buff, sizeof(char), 1, fp)) fseek(fp, 0, SEEK_END);

	rel.nroRelacionamento = 0; //Numero de relacionamentos
	for (int i = 0; i < 100; i++){
		rel.amizades[i].id = 0;
		rel.amizades[i].pontos = 0;
	}
	fwrite(&rel, sizeof(Relacionamento), 1, fp);
	fclose(fp);
	return 0;
}

int rel_escreverRelacionamento(Relacionamento* rel, int id){
	FILE* fp = fopen (arquivoRelacionamento, "rb+");
	if (fp == NULL) return 1;
	fseek(fp, (id-1)*sizeof(Relacionamento), SEEK_SET);
	fwrite(rel, sizeof(Relacionamento), 1, fp);
	fclose(fp);
	return 0;
}

int rel_lerRelacionamentos(Relacionamento* rel, int id){
	FILE* fp = fopen (arquivoRelacionamento, "rb");
	if (fp == NULL) return 1;
	fseek(fp, (id-1)*sizeof(Relacionamento), SEEK_SET);
	fread(rel, sizeof(Relacionamento), 1, fp);
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
	printf(" %d %d", rel->amizades[rel->nroRelacionamento].id, rel->amizades[rel->nroRelacionamento].pontos);
	rel->nroRelacionamento++;
	// heapsort_relacionamento pelos pontos
	heapsort_relacionamento(rel, maiorPontos);
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
	
	heapsort_relacionamento(rel, maiorId); //heapsort_relacionamento pelo id

	if(pos = busca_binaria_indice(rel, maiorId, idAmigo), pos != -1) //remove
	{
		rel->amizades[pos].id = 0;
		rel->amizades[pos].pontos = 0;
	}
	heapsort_relacionamento(rel, maiorPontos); // heapsort_relacionamento pelos pontos
	rel->nroRelacionamento--;

	if(rel_escreverRelacionamento(rel, id)) return 1; // reescrita
	return 0;
}

/* heapesort relacionamento ===================================================================================== */

int maiorId(Relacionamento* heap, int indexA, int indexB) {
    return (heap->amizades[indexA].id > heap->amizades[indexB].id)? indexA : indexB;
}

int maiorPontos(Relacionamento* heap, int indexA, int indexB) {
    return (heap->amizades[indexA].pontos > heap->amizades[indexB].pontos)? indexA : indexB;
}

void trocar(Relacionamento* heap, int indexA, int indexB) 
{
    NoRelacionamento aux;
    aux.id = (heap->amizades[indexA].id);
    aux.pontos = (heap->amizades[indexA].pontos);
    (heap->amizades[indexA].id) = (heap->amizades[indexB].id);
    (heap->amizades[indexA].pontos) = (heap->amizades[indexB].pontos);
    (heap->amizades[indexB].id) = aux.id;
    (heap->amizades[indexB].pontos) = aux.pontos;
    return;
}

void construir_heap(Relacionamento* heap, int(*ordenar)(Relacionamento*, int, int), int n, int i) 
{
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

void heapsort_relacionamento(Relacionamento* heap, int(*ordenar)(Relacionamento*, int, int)) 
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

void print_heap_relacionamento(Relacionamento* heap) 
{
    for(int i = 0; i < heap->nroRelacionamento; ++i) {
        printf("id: %d pontos: %d\n", heap->amizades[i].id, heap->amizades[i].pontos);
    }
}

/* busca binaria ================================================================================ */

int busca_binaria_indice(Relacionamento* relacionamento, int(*ordenar)(Relacionamento*, int, int),  int valor) {
	int inicio = 0, fim, meio;
    fim = relacionamento->nroRelacionamento;
    while(inicio <= fim) {
        meio = (inicio + fim) / 2;
        int u = ordenar(relacionamento, meio, valor);
        if(u == meio) return meio; 
        else if(u < valor) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

