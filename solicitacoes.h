#ifndef SOLICITACAO_H
#define SOLICITACAO_H
#include <stdio.h>
#include <stdlib.h>

typedef struct no_solicitacoes {
	int		id;
	int		pontos; //pontos de afinidade.
}NoSolicitacoes;

typedef struct Solicitacoes_ {
	NoSolicitacoes 	pendencias[100];
	int 			nroSolicitacoes;
} Solicitacoes;

/* Inicializa Solicitacoess com pontuacao zero*/
int sol_novoUsuario();

int sol_escreverSolicitacoes(Solicitacoes* sol, int id);

int sol_lerSolicitacoes(Solicitacoes* sol, int id);

int sol_addSolicitacao (Solicitacoes* sol, int id, int idAmigo, int pontosAmigo);

int sol_recusarSolicitacao (Solicitacoes* sol, int id, int idAmigo);

/* heapsort ====================================================================== */

/* Ordenar Solicitacoes pela funcao (ordenar*), a qual pode ser maiorId ou maiorPontos */
// Ordenar pelo id passar @param (*ordenar) : maiorId
// Ordenar pelos pontos (default) @param (*ordenar) : maiorPontos
void heapsort_solicitacoes(Solicitacoes* heap, int (*ordenar)(Solicitacoes*, int, int));

/* Exibe vetor */
void print_heap_solicitacoes(Solicitacoes* heap);

/* Busca binaria =======================================================================*/

/* Busca binaria no vetor pendencias de Solicitacoes */
int busca_binaria_solicitacoes(Solicitacoes* solicitacoes, int(*ordenar)(Solicitacoes*, int, int),  int valor);

int maiorIdSolicitado(Solicitacoes* heap, int indexA, int indexB);

int maiorPontosSolicitado(Solicitacoes* heap, int indexA, int indexB);

#endif