#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "telas.h"
#include "relacionamento.h"
#include "solicitacoes.h"
#include "grafo.h"

int main(void){

    int qtdInsercoes = 0;
    UsuariosHeader  usersHeaders;
    Usuario*        glob_usuarios;
    
    usr_carregarUsuarios(&usersHeaders, &glob_usuarios);

    for(int i = 0; i < qtdInsercoes; i++){
        Usuario novoUsuario;
        Dados   dados;
        memset(&dados,       0, sizeof(Dados));
        memset(&novoUsuario, 0,      sizeof(Usuario));

        dados.id            = usersHeaders.qtdUsuarios + 1;
        novoUsuario.id      = usersHeaders.qtdUsuarios + 1;
        
    }





    // Desaloca da memórias as variáveis à nivel de login
    usr_descarregarUsuarios(&usersHeaders, &glob_usuarios);

}