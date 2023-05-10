/* TAD - Árvore AVL
 * Autor: João Vitor de Oliveira Souza
 */
#include <stdlib.h>
#include <stdio.h>

#include "libavl.h"

#define max(x, y) (x>y?x:y) 

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

/*  Essa função troca o pai dos filhos do nó 'n' para
    o novo nó, caso esse 'n' não seja a raiz. */
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
    
    Retorna o ponteiro para o nó raiz.
    Retorna NULL se a árvore ficar vazia. */
no_t *removeNo(no_t *n, no_t *noRaiz){
    no_t *a, *novaRaiz;

    novaRaiz = noRaiz;

    if ((n == noRaiz) && (n->esq == NULL) && (n->dir == NULL)){  // Se o nó a ser removido é único retorna NULL.
        free(n);
        return NULL;
    }  

    if ((n->dir == NULL)){               // Se o nó não tiver o filho direito.
        if (n != noRaiz)                  
            trocaNoPai(n, n->esq);
        else {                           // Se for a raiz o nó esq se torna a nova raiz.
            novaRaiz = n->esq;
            novaRaiz->pai = NULL;
        }
    } 
    else {
        if ((n->esq == NULL)){           // Se o nó não tiver o filho esquerdo.
            if (n != noRaiz)
                trocaNoPai(n, n->dir);
            else {                       // Se for a raiz o nó dir se torna a nova raiz.
                novaRaiz = n->dir;
                novaRaiz->pai = NULL;
            }
        } 
        else {
            a = antecessorNo(n);
            trocaNoPai(a, a->esq);       // Troca o nó antecessor de 'n' pelo seu filho esq.

            a->esq = n->esq;             // Atribui os filhos de 'n' também ao nó 'a'.
            a->dir = n->dir;

            trocaNoPai(n, a);            // Troca o nó 'n' com seu antecessor 'a' se não for a raiz.

            if (a->esq != NULL) a->esq->pai = a;             // Se houver filho esq ele terá como pai o nó 'a'.
            if (a->dir != NULL) a->dir->pai = a;             // Se houver filho dir ele terá como pai o nó 'a'.

            if (n == noRaiz){            // Se 'n' for a raiz, então 'a' se torna a nova raiz.
                novaRaiz = a;
                novaRaiz->pai = NULL; 
            }
        }
    }

    free(n);
    return novaRaiz;
}

/*  Imprime a travessia em ordem crescente. */
void imprimeArvore(no_t *n, int nivel){
    if (n != NULL){
        imprimeArvore(n->esq, nivel + 1);
        if (n->pai != NULL) printf("No: %2d, Pai: %2d, Altura: %2d, Nivel: %2d\n", n->chave, n->pai->chave, n->altura, nivel);
        else printf("No: %2d, Pai: N/A, Altura: %2d, Nivel: %2d\n", n->chave, n->altura, nivel);
        imprimeArvore(n->dir, nivel + 1);
    }
}

/*  Essa função corrige a altura dos nós de uma árvore. */
int corrigeAltura(no_t *n){
    int aDir, aEsq;

    if (n == NULL) return 0;

    aDir = corrigeAltura(n->dir);
    aEsq = corrigeAltura(n->esq);

    n->altura = max(aDir, aEsq) + 1;

    return n->altura;
}

/*  Insere o nó na árvore AVL. */
no_t *insereNoAvl(no_t *n, int c){
    insereNo(n, c);

    corrigeAltura(n);
    

    return n;
}