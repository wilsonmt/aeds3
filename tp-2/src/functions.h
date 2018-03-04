
//------------------------------ Include

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//------------------------------ Struct

typedef struct arvore * pArvore;

typedef struct arvore{
	int conquistado;
    int nivel;
    int numNaoConquistas;
    int trechoAtual;
    int maiorTrecho;
	pArvore naoConquista, conquista;
}arvore;


//------------------------------ Headers

    //------------------------------ Funções Algoritmo Guloso

    void fazArvore(pArvore tree, int planetasNaRota, int numNaoConquistas,
        int limite, int nivel, int conquistado);

    void populaArvore (int * distPlanetas, pArvore tree, int planetasNaRota, int situacaoPai,
		int maiorTrechoPai, int trechoAtualPai, int numConquistas, int * solucao);

    void liberaArvore(pArvore tree);

    void forcaBruta (int * distPlanetas, int planetasNaRota, int numConquistas);


    //------------------------------ Funções Algoritmo Guloso

    int identaVetor (int * distPlanetas, int planetasNaRota, int inicial, int final);

    void algoritmoGuloso (int * distPlanetas, int planetasNaRota, int numConquistas);
