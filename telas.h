#ifndef TELAS_H
    #define TELAS_H

    /**
     * Essa classe funciona como um controlador. que delega quais as informações
     * serão exibidas na tela do usuário e também faz as chamadas às funções implementadas
     * nas outras bibliotecas.
     * 
     * Obs.: As configurações foram feitas para um terminal Linux comum. seu comportamento
     *       em um terminal windows não são foram testados. 
     */

    /**
     * INCLUDES NECESSÁRIOS
     */
    #include "usuarios.h"
    #include "dados.h"
    #include "relacionamento.h"
    #include "solicitacoes.h"
    #include "grafo.h"

    /**
     * MAPEAMENTO DAS TELAS
     */
    #define TELA_LOGIN      110
    #define TELA_DASHBOARD  120
    #define SAIR_PROGRAMA   400

    /**
     * CORES UTILIZADAS PELO PROGRAMA
     */
    #define RESET       "\033[0m"
    #define CVERMELHO   "\033[1;31m"
    #define CVERDE      "\033[1;32m"
    #define CAZUL       "\033[1;34m"
    #define CCIANO      "\033[1;36m"
    #define CROSA    "\033[1;35m"

    /**
     * TELAS DO SISTEMA
     */
        /**
         * Exibe as opcoes da tela de login e pede para o usuario selecionar a operacao
         */
        int carregarTelaLogin(UsuariosHeader* usersHeaders, Usuario** users, Usuario* user);
        
        /**
         * Exibe as opcoes da tela de Dashboard. O usuário precisa já estar logado.
         */
        int carregarTelaDashboard(UsuariosHeader* usersHeaders, Usuario** users, Usuario* user);

        /**
         * Exibe todas as solicitações pendentes do usuário. Sendo ele obrigado à aceitar ou recusar elas.
         */
        int carregarTelaSolicitacoesPendentes(Usuario** users, Usuario* user, Solicitacoes* solicitacoes);

        /**
         * Exibe todos os amigos do usuario logado.
         */
        int carregarTelaListarAmigos(Usuario** users, Usuario* user, Relacionamento* amigos);

        /**
         * Exibe a tela sugerindo as 20 pessoas com maior pontuação de afinidade.
         */
        int carregarTelaSugestoesAmizades(Usuario** users, Usuario* user, Rank *r);

        /**
         * Exibe a pessoa com maior ponto de afinidade e que não está comprometida.
         */
        int carregarTelaParceiroIdeal();

    /**
     * FORMULÁRIOS E OUTRAS INTERAÇÕES
     */
        int carregarFormularioCadastro(UsuariosHeader* usersHeaders, Usuario** users);
        
        int carregarFormularioLogin(UsuariosHeader* usersHeaders, Usuario** users, Usuario* user);

        int carregarFormularioAdicionarAmigo(UsuariosHeader* usersHeaders, Usuario** users, Usuario* user, Rank* r);

        int carregarFormularioRemoverAmigo();

    /** FUNÇÕES UTILITÁRIAS
     */
        void mostrarTitulo(char* nomeTela);

        void mostrarOpcao(char num, char* desc);

        void mostrarOpcaoSair(char* desc);

        void mostrarPressioneEnter();
#endif