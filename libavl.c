/* TAD - Árvore AVL
 * Autor: João Vitor de Oliveira Souza
 */
#include <stdlib.h>
#include <stdio.h>

#include "libavl.h"

/*  Cria uma struct no_t com o valor chave 'c'.
    
    Retorna um ponteiro para o o nó.
    Retorna NULL se falhar. */
no_t *criaNo(int c){
    no_t *n;

    if ( !(n = malloc( sizeof(no_t) ) ) ) return NULL;

    n->altura = 0;
    n->chave = c;
    n->pai = NULL;
    n->esq = NULL;
    n->dir = NULL;

    return n;
}

/*  Busca o nó com chave 'c' na árvore.

    Retorna um ponteiro para o nó se com o valor 'c'.
    Retorna NULL se não encontrar. */
no_t *buscaNo(no_t *n, int c){
    if (n == NULL) return NULL;
    
    if (c < n->chave)
        return buscaNo(n->esq, c);
    if (c > n->chave)
        return buscaNo(n->dir, c);
    
    return n;
}

/*  Inclui um nó com chave 'c' na árvore.
    
    Retorna o ponteiro para onde o nó foi inserido.

    Obs: Se o a chave já existe o retorno será NULL. */
no_t *insereNo(no_t *n, int c){
    if (n == NULL) return criaNo(c);

    if (c < n->chave){
        n->esq = insereNo(n->esq, c);
        n->esq->pai = n;
    }
    else if (c > n->chave){
        n->dir = insereNo(n->dir, c);
        n->dir->pai = n;
    }


    return n;
}

/*  Destrói a árvore, desalocando toda a memória. */
void destroiArvore(no_t *n){
    if (n != NULL){
        destroiArvore(n->esq);
        destroiArvore(n->dir);
        free(n);
    }   
}   

/*  Busca o maior nó da árvore/sub árvore. 

    Retorna o ponteiro para o nó com maior valor. */
no_t *maiorNo(no_t *n){
    if (n->dir == NULL) return n;
    
    return maiorNo(n->dir);
}

/*  Busca o antecessor do nó 'n' da árvore/sub árvore. 

    Retorna o ponteiro para o nó antecessor. */
no_t *antecessorNo(no_t *n){
    return maiorNo(n->esq);
}

void trocaNoPai(no_t *n, no_t *novoNo){
    if (n->pai != NULL){
        if (n->pai->dir == n)
            n->pai->dir = novoNo;
        else
            n->pai->esq = novoNo;
        
        if (novoNo != NULL)
            novoNo->pai = n->pai;
    }
}

/*  Remove o nó com valor 'c' da árvore. 
    
    Retorna o ponteiro para o nó raiz. */
no_t *removeNo(no_t *n, no_t *noRaiz){
    no_t *a, *novaRaiz;

    novaRaiz = noRaiz;

    if (n->dir == NULL){            
        trocaNoPai(n, n->esq);
        free(n);
    }
    else{
        if (n->esq == NULL){
            trocaNoPai(n, n->dir);
            free(n);
        }
        else{
            a = antecessorNo(n);
            trocaNoPai(a, a->esq);
            a->esq = n->esq;
            a->dir = n->dir;
            trocaNoPai(n, a);
            
            if (n == noRaiz) novaRaiz = a;
            free(n);
        }
    }
    return novaRaiz;
}

/*  Imprime a travessia em ordem crescente. */
void imprimeArvore(no_t *n){
    if (n != NULL){
        imprimeArvore(n->esq);
        printf("%d ", n->chave);
        imprimeArvore(n->dir);
    }
}