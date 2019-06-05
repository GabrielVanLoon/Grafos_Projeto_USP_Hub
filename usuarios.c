#include "usuarios.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Definindo o arquivo de usuarios
 */
const char arquivoUsuarios[60] = "binarios/usuarios.bin";

int usr_carregarUsuarios(UsuariosHeader* usersHeaders, Usuario** users){
    if(usersHeaders == NULL || users == NULL)
        return 1;

    // Primeira faz a abertura do arquivo, caso ele não exista retorna uma lista
    // de usuarios vazia e o cabeçalho com tamanho 0.
    FILE* fp = fopen(arquivoUsuarios, "r+b");
    (*users) = NULL;
    usersHeaders->qtdUsuarios = 0;

    if(fp == NULL){
        return 0;
    } 

    // Arquivo existe mas está vazio, também retorna uma lista vazia
    if( fread( usersHeaders, sizeof(UsuariosHeader), 1, fp) != 1){
        return 0;
    }

    // Lê os @qtdUsuarios do arquivo
    if(usersHeaders->qtdUsuarios > 0){
        (*users) = calloc(sizeof(Usuario), usersHeaders->qtdUsuarios);
        for(int i = 0; i < usersHeaders->qtdUsuarios; i++){
            if( fread( &((*users)[i]), sizeof(Usuario), 1, fp) != 1 ){
                usersHeaders->qtdUsuarios = i;
                break;
            }
        }
    } 
    
    // Fecha o arquivo e finaliza a função
    fclose(fp);
    return 0;
}

int usr_descarregarUsuarios(UsuariosHeader* usersHeaders, Usuario** users){
    if(usersHeaders == NULL || users == NULL)
        return 1;

    // Primeira faz a abertura do arquivo, caso ele não exista retorna erro
    FILE* fp = fopen(arquivoUsuarios, "w+b");
    if(fp == NULL){
        return 1;
    } 

    // Escreve o cabeçalho e em seguida os registros
    fseek(fp, 0, SEEK_SET);
    fwrite( usersHeaders, sizeof(UsuariosHeader), 1, fp);
    for(int i = 0; i < usersHeaders->qtdUsuarios; i++){
        fwrite( &((*users)[i]), sizeof(Usuario), 1, fp);
    }
    
    // Fecha o arquivo e desaloca todas os vetores utilizados
    fclose(fp);
    free((*users));
    (*users) == NULL;
    return 0;
}

int usr_inserirNovoUsuario(UsuariosHeader* usersHeaders, Usuario** users, Usuario* u){
    if(usersHeaders == NULL || users == NULL || u == NULL)
        return 1;

    int indice = usersHeaders->qtdUsuarios;
    
    usersHeaders->qtdUsuarios += 1;
    (*users) = realloc((*users), usersHeaders->qtdUsuarios * sizeof(Usuario));
    (*users)[indice] = (*u);

    return 0;
}

int usr_buscarUsuario(UsuariosHeader* usersHeaders, Usuario** users, char* login){
    if(usersHeaders == NULL || users == NULL || login == NULL)
        return -1;

    // Busca o login no vetor de usuarios, se existir retorna a posição senão retorna -1
    for(int i = 0; i < usersHeaders->qtdUsuarios; i++){
        if(strcmp(login, (*users)[i].login ) == 0)
            return i;
    }

    return -1;
}

void usr_listarUsuarios(UsuariosHeader* usersHeaders, Usuario** users){
    if(usersHeaders == NULL || users == NULL)
        return;

    printf("\tQuantidade de usuários: %d.\n", usersHeaders->qtdUsuarios);
    for(int i = 0; i < usersHeaders->qtdUsuarios; i++){
        printf("\tUsuário nº %d\tLogin: '%s'\n", (*users)[i].id, (*users)[i].login);
    }
    getchar();
}