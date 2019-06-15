/*
	@Descricao: O arquivo relacionamento mantem as relacoes de amizades para os usuarios.
	O arquivo sempre esta de tal modo que o tamanhoRelacionamento * id (do usuario) eh a regiao
	de relacoes deste. 

	Obs: -A ordenacao default eh pelo valor de maior afinidade. Assim ao ler o arquivo, se quiser ordenadar pelo id,
	apenas usar heapsort(relacionamento, maiorId). No entanto, a operação não eh recomendada ser usada fora de funcoes definidas.

*/

#ifndef RELACIONAMENTO_H
#define RELACIONAMENTO_H
#include <stdio.h>
#include <stdlib.h>

typedef struct no_ {
	int		id,
			pontos; //pontos de afinidade.
}NoRelacionamento;

typedef struct relacionamento_ {
	NoRelacionamento 	amizades[100];
	int 				nroRelacionamento;
} Relacionamento;

/* Inicializa relacionamentos com pontuacao zero
	@return 1 erro na abertura do arquivo
	@return 0 ocorreu o esperado 
*/
int rel_novoUsuario();

/* Escrever Relacionamento* rel e escreve no arquivo .bin relacionamento
	@return 1 erro na abertura do arquivo
	@return 0 ocorreu o esperado 
*/
int rel_escreverRelacionamento(Relacionamento* rel, int id);

/* Ler relacionamento.bin e escreve no Relacionamento* rel
	@return 1 erro na abertura do arquivo
	@return 0 ocorreu o esperado 
*/
int rel_lerRelacionamentos(Relacionamento* rel, int id);

/* Adicionar um relacionamento ao arquivoRelacionamento.bin 
	@return 2 se o usuario de (id) atingiu o numero maximo de amizades.
	@return 1 se ocorreu erro na abertura do arquivo.
	@return 0 ocorreu o esperado.
*/
int rel_addAmizade (Relacionamento* rel, int id, int idAmigo, int pontosAmigo);

int rel_removeAmizade (Relacionamento* rel, int id, int idAmigo);

/* Ordenar Relacionamento pela funcao (ordenar*), a qual pode ser maiorId ou maiorPontos */
void heapsort_relacionamento(Relacionamento* heap, int (*ordenar)(Relacionamento*, int, int));

/* Exibe vetor de relacionamento */
void print_heap_relacionamento(Relacionamento* heap);

/* Busca binaria =======================================================================*/
int busca_binaria_indice(Relacionamento* relacionamento, int(*ordenar)(Relacionamento*, int, int),  int valor);

#endif