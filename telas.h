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
        int carregarTelaDashboard();

    /**
     * FORMULÁRIOS E OUTRAS INTERAÇÕES
     */
        int carregarFormularioCadastro(UsuariosHeader* usersHeaders, Usuario** users);
        
        int carregarFormularioLogin(UsuariosHeader* usersHeaders, Usuario** users, Usuario* user);

#endif