#ifndef TELAS_H
    #define TELAS_H

    /**
     * INCLUDES NECESSÁRIOS
     */
    #include "usuarios.h"
    #include "dados.h"

    /**
     * MAPEAMENTO DAS TELAS
     */
    #define TELA_LOGIN      110
    #define TELA_DASHBOARD  120
    #define SAIR_PROGRAMA   400

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
        int carregarTelaSolicitacoesPendentes();

        /**
         * Exibe todos os amigos do usuario logado.
         */
        int carregarTelaListarAmigos();

        /**
         * Exibe a tela sugerindo as 20 pessoas com maior pontuação de afinidade.
         */
        int carregarTelaSugestoesAmizades();

        /**
         * Exibe a pessoa com maior ponto de afinidade e que não está comprometida.
         */
        int carregarTelaParceiroIdeal();

    /**
     * FORMULÁRIOS E OUTRAS INTERAÇÕES
     */
        int carregarFormularioCadastro(UsuariosHeader* usersHeaders, Usuario** users);
        
        int carregarFormularioLogin(UsuariosHeader* usersHeaders, Usuario** users, Usuario* user);

        int carregarFormularioAdicionarAmigo();

        int carregarFormularioRemoverAmigo();

#endif