#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "usuarios.h"
#include "dados.h"

/**
 * Defines para mapear as telas
 */
    #define TELA_LOGIN      110
    #define TELA_DASHBOARD  120
    #define SAIR_PROGRAMA   120

/**
 * Variaveis globais que serão utilizadas pelo sistema
 */
    UsuariosHeader  glob_usuariosHeader;
    Usuario*        glob_usuarios;
    Usuario         glob_usuarioAtual;
    Dados           glob_dadosUsuarioAtual;

/**
 * Protótipos das Funções de Telas
 */
    int carregarTelaLogin();
    int carregarTelaDashboard();

/**
 * Protótipos das Funções de Formularios
 */
    int carregarFormularioCadastro();
    // int carregarFormularioLogin();

/**
 * Função principal, só chama a tela que inicia o programa
 */
int main(void){
    
    int telaAtual = TELA_LOGIN;

    // Realiza as configurações do programa
    usr_carregarUsuarios(&glob_usuariosHeader, &glob_usuarios);

    // Realiza o controle das telas
    while(telaAtual != SAIR_PROGRAMA){
        switch (telaAtual) {
            case TELA_LOGIN:
                telaAtual = carregarTelaLogin();
                break;
            case TELA_DASHBOARD:
                telaAtual = carregarTelaDashboard();
                break;
        }
    }

    // Realiza o free dos dados e reescreve o indice da memória para o disco

    return 0;
}

// TELAS

    /**
     * Exibe as opcoes da tela de login e pede para o usuario selecionar a operacao
     */
    int carregarTelaLogin(){
        char opcao = 0;
        do {
            system("clear");
            printf("\n");
            printf("\t***** REDE SOCIAL - AMIZADE VERDADEIRA\n");
            printf("\t1 - Fazer Login\n");
            printf("\t2 - Registrar-se\n");
            printf("\t5 - Sair\n");
            printf("\n\tSelecione a Opção: ");
            fflush(stdout);

            scanf(" %c", &opcao);
        } while(opcao != '1' && opcao != '2' && opcao != '5');

        if(opcao == '2')
            return carregarFormularioCadastro();
        else if(opcao == '5')
            return SAIR_PROGRAMA;
        // else
            // return carregarFormularioLogin();



        return SAIR_PROGRAMA; 
    }

    /**
     * Exibe as opcoes da tela de Dashboard
     */
    int carregarTelaDashboard(){
        return TELA_LOGIN; // todo
    }

// FORMULÁRIOS

    int carregarFormularioCadastro(){
        Usuario novoUsuario;
        Dados   dados;
        memset(&dados, 0, sizeof(Dados));
        memset(&novoUsuario, 0,      sizeof(Usuario));

        // Definindo o ID que irá ser cadastrado
        dados.id = glob_usuariosHeader.qtdUsuarios;
        novoUsuario.id      = glob_usuariosHeader.qtdUsuarios;

        // Faz o usuário preencher os dados
        system("clear");
        printf("\n");
        printf("\t***** REDE SOCIAL - CADASTRAR USUÁRIO\n");
             
        printf("\n\tNome: ");
        scanf(" %59[^\r\n]", dados.nome);

        printf("\n\tIdade: ");
        scanf(" %d", &dados.idade);

        printf("\n\tGênero Masculino [m] ou Feminino [f]: ");
        scanf(" %c", &dados.genero);

        printf("\n\tOrientação Hetero[e], Homossexual[o] ou Bissexual[b]: ");
        scanf(" %c", &dados.orientacao);

        printf("\n\tEstou namorando (s/n): ");
        scanf(" %c", &dados.namorando);

        // Verifica se todos os dados foram inseridos corretamente
        fflush(stdout);
        if( strlen(dados.nome) == 0 || dados.idade < 16 || (dados.genero != 'm' && dados.genero != 'f')
            || (dados.orientacao != 'e' && dados.orientacao != 'o' && dados.orientacao != 'b') 
            || (dados.namorando != 's' && dados.namorando != 'n')) {
                getchar();
                printf("\n\tVocê preencheu algum dado incorretamente!\n");
                printf("\tpressione ENTER para voltar\n");
                getchar();
                return TELA_LOGIN;
        }

        // Faz o usuario criar um login
        int idUsuario = 1, first = 1;
        do {
            if(!first)
                printf("\tO login já está sendo utilizado. Por favor escolha outro.\n");

            printf("\n\tLogin: ");
            scanf(" %59[^\r\n]", novoUsuario.login);
            
            // Verifica se o login já existe
            idUsuario = usr_buscarUsuario(&glob_usuariosHeader, &glob_usuarios, novoUsuario.login);

            if(strlen(novoUsuario.login) == 0){
                idUsuario = 1;
            }

            first = 0;
        } while(idUsuario != -1);

        // Agora só insere os dados no vetor de usuarios e no arquivo de dados
        getchar();
        printf("\n\tUsuario '%s' cadastrado com sucesso!\n", novoUsuario.login);
        printf("\tpressione ENTER para voltar...\n");
        getchar();

        return TELA_LOGIN;
    }