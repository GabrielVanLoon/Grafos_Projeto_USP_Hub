#ifndef OPCOES_GRAFO_H
    #define  OPCOES_GRAFO_H

    /**
     * Mapeia de maneira fixa o id de cada opção possível do usuário.
     */

    typedef enum _musica { 
        Sertanejo   = 1, 
        Rock        = 2, 
        Gospel      = 3,
        MPB         = 4, 
        Pop         = 5, 
        Reggae      = 6, 
        Samba       = 7, 
        Pagode      = 8, 
        Funk        = 9, 
        Eletronica  = 10, 
        OutraMusica = 11
    } Musica;

    enum _cidade {
        Analandia      = 101,
        Araraquara     = 102,
        Brotas         = 103,
        Campinas       = 104,
        Ibate          = 105,
        Limeira        = 106,
        RioClaro       = 107,
        SaoCarlos      = 108,
        SaoPaulo       = 109
    } Cidade;

    enum _filme {
        Acao           = 201,
        Animacao       = 202,
        Aventura       = 203,
        Comedia        = 204,
        ComediaRomantica    = 205,
        Documentario        = 206,
        Drama               = 207,
        FiccaoCientifica    = 208,
        Faroeste            = 209,
        Musical             = 210,
        Romantico           = 211,
        Suspense            = 212,
        Terror              = 213,
        OutroFilme          = 214
    } Filme;

    enum _livro { 
        Ciencia         = 301, 
        Filosofia       = 302, 
        Ficcao          = 303, 
        Historia        = 304, 
        Poesia          = 305, 
        AutoAjuda       = 306, 
        Romance         = 307,
        Novela          = 308, 
        OutroLivro      = 309 
    } Livro;

    enum _tribes { 
        NerdGeek    = 401, 
        Hippie      = 402, 
        Gotico      = 403,
        Hipster     = 404,
        Kpoper      = 405,
        Otaku       = 406,
        Fitness     = 407,
        Outro       = 408 
    } Tribo ;

    /**
     * Outras funções utilitárias...
     */


#endif