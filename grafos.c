#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

const char arquivoGrafo[] = "binarios/grafo.bin";
const int tamanhoGrafo = sizeof(Grafo);

enum _cidade {
    Angatuba = 0,
    Anhembi = 1,
    Araraquara = 2,
    Araras = 3,
    Campinas = 4,
    Carapicuiba = 5,
    Cerquilho = 6,
    Cotia = 7,
    Guara = 8,
    Osasco = 9,
    Ribeirao_Branco = 10,
    Ribeirao_Preto = 11,
    Sao_Paulo = 12,
    Sorocaba = 13,
    Piracibaca = 14
};

enum _filme {
    Acao = 100,
    Animacao = 101,
    Aventura = 102,
    Chanchada = 103,
    Comedia = 104,
    Comedia_romantica = 105,
    Comedia_dramatica = 106,
    Comedia_de_acao = 107,
    Danca = 108,
    Documentario = 109,
    Drama = 110,
    Ficcao = 111,
    Filmes_de_guerra = 112,
    Musical = 113,
    Romance = 114,
    Seriado = 115,
    Suspense = 116,
    Terror = 117,
    Outro = 118
};

enum _livro { Ciencia = 200, Filosofia = 201, Livro_Ficcao = 202, Historia = 203, Poesia = 204, Auto_Ajuda = 205, Faca_voce_mesmo = 206, Outro_opcao = 207};

enum _tribes { Skatista = 300, Hippie = 301, Punk = 302, Gotico = 303, Emo = 304, Skinhead = 305, outra_tribo = 306 };

enum _musica { Sertanejo = 400, Rock = 401, Gospel_Religioso = 402, Pop_Rock = 403, MPB = 404, Pop = 405, Reggae = 406, Sampa = 407, Pagode = 408, Funk = 409, Eletronica = 410, Outra_estilo = 411 };

int grl_addUser(User* user, int id, int  cidade, int filme, int livro, int tribes, int musica) {
    FILE *fp = fopen(arquivoGrafo, "rb+");
    if(fp == NULL) fp = fopen(arquivoGrafo, "wb+");
    fseek(fp, tamanhoGrafo, SEEK_END);
    fread(user,tamanhoGrafo, 1, fp);
    user->id = id;
    user->cidade = cidade;
    user->filme = filme;
    user->livros = livro;
    user->tribes = tribes;
    user->musica = musica;

    fwrite(user, tamanhoGrafo, 1, fp);
    fclose(fp);
    return 0;

}

int grf_lerUser(User* user, int id) {
 FILE *fp = fopen(arquivoGrafo, "rb+");
    if(fp == NULL) return 1;  
    fseek(fp, (id-1)*tamanhoGrafo, SEEK_SET);
    fread(&user,tamanhoGrafo, 1, fp);
    fclose(fp);
    return 0;
}

int grf_calculaPontuacaoUser(User idA, User idB, int* pontos) {
    *pontos = 0;
    *pontos += (userA.cidade == userB.cidade);
    *pontos += (userA.filme == userB.filme);
    *pontos += (userA.tribes == userB.tribes);
    *pontos += (userA.musica == userB.musica);

    return 0;
}

int grf_dfs(Grafo* grafo, int id) {   
    FILE *fp = fopen(arquivoGrafo, "rb+");
    if(fp == NULL) fp = fopen(arquivoGrafo, "wb+");
    fseek(fp, 0, SEEK_SET);

    int *pontuacao = malloc(sizeof(int)*grafo->nroUsers);
    User *matriz = malloc(sizeof(User)*grafo->nroUsers);

    fread(matriz, sizeof(User), grafo->nroUsers, fp);
    
    for(int i = 0; i < grafo->nroUsers; ++i) {
        grf_calculaPontuacaoUser(&matriz[i], &matriz[id], &pontuacao[i]);
    }

    grafo->pontuacao = pontuacao;
    return 0;
}

/*
int grf_atualizaGrafo(int  cidade, int filme, int livro, int tribes, int musica) {
    FILE *fp = fopen(arquivoGrafo, "rb+");
    if(fp == NULL) fp = fopen(arquivoGrafo, "wb+");
    Grafo grafo;
    User userA, userB;
    int pontos;

    fread(&grafo, sizeof(Grafo), 1, fp);
    grl_addUser(&userA, cidade, filme, livro, tribes, musica);
    grafo.pontuacao[userA.id] =  -1; // para ele mesmo tem a maior pontuacao,
    if( grafo.nroUsers < maximoUsers) {
        for(int i = 0; i < grafo.nroUsers; ++i)
        grf_lerUser(&UserB, i);
        grf_calculaPontuacao(userA.id, userB.id, &pontos);
        grafo.pontuacao[userB.id] =  pontos;
        fseek(fp, (userB.id-1)) 
    }
    ++grafo.nroUsers;
    
    fclose(fp);
    return 0;
}
*/