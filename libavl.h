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

/*  Essa função troca o pai dos filhos do nó 'n' para
    o novo nó, caso esse 'n' não seja a raiz. */
void trocaNoPai(no_t *n, no_t *novoNo);

/*  Remove o nó com valor 'c' da árvore. 
    
    Retorna o ponteiro para o nó raiz.
    Retorna NULL se a árvore ficar vazia. */
no_t *removeNo(no_t *n, no_t *noRaiz);

/*  Essa função realiza a rotação à esquerda.
    
    Retorna um ponteiro para o nó que foi trocado. */
no_t *rotacaoEsq(no_t *n);

/*  Essa função realiza a rotação à direita.

    Retorna um ponteiro para o nó que foi trocado. */
no_t *rotacaoDir(no_t *n);

/*  Essa função corrige a altura dos nós de uma árvore recursivamente. */
int corrigeAltura(no_t *n);

/*  Essa função verifica qual lado da árvore está desbalanceado. Se o valor
    for negativo e < -1, então a árvore está desbalanceada à esquerda. Já se
    a diferença for positiva e > 1, então o desbalanceamento é à direita.
    Caso esteja no intervalo [-1, 1], a árvore está balanceada.

    Retorna o valor da diferença entre o a altura dos nós. */
int verificaBalanceamento(no_t *n);

/*  Essa função verifica qual vai ser o tipo de rotação.
    blc é o parâmetro que indica qual lado da árvore está 
    desbalanceado. 

    Retorna 1 para rotação simples à esquerda.
    Retorna 2 para rotação simples à direita.
    Retorna 0 se não for nenhuma dessas. */
int verificaRotacao(no_t *n, int blc);

/*  Balanceia o nó atual da árvore.  */
no_t *balanceiaArvore(no_t *n);

/*  Essa função faz o balanceamento da árvore até o nó raiz,
    a partir do nó 'n'.
    
    Retorna o ponteiro para a nova raiz (se ela for trocada). */
no_t *balanceiaAteRaiz(no_t *n, no_t *raiz);

/*  Insere o nó na árvore AVL. */
no_t *insereNoAvl(no_t *n, int c);

/* Remove o nó da árvore AVL, mantendo as propriedades da árvore. */
no_t *removeNoAvl(no_t *n, no_t *noRaiz);

/*  Imprime na saída padrão e em ordem crescente, as chaves
    e o nível do seu respectivo nó separados por ','. */
void imprimeNivelArvore(no_t *n, int nivel);

#endif