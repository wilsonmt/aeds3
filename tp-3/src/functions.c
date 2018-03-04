
//------------------------------ Include

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "functions.h"


//------------------------------ Funcoes

	/* ------------------------------
		Funcao que monta a arvore de possibilidades
		e verifica se existe solucao */

void fazArvore(pArvore tree, int * calorias, int valorPai, int nivel,
	int limite, int come, int numAlimentos, int * achou)
{
	/* Se a arvore nao e nula e se a solucao ainda nao foi encontrada */
	if (tree != NULL && achou[0]==0)
	{
		if (nivel > 0)
		{
			/* Se come, o valor total e acrescido ao valor existente,
				senao o valor se mantem inalterado */
			if (come == 0)
            	tree->valor = valorPai;
        	else
            	tree->valor = valorPai + calorias[nivel-1];
		}
		/* Se o valor do no e o mesmo do limite de calorias que e necessario
			a resposta e marcada como 1 e a execucao e interrompida */
		if (tree->valor == limite)
		{
			achou[0] = 1;
			return;
		}
		/* Verifica se e possivel e necessario construir mais arvores
				-> Possivel: Se existem ainda alimentos para calcular
				-> Necessario: Se o valor atual nao extrapola as calorias */
		if (nivel < numAlimentos && tree->valor < limite)
		{
			/* Se ainda nao encontrou a solucao aloca os
				nos filhos e continua a funcao recursiva */
			if (achou[0] == 0)
			{
				//Aloca os dois filhos
				tree->naoCome = (pArvore) calloc (1, sizeof(arvore));
				fazArvore(tree->naoCome, calorias, tree->valor,
					nivel+1, limite, 0, numAlimentos, achou);
			}

			if (achou[0] == 0)
			{
				tree->come = (pArvore) calloc (1, sizeof(arvore));
				if (tree->valor+calorias[nivel]<=limite)
					fazArvore(tree->come, calorias, tree->valor,
						nivel+1, limite, 1, numAlimentos, achou);
			}
		}
	}
}


/* ------------------------------
	Funcao recursiva que libera a arvore */

void liberaArvore(pArvore tree)
{
	if (tree != NULL)
	{
		liberaArvore(tree->come);
		liberaArvore(tree->naoCome);
		free(tree);
	}
}


/* ------------------------------
	Funcao que centraliza as operacoes para descobrir a solucao */

void central (pEntrada dados)
{
	/* A arvore de possibilidades e criada e
		a funcao que calcula a mesma e chamada */
    pArvore tree = (pArvore) calloc (1, sizeof(arvore));
	/* A variavel abaixo guarda a solucao, se e sim ou nao */
	int * achou  = (int *) calloc (2, sizeof(int));
	achou[0] = 0;
	/* Dados pegos da struct */
	int * calorias = dados->calorias;
	int limiteCal = dados->limiteCal;
	int numAlimentos = dados->numAlimentos;
	/* A arvore de possibilidades foi criada e
		a funcao que calcula a mesma e chamada */
    fazArvore(tree, calorias, 0, 0, limiteCal, 0, numAlimentos, achou);
	/* Salva os resultados na struct */
	dados->resultado = achou[0];
	/* Libera o que foi alocado */
	free(achou);
    liberaArvore(tree);
}

/* Funcao auxiliar necessaria para paralelizar */
void * centralParalelizado (void * dadosV)
{
	/* Recebe o parametro void* e faz o casting pra struct
		dados, chamando dessa forma a funcao desejada */
	pEntrada dados;
	dados = (pEntrada)dadosV;
	central(dados);
	pthread_exit(NULL);
}
