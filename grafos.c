#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

const char arquivoGrafo[] = "binarios/grafo.bin";
const int tamanhoGrafo = sizeof(Grafo);

enum _cidade {
    Angatuba,
    Anhembi,
    Araraquara,
    Araras,
    Campinas,
    Carapicuiba,
    Cerquilho,
    Cotia,
    Guara,
    Osasco,
    Ribeirao_Branco,
    Ribeirao_Preto,
    Sao_Paulo,
    Sorocaba,
    Piracibaca
};

enum _filme {
    Acao,
    Animacao,
    Aventura,
    Chanchada,
    Comedia,
    Comedia_romantica,
    Comedia_dramatica,
    Comedia_de_acao,
    Danca,
    Documentario,
    Drama,
    Ficcao,
    Filmes_de_guerra,
    Musical,
    Romance,
    Seriado,
    Suspense,
    Terror,
    Outro
};

enum _livro { Ciencia, Filosofia, Livro_Ficcao, Historia, Poesia, Auto_Ajuda, Faca_voce_mesmo, Outro_opcao };

enum _tribes { Skatista, Hippie, Punk, Gotico, Emo, Skinhead, outra_tribo };

enum _musica { Sertanejo, Rock, Gospel_Religioso, Pop_Rock, MPB, Pop, Reggae, Sampa, Pagode, Funk, Eletronica, Eletronico, Outra_estilo };

int grl_addUser(User* user, int  cidade, int filme, int livro, int tribes, int musica) {
    FILE *fp = fopen(arquivoGrafo, "rb+");
    if(fp == NULL) fp = fopen(arquivoGrafo, "wb+");
    fseek(fp, tamanhoGrafo, SEEK_END);
    fread(user,tamanhoGrafo, 1, fp);
    user->id++;
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

int grf_calculaPontuacao(int idA, int idB, int* pontos) {
    User userA, userB;

    grf_lerUser(&userA, idA);
    grf_lerUser(&userB, idB);

    *pontos = 0;
    *pontos += (userA.cidade == userB.cidade);
    *pontos += (userA.filme == userB.filme);
    *pontos += (userA.tribes == userB.tribes);
    *pontos += (userA.musica == userB.musica);

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