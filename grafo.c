#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

const char arquivoGrafo[] = "binarios/grafo.bin";
const int tamanhoGrafo = sizeof(Grafo);

/**
 * Funções para manipulação do Grafo.bin
 */
    int grf_abrirGrafo(Grafo* g, int carregarArestas){
        FILE        *fp = fopen(arquivoGrafo, "rb+");
        ArestaGrafo aux;

        if(fp == NULL){
            g->qtdUsuarios  = 0;
            g->qtdArestas   = 0;
            g->adj          = NULL;
            return 0;
        } 

        fread(&(g->qtdUsuarios), sizeof(int), 1, fp);
        fread(&(g->qtdArestas),  sizeof(int), 1, fp);

        if(carregarArestas){
            g->adj    = malloc((g->qtdUsuarios + 1) * sizeof(char*));
            g->adj[0] = NULL;
            for(int i = 1; i <= g->qtdUsuarios; i++){
                g->adj[i] = calloc(MAX_OPCOES, sizeof(char));
            }

            for(int i = 0; i < g->qtdArestas; i++){
                fread(&(aux.idUsuario), sizeof(int), 1, fp);
                fread(&(aux.idOpcao),   sizeof(int), 1, fp);

                g->adj[aux.idUsuario][aux.idOpcao] = POSSUI_ARESTA;
            }
        }
            
        fclose(fp);
        return 0;
    }

    int grf_destruirGrafo(Grafo* g){
        if(g == NULL || g->qtdArestas <= 0)
            return 1;

        for(int i = 1; i <= g->qtdUsuarios; i++){
            if(g->adj[i] != NULL) free(g->adj[i]);
        }
        free(g->adj);

        g->qtdArestas  = 0;
        g->qtdUsuarios = 0;
    }

    int grf_inserirAresta(int idUsuario, int idOpcao, int ehNovoUsuario){
        FILE* fp;
        Grafo g;

        // Carrega o header do grafo e incrementa os valores
        grf_abrirGrafo(&g, 0);

        if(ehNovoUsuario) 
            g.qtdUsuarios += 1;
        g.qtdArestas  += 1;

        fp = fopen(arquivoGrafo, "rb+");
        if(fp == NULL)
            fp = fopen(arquivoGrafo, "wb+");

        // Atualiza o cabeçalho
        fseek(fp, 0, SEEK_SET);
        fwrite(&(g.qtdUsuarios), sizeof(int), 1, fp);
        fwrite(&(g.qtdArestas),  sizeof(int), 1, fp);

        // Insere a nova aresta
        fseek(fp, 0, SEEK_END);
        fwrite(&(idUsuario), sizeof(int), 1, fp);
        fwrite(&(idOpcao), sizeof(int), 1, fp);

        fclose(fp);
        return 0;
    }

    Rank grf_carregarRank(int idUsuario){
        Rank  r;
        Grafo g;

        // Primeiro carrega o grafo
        grf_abrirGrafo(&g, 1);

        // Configurando o Rank.
        r.qtdItens = g.qtdUsuarios;
        r.usuarios = calloc(r.qtdItens, sizeof(RankItem));

        for(int i = 0; i < r.qtdItens; i++)
            r.usuarios[i].id = i+1;

        /**
         * Cálculo dos pontos
         * 
         * Faz uma busca iterativa em dois niveis. Primeiro acha as opçcoes do usuário
         * e em seguida avança para os outros usuários que também selecionaram essa opcao.
         */
        for(int opt = 1; opt < MAX_OPCOES; opt++){
            if(g.adj[idUsuario][opt] == ARESTA_VAZIA)
                continue;
            
            for(int usr = 1; usr < g.qtdUsuarios; usr++){
                if(usr == idUsuario || g.adj[usr][opt] == ARESTA_VAZIA)
                    continue;
                
                r.usuarios[usr-1].pontuacao += PONTUACAO_PADRAO; 
            }
        }

        /**
         * Ordena o rank e também desaloca o grafo da memória
         */
        grf_destruirGrafo(&g);

        grf_ordernarRank(&r);

        return r;
    }

    void grf_destruirRank(Rank* r){
        if(r == NULL || r->usuarios == NULL)
            return;
        free(r->usuarios);
        r->usuarios = NULL;
    }

    void grf_ordernarRank(Rank* rank){
        if(rank == NULL || rank->qtdItens <= 1)
            return;

        // TODO: Fazer uma ordenação decente pq atualmente está bubble sort
        for(int l = 0; l < rank->qtdItens; l++){
            for(int r = l+1; r < rank->qtdItens; r++){
                if(rank->usuarios[l].pontuacao < rank->usuarios[r].pontuacao){
                    RankItem temp     = rank->usuarios[l];
                    rank->usuarios[l] = rank->usuarios[r];
                    rank->usuarios[r] = temp;
                }
            }
        }
    }