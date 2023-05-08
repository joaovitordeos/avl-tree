#include <stdio.h>
#include "libavl.h"

int main (int argc, char **argv){
    no_t *raiz;
    int chave;
    char op;

    raiz = NULL;
    
    while (scanf("%c %d", &op, &chave)){
        if (raiz == NULL)
            raiz = criaNo(chave);
        else{ 
            if (op == 'i')  insereNo(raiz, chave);
            if (op == 'r')  raiz = removeNo(buscaNo(raiz, chave), raiz);
        }

        printf("Operacao %c, no: %d\n", op, chave);
        if (raiz->esq && raiz->dir) printf("Raiz: %d, fDir: %d, fEsq: %d\n", raiz->chave, raiz->dir->chave, raiz->esq->chave);
        else printf("Raiz: %d\n", raiz->chave);
        imprimeArvore(raiz);
        printf("\n");
    }

    destroiArvore(raiz);

    return 0;
}