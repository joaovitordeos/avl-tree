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
    
    Retorna no final o ponteiro para a árvore. */
no_t *insereNo(no_t *n, int c);

/*  Busca o maior nó da árvore/sub árvore. 

    Retorna o ponteiro para o nó com maior valor. */
no_t *maiorNo(no_t *n);

/*  Busca o antecessor do nó 'n' da árvore/sub árvore. 

    Retorna o ponteiro para o nó antecessor. */
no_t *antecessorNo(no_t *n);

/*  Remove o nó com valor 'c' da árvore. 

    Retorna o ponteiro para o nó raiz. */
no_t *removeNo(no_t *n, no_t *nRaiz);

/*  Imprime a travessia em ordem crescente. */
void imprimeArvore(no_t *n, int nivel);

/*  Insere o nó na árvore AVL. */
no_t *insereNoAvl(no_t *n, int c);

/* Remove o nó da árvore AVL, mantendo as propriedades da árvore. */
no_t *removeNoAvl(no_t *n, no_t *noRaiz);


#endif