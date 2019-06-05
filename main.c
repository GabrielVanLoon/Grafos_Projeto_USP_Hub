#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "usuarios.h"
#include "dados.h"
#include "telas.h"

/**
 * A main() tem como função controlar o fluxo de telas do usuário. Além disso
 * ela também possui as variáveis que irão conter todos os dados necessários para
 * que o sistema funcione.
 */
int main(void){
    
    // Variáveis que serão manipuladas pelo sistema à nivel de login
    UsuariosHeader  glob_usuariosHeader;
    Usuario*        glob_usuarios;
    Usuario         glob_usuarioAtual;
    Dados           glob_dadosUsuarioAtual;

    // Variável que irá controlar a tela atual do usuário 
    int telaAtual = TELA_LOGIN;

    // Realiza as configurações do programa
    usr_carregarUsuarios(&glob_usuariosHeader, &glob_usuarios);

    // Realiza o controle das telas
    while(telaAtual != SAIR_PROGRAMA){
        switch (telaAtual) {
            case TELA_LOGIN:
                telaAtual = carregarTelaLogin(&glob_usuariosHeader, &glob_usuarios, &glob_usuarioAtual);
                break;
            case TELA_DASHBOARD:
                telaAtual = carregarTelaDashboard(&glob_usuariosHeader, &glob_usuarios, &glob_usuarioAtual);
                break;
        }
    }

    // Desaloca da memórias as variáveis à nivel de login
    usr_descarregarUsuarios(&glob_usuariosHeader, &glob_usuarios);

    return 0;
}