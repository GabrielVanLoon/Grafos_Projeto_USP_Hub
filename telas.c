#include "telas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/** TELAS DO SISTEMA
 */
    int carregarTelaLogin(UsuariosHeader* usersHeaders, Usuario** users, Usuario* user){
        char opcao = 0;
        do {
            system("clear");
            printf("\n\t***** REDE SOCIAL - AMIZADE VERDADEIRA\n\n");
            printf("\t1 - Fazer Login\n");
            printf("\t2 - Crie uma conta!\n");
            printf("\t3 - Mostrar logins\n");
            printf("\t5 - Sair\n");
            printf("\n\tSelecione a Opção: ");
            fflush(stdout);

            scanf(" %c", &opcao); getchar();
        } while(opcao != '1' && opcao != '2' && opcao != '5' && opcao != '3');
        

        // Fazendo as chamadas das opções
        if(opcao == '1'){
            return carregarFormularioLogin(usersHeaders, users, user);

        } else if(opcao == '2'){
            return carregarFormularioCadastro(usersHeaders, users);

        } else if(opcao == '3'){
            printf("\n\n\t***** REDE SOCIAL - LISTA DE LOGINS\n\n");
            usr_listarUsuarios(usersHeaders, users);
        
        } else if(opcao == '5'){
            return SAIR_PROGRAMA;
        } 
            
        return TELA_LOGIN; 
    }

    int carregarTelaDashboard(UsuariosHeader* usersHeaders, Usuario** users, Usuario* user){
        char opcao = 0;

        // Carregando as variáveis que serão manipuladas à nivel de dashboard
        // Relacionamento dsh_amigosUsuario;
        // Dados          dsh_dadosAmigosUsuario;            
        // Solicitacoes   dsh_solicitacoesPendentes;    
        // ?????          dsh_pontosAfinidade;

        // Mostra as solicitações de amizade pendentes caso existam

        // Exibe as principais opções do painel
        while(opcao != '0'){
            do {
                system("clear");
                printf("\n\t***** REDE SOCIAL - DASHBOARD\n\n");
                printf("\t1 - Ver lista de amizades\n");
                printf("\t2 - Ver sugestões de amizades\n");
                printf("\t3 - Enviar solicitação de amizade\n");
                printf("\t4 - Excluir amizade\n");
                printf("\t5 - Encontrar parceiro(a) ideal\n");
                printf("\t0 - Sair\n");
                printf("\n\tSelecione a Opção: ");
                fflush(stdout);

                scanf(" %c", &opcao); 
                getchar();
            } while(opcao < '0' || opcao > '5');

            if(opcao == '1'){

            }
        }

        // Desaloca da memórias as variáveis à nível de dashboard
            
        return TELA_LOGIN; // todo
    }

    int carregarTelaSolicitacoesPendentes(){
        return TELA_DASHBOARD;
    }

    int carregarTelaListarAmigos(){
        return TELA_DASHBOARD;
    }

    int carregarTelaSugestoesAmizades(){
        return TELA_DASHBOARD;
    }

    int carregarTelaParceiroIdeal(){
        return TELA_DASHBOARD;
    }

/** FORMULÁRIOS DO SISTEMA
 */
    int carregarFormularioCadastro(UsuariosHeader* usersHeaders, Usuario** users){
        Usuario novoUsuario;
        Dados   dados;
        memset(&dados,       0, sizeof(Dados));
        memset(&novoUsuario, 0,      sizeof(Usuario));

        // Definindo o ID que irá ser cadastrado
        dados.id            = usersHeaders->qtdUsuarios + 1;
        novoUsuario.id      = usersHeaders->qtdUsuarios + 1;

        // Faz o usuário preencher os dados
        system("clear");
        printf("\n\t***** REDE SOCIAL - CADASTRAR USUÁRIO\n\n");
             
        printf("\tNome: ");
        scanf(" %59[^\r\n]", dados.nome);

        printf("\tIdade: ");
        scanf(" %d", &dados.idade);

        printf("\tGênero Masculino [m] ou Feminino [f]: ");
        scanf(" %c", &dados.genero);

        printf("\tOrientação Hetero[e], Homossexual[o] ou Bissexual[b]: ");
        scanf(" %c", &dados.orientacao);

        printf("\tEstou namorando (s/n): ");
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
        
        // Faz o usuário preencher as preferencias dele (filme, musica, etc...)
        // @TODO 

        // Faz o usuario criar um login
        int idUsuario = 1, first = 1;
        do {
            if(!first)
                printf("\tO login já está sendo utilizado. Por favor escolha outro.\n");

            printf("\tLogin: ");
            scanf(" %59[^\r\n]", novoUsuario.login);
            getchar();

            // Verifica se o login já existe
            idUsuario = usr_buscarUsuario(usersHeaders, users, novoUsuario.login);

            if(strlen(novoUsuario.login) == 0){
                idUsuario = 1;
            } 

            first = 0;
        } while(idUsuario != -1);

        // Agora só insere os dados no vetor de usuarios e no arquivo de dados
        usr_inserirNovoUsuario(usersHeaders, users, &novoUsuario);
        dad_escreverDados(&dados);
        
        // Mensagem final avisando que o usuário foi inserido com sucesso
        
        printf("\n\tUsuario '%s' cadastrado com sucesso!\n", novoUsuario.login);
        printf("\tpressione ENTER para voltar...\n");
        getchar();

        return TELA_LOGIN;
    }

    int carregarFormularioLogin(UsuariosHeader* usersHeaders, Usuario** users, Usuario* user){
        int  id;
        char login[60];

        system("clear");
        printf("\n\t***** REDE SOCIAL - CADASTRAR USUÁRIO\n\n");

        printf("\n\tDigite seu login: ");
        scanf(" %59[^\r\n]", login);
        getchar();

        id = usr_buscarUsuario(usersHeaders, users, login);

        // O usuário existe, então devemos atribuir seus dados para @user e abrir o dashboard
        if(id != -1){
            (*user) = (*users)[id];
            return TELA_DASHBOARD;
        }

        printf("\n\tLogin '%s' não cadastrado no sistema. Verifique se digitou corretamente!\n", login);
        printf("\tpressione ENTER para voltar...\n");
        getchar();
        
        return TELA_LOGIN;
    }

    int carregarFormularioAdicionarAmigo(){
        // TODO
        return TELA_DASHBOARD;
    }

    int carregarFormularioRemoverAmigo(){
        // TODO
        return TELA_DASHBOARD;
    }