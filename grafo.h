/*
    Cada usuario novo ganha um id



*/
#ifndef GRAFO_H
#define GRAFO_H
#define maximoUsers 100000

typedef struct user_ {
    int id, 
        cidade, 
        filme,
        livros, 
        tribes, 
        musica;
}User;

typedef struct grafo_ {
    int id, 
        nroUsers,
        pontuacao[maximoUsers];
}Grafo;

int grf_addUser(int cidades, int filme, int livros, int tribes, int musica);

int grf_comparaUser(int idA, int idB);

int grf_calculaPontuacao(int idA, int idB, int* pontos);

#endif