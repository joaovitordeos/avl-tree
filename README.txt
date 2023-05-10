Algoritmos e Estruturas de Dados III
Trabalho 1 TAD: Árvore AVL
Discente: João Vitor de Oliveira Souza      GRR20211760

OBJETIVO:
	O trabalho tem como objetivo desenvolver a capacidade compreender o
funcionamento da estrutura de dado Árvore de Busca Binária, mais especificamente
sobre a Árvore AVL, cuja qual a principal característica é sempre manter
a árvore balanceada para a otimização de buscas, remoção e inclusão em um valor
médio de comparações O(log n). E para além de compreendê-las, tambémtem como
objetivo buscar forma de implementá-las.

IMPLEMENTAÇÃO:
	Para este trabalho criei um módulo chamado “libavl.c” juntamente com seu
cabeçalho “libavl.h” onde estão todas as funções relacionadas à implementação da
árvore em si.
	Para cada função elaborada em “libavl.c” há em seu cabeçalho em “libavl.h”
uma breve descrição sobre o objetivo da função e sobre seu retorno. Essa lib 
possui uma struct no_t que guarda a chave, o ponteiro p/ filhos/pai e a altura.

A estrutura dos nós é a seguinte:

struct no {
	struct no *dir, *esq, *pai;
	int chave;
	int altura;
};

	Tomei como base para o desenvolvimento da AVL, os algoritmos da BST vistos
em aula com algumas correções para evitar problemas com perca de ponteiros. E
sobre as principais funções (inclusão e remoção) eu implementei da seguinte maneira:

“no_t *insereNoAvl(no_t *n, int c)”:  Para essa função eu usei o algoritmo de
inserção da busca binária vista em aula, e depois de inserido eu uso uma função
de busca “buscaNo(nó, chave)” e chamo a função “balanceiaAteRaiz(nó inserido, nó raiz)”
que é responsável por fazer o balanceamento das subárvores a partir do nó
inserido até a raiz.


“no_t *removeNoAvl(no_t *n, no_t *raiz)”:  Nessa função é necessário fornecer o
ponteiro para o nó a ser removido juntamente com o nó raiz. E dentro do escopo
dessa função eu tratei de 4 casos:

1 – Remoção de um nó folha, onde eu apenas removo o nó e chamo o balanceamento
para todas as subárvores acima até a raiz por meio da função “balanceiaAteRai()”.

2 – Remoção de um nó com filho direito, onde eu chamo o balanceamento para todas
as subárvores a partir do nó esquerdo que o substituiu.

3 – Remoção de um nó com filho esquerdo, que é basicamente o caso 2 porém com o
filho oposto.

4 – Remoção de um nó que possui os dois filhos, onde eu removo o nó e a partir
do pai do seu antecessor eu rebalanceio todas as subárvores até a raiz.

	A remoção dos nós também e feita a partir de uma versão modificada de
remoção de nó da BST visto em aula. Porém para a manutenção das propriedades
da AVL eu usei funções auxiliares. Dentre as funções auxiliares, as que vou dar
mais destaques são as de manutenção das propriedades da AVL:


“corrigeAltura(no_t *n)”: Essa função é responsável por manter a altura de cada
nó correta.


“balanceiaArvore(no_t *n)”: Essa função balanceia uma árvore/subárvore a partir
de uma verificação da altura de seus nós filhos, tratando de cada caso particular.
	Ela usa de uma função separada para verificar qual lado está desbalanceado (se
tiver) e depois dessa verificação ela chama a função “verificaRotacao()” que
retorna um valor inteiro de [0,2] que diz qual será a rotação necessária para 
determinado desbalanceamento.
	Depois de verificar qual será a rotação, ela
chama as funções de rotação necessária, se for necessária uma rotação composta,
ela chamará uma por vez, caso seja uma rotação simples ela chama apenas a 
função de rotação simples.


“no_t *balanceiaAteRaiz(no_t *n, no_t *raiz)”: Função responsável por fazer os
balanceamentos das subárvoresde n, até a raiz, chamando a função “balanceiaArvore()”
em um loop while, retornando o ponteiro para a raiz ou uma possível nova raiz.
