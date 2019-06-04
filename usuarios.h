#ifndef USUARIOS_H 
    #define USUARIOS_H 10
    
    /**
     * USUARIOS.BIN
     * 
     * O arquivo usuarios.bin servirá com um arquivo de indice primário.
     * Seu objetivo é carregar na memória um array com todos os usuários cadastrados no
     * sistema. Para isso ele salva a relação [id,login] de cada usuário.
     */

    /**
     * Struct de cabeçalho do UsuariosHeader.h
     * Obs.: Cabeçalho fica no primeiro index de memória
     */
    typedef struct _usuariosHeader{
        int  qtdUsuarios;
    } UsuariosHeader;

    /**
     * Struct de dados do Usuario.h
     */
    typedef struct _usuario{
        int   id;
        char  login[60];
    } Usuario;

    /**
     * Funções básicas para manipulação da lista
     */
    int usr_carregarUsuarios(UsuariosHeader* usersHeaders, Usuario** users);

    int usr_descarregarUsuarios(UsuariosHeader* usersHeaders, Usuario** users);

    int usr_inserirNovoUsuario(UsuariosHeader* usersHeaders, Usuario** users, Usuario* u);

    int usr_buscarUsuario(UsuariosHeader* usersHeaders, Usuario** users, char* login);

#endif 