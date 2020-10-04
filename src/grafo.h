#ifndef GRAFO_H
    #define GRAFO_H


    /**
     * Includes e defines necessários
     */
    #include "opcoes.h"
    
    #define MAX_OPCOES    410
    
    #define ARESTA_VAZIA    0
    #define POSSUI_ARESTA   1

    #define PONTUACAO_PADRAO 50
    #define LIMIAR_PONTUACAO 100 // Se dois usuarios tiverem <= limiar então não são compativeis


    /**
     * Struct Aresta
     * Faz o mapeamento de uma aresta do tipo idUsuario -> idOpção
     */
    typedef struct _aresta{
        int idUsuario;
        int idOpcao;
    } ArestaGrafo;

    /**
     * Struct Grafo
     * Carrega o grafo bipartido da seguinte forma: matriz_adjacencias[usuario][opcao].
     * Dessa forma é possível obter todas as conexões de preferências existentes no sistema.
     */
    typedef struct _grafo {
        int  qtdUsuarios;
        int  qtdArestas;
        char** adj;
    } Grafo;

    /** 
     * Struct Rank
     * É a struct que de fato interessa para o usuário final, pois vai retornar a relação de
     * usuários do sistema ordenada pelos de maior afinidade com os de menor afinidade. 
     */
    typedef struct _rankItem{
        int id, pontuacao;
    } RankItem;

    typedef struct _rank{
        int        qtdItens;
        RankItem*  usuarios;
    } Rank;

    /**
     * Funções para manipulação do Grafo.bin
     */

    // Lê grafo.bin da memória e carrega no Grafo *g
    int grf_abrirGrafo(Grafo* g, int carregarArestas);

    // Desaloca da memória um Grafo *g que tenha sido carregado com arestas
    int grf_destruirGrafo(Grafo* g);

    // Insere rapidamente na memória novas arestas
    int grf_inserirAresta(int idUsuario, int idOpcao, int ehNovoUsuario);

    /**
     * Função para retornar o rank de usuários mais similares com o @idUsuario.
     */

    // Abre o arquivo de grafo, performa a busca e retorna um rank ordenado pronto para uso 
    Rank grf_carregarRank(int idUsuario);

    // Desaloca a memória utilizada no Rank
    void grf_destruirRank(Rank* r);

    // Ordena os itens de um rank por ordem decrescente de pontuacao
    void grf_ordernarRank(Rank* r);

#endif