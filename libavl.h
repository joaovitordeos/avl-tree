/* TAD - Árvore AVL
 * Autor: João Vitor de Oliveira Souza
 */
#ifndef __LIBAVL__
#define __LIBAVL__

/*  Estrutura do nó com ponteiro para o pai, filho dir. e esq.*/
struct no {
    struct no *dir, *esq, *pai;
    int altura;
    int chave;
};

typedef struct no no_t;

/*  Cria uma struct no_t com o valor chave 'c'.
    
    Retorna um ponteiro para o o nó.
    Retorna NULL se falhar. */
no_t *criaNo(int c);

/*  Destrói a árvore, desalocando toda a memória. */
void destroiArvore(no_t *n);

/*  Busca o nó com chave 'c' na árvore.

    Retorna um ponteiro para o nó se com o valor 'c'.
    Retorna NULL se não encontrar. */
no_t *buscaNo(no_t *n, int c);

/*  Inclui um nó com chave 'c' na árvore.
    
    Retorna o ponteiro para onde o nó foi inserido.

    Obs: Se o a chave já existe o retorno será NULL. */
no_t *insereNo(no_t *n, int c);

/*  Remove o nó com valor 'c' da árvore. 
    
    Retorna o nó que ficou no lugar do nó removido. */
no_t *removeNo(no_t *n, no_t *nRaiz);

/*  Imprime a travessia em ordem crescente. */
void imprimeArvore(no_t *n);


#endif