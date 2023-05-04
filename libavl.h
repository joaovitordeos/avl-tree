#ifndef __LIBAVL__
#define __LIBAVL__

/* Estrutura do nó com ponteiro para o pai, filho dir. e esq.*/
struct no {
    struct no *dir, *esq, *pai;
    int chave;
};

typedef struct no no_t;

/*  Cria uma struct no_t com o valor chave 'c'.
    
    Retorna um ponteiro para o o nó.
    Retorna NULL se falhar. */
no_t *criaNo(int c);

/*  Bus*/
no_t *buscaNo(no_t *n, int c);

#endif