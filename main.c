#include <stdio.h>
#include "libavl.h"

#define INSERIR 'i'
#define REMOVER 'r'

int main (int argc, char **argv){
    no_t *raiz;
    int chave;
    char op;

    raiz = NULL;
    scanf("%c %d", &op, &chave);
    while (chave != 0){
        
        if (raiz == NULL)
            raiz = criaNo(chave);
        else{ 
            if (op == INSERIR)  raiz = insereNoAvl(raiz, chave);
            if (op == REMOVER)  raiz = removeNo(buscaNo(raiz, chave), raiz);
        }

        if (raiz != NULL){
           printf("Operacao %c, no: %d\n", op, chave);
           if (raiz->esq && raiz->dir) printf("Raiz: %d, fDir: %d, fEsq: %d\n", raiz->chave, raiz->dir->chave, raiz->esq->chave);
           else printf("Raiz: %d\n", raiz->chave);
           imprimeArvore(raiz, 0);
           printf("\n");
        }

        scanf("%c %d", &op, &chave);
    }

    destroiArvore(raiz);

    return 0;
}