/*
    Cada usuario novo ganha um id



*/
#ifndef GRAFO_H
#define GRAFO_H

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
    int nroUsers;
    int* pontuacao;
}Grafo;

/*
    Adiciona no grafo um usuario.
*/
int grf_addUser(int cidades, int filme, int livros, int tribes, int musica);

/* */
int grf_comparaUser(int idA, int idB);

int grf_calculaPontuacaoUser(User idA, User idB, int* pontos);

int grf_dfs(Grafo* grafo, int id);

#endif