#include "telas.h"
#include "relacionamento.h"
#include "solicitacoes.h"
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
            printf("\t0 - Sair\n");
            printf("\n\tSelecione a Opção: ");
            fflush(stdout);

            scanf(" %c", &opcao); getchar();
        } while(opcao != '1' && opcao != '2' && opcao != '3' && opcao != '0');
        

        // Fazendo as chamadas das opções
        if(opcao == '1'){
            return carregarFormularioLogin(usersHeaders, users, user);

        } else if(opcao == '2'){
            return carregarFormularioCadastro(usersHeaders, users);

        } else if(opcao == '3'){
            printf("\n\n\t***** REDE SOCIAL - LISTA DE LOGINS\n\n");
            usr_listarUsuarios(usersHeaders, users);
        
        } else if(opcao == '0'){
            return SAIR_PROGRAMA;
        } 
            
        return TELA_LOGIN; 
    }

    int carregarTelaDashboard(UsuariosHeader* usersHeaders, Usuario** users, Usuario* user){
        char opcao = 0;

        // Mostra as solicitações de amizade pendentes caso existam
        Solicitacoes   dsh_solicitacoesPendentes;
        if(!sol_lerSolicitacoes(&dsh_solicitacoesPendentes, user->id) &&
            dsh_solicitacoesPendentes.nroSolicitacoes > 0){
            
            carregarTelaSolicitacoesPendentes(users, user, &dsh_solicitacoesPendentes);
        }

        // Carregando as variáveis que serão manipuladas à nivel de dashboard
        Relacionamento dsh_amigosUsuario;           
        // ?????          dsh_pontosAfinidade;

        rel_lerRelacionamentos(&dsh_amigosUsuario, user->id);

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

            switch(opcao){
                case '2':
                case '5':
                    break;
                
                case '1':
                    carregarTelaListarAmigos(users, user, &dsh_amigosUsuario);
                    break;
                    
                case '3':
                    carregarFormularioAdicionarAmigo(usersHeaders, users, user);
                    break;

                case '4':
                    carregarFormularioRemoverAmigo(users, user, &dsh_amigosUsuario);
                    break;
            } 
        }

        // Desaloca da memórias as variáveis à nível de dashboard
            
        return TELA_LOGIN; // todo
    }

    int carregarTelaSolicitacoesPendentes(Usuario** users, Usuario* user, Solicitacoes* solicitacoes){
        Relacionamento rel;
        char opt;
        int  aux, aux2;

        for(int i = 0; i < solicitacoes->nroSolicitacoes; i++){
            
            int id = solicitacoes->pendencias[i].id;

            system("clear");
            printf("\n\t***** REDE SOCIAL - PEDIDO DE AMIZADE\n\n");
            printf("\n\tO usuário @%s te enviou uma solicitação de amizade!\n", (*users)[id-1].login);
            printf("\tVocês possuem %d pontos de afinidade.\n", solicitacoes->pendencias[i].pontos);
            printf("\tDeseja aceitar? (s/n): ");
            scanf(" %c%*c", &opt);

            if(opt == 's'){
                aux  = rel_addAmizade(&rel, user->id, solicitacoes->pendencias[i].id, solicitacoes->pendencias[i].pontos);
                aux2 = rel_addAmizade(&rel, solicitacoes->pendencias[i].id, user->id, solicitacoes->pendencias[i].pontos);

                if(aux == 1 || aux == 2){
                    printf("\n\tOcorreu um erro ao aceitar a solicitação.\n");
                    printf("\n\tVerifique se você não alcançou o limite de amigos.\n");
                } else {
                    printf("\n\tUsuário adicionado com sucesso.\n");
                }
                printf("\n\tpressione ENTER para continuar...\n");
                getchar();
            }

            // Exclui o cadastro da solicitação de amizade
            sol_excluirSolicitacao(user->id, solicitacoes->pendencias[i].id);
        }
                        
        return TELA_DASHBOARD;
    }

    int carregarTelaListarAmigos(Usuario** users, Usuario* user, Relacionamento* amigos){
        
        system("clear");
        printf("\n\t***** REDE SOCIAL - LISTA DE AMIGOS\n");

        if(amigos->nroRelacionamento <= 0)
            printf("\n\tVocê ainda não tem nenhum amigx =(\n");
        else
            printf("\n\tVocê possui %d amigos.\n\n", amigos->nroRelacionamento);

        for(int i = 0; i < amigos->nroRelacionamento; i++){ 
            int id = amigos->amizades[i].id;
            printf("\tnº %02d  -  @%-20s (%d pontos de afinidade)\n", i+1, (*users)[id-1].login, amigos->amizades[i].pontos);
        }

        printf("\n\tpressione ENTER para continuar...\n");
        getchar();

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
        rel_novoUsuario();
        sol_novoUsuario();
        
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

    int carregarFormularioAdicionarAmigo(UsuariosHeader* usersHeaders, Usuario** users, Usuario* user){
        Usuario novoAmigo;
       
        system("clear");
        printf("\n\t***** REDE SOCIAL - ADICIONAR AMIGO\n\n");
        printf("\n\tInsira o login de quem deseja adicionar: @");
        scanf("%60s%*c", novoAmigo.login);
        
        // Buscando o amigo
        novoAmigo.id = -1;
        for(int i = 0; i < usersHeaders->qtdUsuarios; i++){
            if(strcmp(novoAmigo.login, (*users)[i].login) == 0){
                novoAmigo.id = (*users)[i].id;
                break;
            }
        }

        // Caso o login não exista
        if(novoAmigo.id == -1){
            printf("\n\tNão encontramos o usuário @%s no sistema.\n", novoAmigo.login);
            printf("\tpressione ENTER para voltar...\n");
            getchar();
        } else {

            sol_addSolicitacao(novoAmigo.id, user->id , 15);
            printf("\n\tSolicitação enviada com sucesso!\n");
            printf("\tpressione ENTER para voltar...\n");
            getchar();

        }
        
        return TELA_DASHBOARD;
    }

    int carregarFormularioRemoverAmigo(Usuario** users, Usuario* user, Relacionamento* amigos){
        Usuario amigo;
       
        system("clear");
        printf("\n\t***** REDE SOCIAL - REMOVER AMIGO\n\n");
        printf("\n\tInsira o login de quem deseja remover: @");
        scanf("%60s%*c", amigo.login);
        
        // Buscando o amigo
        amigo.id = -1;
        for(int i = 0; i < amigos->nroRelacionamento; i++){
            int id = amigos->amizades[i].id;
            if(strcmp(amigo.login, (*users)[id -1].login) == 0){
                amigo.id = (*users)[i].id;
                break;
            }
        }

        // Caso o login não exista
        if(amigo.id == -1){
            printf("\n\tNão encontramos o usuário @%s na sua lista de amizes.\n", amigo.login);
            printf("\tpressione ENTER para voltar...\n");
            getchar();
        } else {

            rel_removeAmizade(amigos, user->id, amigo.id);
            rel_removeAmizade(amigos, amigo.id, user->id);
            rel_lerRelacionamentos(amigos, user->id); // Carregando os amigos atualizado

            printf("\n\tRemoção feita com sucesso!\n");
            printf("\tpressione ENTER para voltar...\n");
            getchar();

        }
        
        return TELA_DASHBOARD;
    }