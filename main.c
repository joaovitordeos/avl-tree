#include <stdio.h>
#include "libavl.h"

int main (int argc, char **argv){
    int chave;
    char op;
    no_t *raiz;

    raiz = NULL;

    scanf("%c %d", &op, &chave);
    raiz = criaNo(chave);
    
    while (chave){
        imprimeArvore(raiz);
        printf("\n");

        scanf("%c %d", &op, &chave);

        if (op == 'i')  insereNo(raiz, chave);
        if (op == 'r')  raiz = removeNo(buscaNo(raiz, chave), raiz);
    }

    destroiArvore(raiz);

    return 0;
}