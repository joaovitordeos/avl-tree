#include <stdio.h>
#include "libavl.h"

int main (int argc, char **argv){
    no_t *t;
    int chave;

    t = NULL;

    scanf("%d", &chave);
    t = criaNo(chave);
    
    while (chave){
        imprimeArvore(t);

        scanf("%d", &chave);

        insereNo(t, chave);
    }

    destroiArvore(t);

    return 0;
}