#include <stdio.h>
#include "libavl.h"

#define INSERIR 'i'
#define REMOVER 'r'

#define NV_INI 0

int main (int argc, char **argv){
    no_t *raiz;
    int chave;
    char op;

    raiz = NULL;

    while (fscanf(stdin, "%c %d", &op, &chave) != EOF){  // Lê as operações até o fim do arquivo
        
        if (raiz == NULL)
            raiz = criaNo(chave);
        else{ 
            if (op == INSERIR)  raiz = insereNoAvl(raiz, chave);
            if (op == REMOVER)  raiz = removeNoAvl(buscaNo(raiz, chave), raiz);
        }
    }
    
    if (raiz != NULL)
        imprimeNivelArvore(raiz, 0);

    destroiArvore(raiz);

    return 0;
}