#include "relacionamento.h"
#include "solicitacoes.h"

int main() {
    Relacionamento rel;
    int id = 1; //comeca no 1
    for(int i = 1; i < 10000; ++i) {
        if(rel_novoUsuario()) break; // erro
        if(rel_addAmizade (&rel, id, i, (i*7)%101) == 2) {
            printf("Usuario %d atingiu limite de amiguinhos.\n", id);
            rel_lerRelacionamentos(&rel, id);
            print_heap_relacionamento(&rel);
            ++id;
        }
    }
    return 0;
}