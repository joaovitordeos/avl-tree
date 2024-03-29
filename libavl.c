/* TAD - Árvore AVL
 * Autor: João Vitor de Oliveira Souza
 */
#include <stdlib.h>
#include <stdio.h>

#include "libavl.h"

#define ROT_ESQ 1
#define ROT_DIR 2

#define max(x, y) (x>y?x:y)           // Calcula o máximo entre dois inteiros.

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
    
    Retorna no final o ponteiro para a árvore. */
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
        else {                           // Se o nó possuir os dois filhos.
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

/* Essa função realiza a rotação à esquerda. */
no_t *rotacaoEsq(no_t *n){
    no_t *t;

    if (n == NULL || n->dir == NULL) return n;  // Verifica se os nós envolvidos não são nulos. 

    if (n->pai != NULL) {         // Se o pai não é nulo (não é a raiz).
        if (n == n->pai->esq) {    
            n->pai->esq = n->dir; // Se for o filho esquerdo, o pai recebe em seu lugar o filho direito do nó 'n'.
        } else {
            n->pai->dir = n->dir; // Se for o filho direito, o pai recebe em seu lugar o filho direito do nó 'n'.
        }
    }

    // Trocas de ponteiros para a rotação.
    t = n->dir;
    n->dir = t->esq;
    t->esq = n;

    // Troca de pais;
    t->pai = n->pai;
    n->pai = t;

    // Se possuir filho direitor, ele passa a apontar para 'n' como pai
    if (n->dir != NULL) n->dir->pai = n;

    return t;
}

/* Essa função realiza a rotação à direita. */
no_t *rotacaoDir(no_t *n){
    no_t *t;

    if (n == NULL || n->esq == NULL) return n; // Verifica se os nós envolvidos não são nulos.

    if (n->pai != NULL) {           // Se o pai não é nulo (não é a raiz).
        if (n == n->pai->esq) {
            n->pai->esq = n->esq;   // Se for o filho esquerdo, o pai recebe em seu lugar o filho esquerdo do nó 'n'.
        } else {
            n->pai->dir = n->esq;   // Se for o filho direito, o pai recebe em seu lugar o filho esquerdo do nó 'n'.
        }
    }

    // Trocas de ponteiros para a rotação.
    t = n->esq;
    n->esq = t->dir;
    t->dir = n;

    // Troca de pais
    t->pai = n->pai;
    n->pai = t;

    // Se possuir filho esquerdo, ele passa a apontar para 'n' como pai
    if (n->esq != NULL) n->esq->pai = n;

    return t;
}


/*  Imprime na saída padrão e em ordem crescente, as chaves
    e o nível do seu respectivo nó separados por ','. */
void imprimeNivelArvore(no_t *n, int nivel){
    if (n != NULL){
        imprimeNivelArvore(n->esq, nivel + 1);
        fprintf(stdout, "%d,%d\n", n->chave, nivel);
        imprimeNivelArvore(n->dir, nivel + 1);
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

/*  Essa função verifica qual lado da árvore está desbalanceado.

    Retorna o valor da diferença entre o a altura dos nós. */
int verificaBalanceamento(no_t *n){
    if ((n->dir != NULL) && (n->esq != NULL))
        return (n->dir->altura - n->esq->altura);      // Se o nó possuir 2 filhos, a diferença é entre a altura do (direito - esquerdo).

    if (n->dir == NULL)
        return (-1 * n->esq->altura);                  // Se o nó esquerdo for o único filho, então a diferença é dada pela sua altura * -1.            

    return (n->dir->altura);                           // Se o nó direitor for o único filho, então a diferença é dada pela sua altura.
}

/*  Essa função verifica qual vai ser o tipo de rotação.
    blc é o parâmetro que indica qual lado da árvore está 
    desbalanceado. 

    Retorna 1 para rotação simples à esquerda.
    Retorna 2 para rotação simples à direita.
    Retorna 0 se não for nenhuma dessas. */
int verificaRotacao(no_t *n, int blc){
    if (blc > 1){
        // Se o filho direito da raiz possuir o nó esquerdo nulo, ou o lado direito estiver mais alto
        // Retorna a rotação à esquerda.
        if ((n->dir->esq != NULL) && (n->dir->dir !=NULL) && (n->dir->dir->altura >= n->dir->esq->altura))
            return ROT_ESQ;
    }
    if (blc < -1){
        // Se o filho esquerdo da raiz possuir o nó direito nulo, ou o lado esquerdo estiver mais alto
        // Retorna a rotação à direita.
        if ((n->esq->dir != NULL) && (n->esq->esq != NULL) && (n->esq->esq->altura >= n->esq->dir->altura) )
            return ROT_DIR; 
    }
    return 0;
}

/*  Balanceia a árvore. */
no_t *balanceiaArvore(no_t *n){
    int blc;

    blc = verificaBalanceamento(n);

    if (blc > 1){
        if (verificaRotacao(n, blc) == ROT_ESQ){  // Verifica se o desbalanceamento à direita será feito uma rotação simples à esquerda.
            n = rotacaoEsq(n);
        }
        else{
            n->dir = rotacaoDir(n->dir);          // Se não for simples, então realiza a rotação em 'zig-zag'da dir p/ esq.
            n = rotacaoEsq(n);
        }
    }

    else if (blc < -1){
        if (verificaRotacao(n, blc) == ROT_DIR){  // Verifica se o desbalanceamento à esquerda será feito uma rotação simples à direita.
            n = rotacaoDir(n);
        }
        else{
            n->esq = rotacaoEsq(n->esq);          // Se não for simples, então realiza a rotação em 'zig-zag' da esq p/ dir.
            n = rotacaoDir(n);
        }
    }
    
    return n;
}

/*  Essa função faz o balanceamento da árvore até um nó antes da raiz,
    a partir do nó 'n'.
    
    Retorna o ponteiro do último nó rotacionado. */
no_t *balanceiaAteRaiz(no_t *n, no_t *raiz){
    no_t *proxPai;
    if (n == NULL) return raiz;

    proxPai = n->pai;

    while (proxPai != raiz){               
        corrigeAltura(raiz);

        proxPai = balanceiaArvore(proxPai);       // Balanceia as subárvore do nó 'n' até um nó antes ao nó 'raiz'

        proxPai = proxPai->pai;
    }

    proxPai = balanceiaArvore(proxPai);           // Balanceia o nó 'raiz'

    corrigeAltura(proxPai);

    return proxPai;
}

/*  Insere o nó na árvore AVL, mantendo as propriedades da árvore. */
no_t *insereNoAvl(no_t *n, int c){

    insereNo(n, c);

    n = balanceiaAteRaiz(buscaNo(n, c), n);   // Balanceia a árvore a partir do novo nó inserido na árvore.

    return n;
}

/* Remove o nó da árvore AVL, mantendo as propriedades da árvore. */
no_t *removeNoAvl(no_t *n, no_t *noRaiz){
    no_t *novaRaiz, *aux;

    novaRaiz = noRaiz;
    
    if (n == NULL) return novaRaiz;
    

    if ((n->dir == NULL) && (n->esq == NULL)){  // Se o nó for uma folha;
        aux = n->pai;
        
        novaRaiz = removeNo(n, novaRaiz);

        corrigeAltura(novaRaiz);

        novaRaiz = balanceiaAteRaiz(aux, novaRaiz);
    }
    else{ 
        if((n->dir != NULL) && (n->esq == NULL)){   // Se o nó tiver apenas o filho direito.
            aux = n->dir;

            novaRaiz = removeNo(n, novaRaiz);

            corrigeAltura(novaRaiz);

            novaRaiz = balanceiaAteRaiz(aux, novaRaiz); // Balanceia a árvore a partir do filho dir do nó removido.
        }
        else if((n->dir == NULL) && (n->esq != NULL)){  // Se o nó tiver apenas o filho esquerdo.
            aux = n->esq;

            novaRaiz = removeNo(n, novaRaiz);

            corrigeAltura(novaRaiz);

            novaRaiz = balanceiaAteRaiz(aux, novaRaiz); // Balanceia a árvore a partir do filho esq do nó removido.
        }
        else {                                          // Se o nó tiver os dois filhos .
            aux = antecessorNo(n)->pai;

            novaRaiz = removeNo(n, novaRaiz);

            corrigeAltura(novaRaiz);

            novaRaiz = balanceiaAteRaiz(aux, novaRaiz);  // Balanceia a árvore a partir do nó pai do antecessor do nó removido.
        }
    }
    return novaRaiz;
}