
//------------------------------ Include

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


//------------------------------ Funções Força Bruta

// Função que aloca a árvore na memória
void fazArvore(pArvore tree, int planetasNaRota, int numNaoConquistas, int limite, int nivel, int conquistado)
{
	if (tree != NULL)
	{
		//Insere o nível da árvore (número de planetas que foram passados no caminho)
		tree->nivel = nivel;
		//Insere o número de comquistas feitas até então
		tree->numNaoConquistas = numNaoConquistas;
		//Informa se último planeta foi conquistado ou não
		tree->conquistado = conquistado;

		//Se o nível respeita aos limites do problema, os filhos serão alocados
		if (tree->nivel < planetasNaRota && numNaoConquistas <= limite)
		{
			//Aloca os dois filhos
			tree->naoConquista = (pArvore) calloc (1, sizeof(arvore));
			tree->conquista = (pArvore) calloc (1, sizeof(arvore));
			//Chama a função recursivamente para continuar a alocação da árvore
			fazArvore(tree->naoConquista, planetasNaRota, numNaoConquistas+1, limite, nivel+1, 0);
			fazArvore(tree->conquista, planetasNaRota, numNaoConquistas, limite, nivel+1, 1);
		}
		else if (tree->nivel == planetasNaRota && numNaoConquistas <= limite)
		{
			/*Se chegou ao limite, não é necessário alocar os dois filhos,
			somente um, já que o planeta destino sempre será ocupado*/
			tree->conquista = (pArvore) calloc (1, sizeof(arvore));
			fazArvore(tree->conquista, planetasNaRota, numNaoConquistas, limite, nivel+1, 1);
		}
	}
}


//Função que calcula os valores da estrutura e insere na árvore
void populaArvore (int * distPlanetas, pArvore tree, int planetasNaRota, int situacaoPai,
		int maiorTrechoPai, int trechoAtualPai, int numConquistas, int * solucao)
{
	//A condição inicial é de que o nó esteja alocado, respeitando as condições impostas na alocação
	if (tree != NULL)
	{
		//O maior trecho inicialmente é herdado do pai
		tree->maiorTrecho = maiorTrechoPai;
		//Verifica se a situação de comquista é para somar ao caminho atual ou iniciar do zero
		if (situacaoPai == 1)
			tree->trechoAtual = distPlanetas[tree->nivel-1];
		else if (situacaoPai == 0)
			tree->trechoAtual = trechoAtualPai + distPlanetas[tree->nivel-1];

		//Se o trecho atual é maior do que o maior trecho herdado do pai, então o mesmo é atualizado
		if (tree->trechoAtual > tree->maiorTrecho)
			tree->maiorTrecho = tree->trechoAtual;

		//Chama a função para popular os filhos do nó atual
		populaArvore(distPlanetas, tree->naoConquista, planetasNaRota,
			tree->conquistado, tree->maiorTrecho, tree->trechoAtual, numConquistas, solucao);
		populaArvore(distPlanetas, tree->conquista, planetasNaRota,
			tree->conquistado, tree->maiorTrecho, tree->trechoAtual, numConquistas, solucao);

		//Verifica se o valor do nó atual pode ser classificado como possível solução
		if (tree->nivel == planetasNaRota && tree->numNaoConquistas == planetasNaRota-numConquistas)
		{
			//Se sim, verifica se realmente é a solução até o momento da execução
			if (solucao[0] > tree->conquista->maiorTrecho || solucao[0] == -1)
				solucao[0] = tree->conquista->maiorTrecho;
		}
	}
}


//Libera a árvore que foi alocada na memória
void liberaArvore(pArvore tree)
{
	if (tree != NULL)
	{
		liberaArvore(tree->conquista);
		liberaArvore(tree->naoConquista);
		free(tree);
	}
}

//Função central que cria a árvore, chama as funções de criar e popular a árvore e de liberar também
void forcaBruta (int * distPlanetas, int planetasNaRota, int numConquistas)
{
	//Cria a árvore de possibilidades
	pArvore tree = (pArvore) calloc (1, sizeof(arvore));
	//Define o limite de "não conquistas" que um nó pode ter para poder ser criado pela árvore
	int limite = planetasNaRota-numConquistas;
	//Variável que armazenará a solução
	int * solucao = (int *) calloc (1, sizeof(int));
	solucao[0]=-1;
	//A árvore é feita de acordo com os parâmetros passados
	fazArvore(tree, planetasNaRota, 0, limite, 0, 0);
	//A árvore é populada de acordo com os valores informados
	populaArvore(distPlanetas, tree, planetasNaRota, 1, 0, 0, numConquistas, solucao);
	//A solução é impressa
	printf("%d\n", solucao[0]);
	//Tudo o que foi alocado é liberado da memória
	free (solucao);
	liberaArvore(tree);
}



//------------------------------ Funções Algoritmo Guloso

//Função que realiza a operação de "pular um planeta"
int identaVetor (int * distPlanetas, int planetasNaRota, int inicial, int final)
{
	int j, soma1, soma2, menor=-1;

	//Percorre o vetor da posição inicial até a final
	for (j=inicial; j<final; j++)
	{
		soma1 = distPlanetas[j]+distPlanetas[j+1];
		soma2 = distPlanetas[menor]+distPlanetas[menor+1];

		/*Se a posição inicial for 0, pega o menor número que aparece primeiro,
			senão pega o menor número que aparece por último*/
		if (inicial == 0)
		{
			if (soma1 < soma2 || menor == -1)
				menor = j;
		}
		else
		{
			if (soma1 <= soma2 || menor == -1)
				menor = j;
		}
	}

	//Identa o vetor, fazendo a menor soma no mesmo e deslocando os demais valores para a esquerda
	//Soma
	distPlanetas[menor] += distPlanetas[menor+1];
	//Deslocando o menor valor
	for (j=menor; j<final; j++)
		distPlanetas[j+1] = distPlanetas[j+2];
	//Retorna a primeira posição após a que foi somada
	return menor+1;
}


void algoritmoGuloso (int * distPlanetas, int planetasNaRota, int numConquistas)
{
	//São definidas quantas operações de redução do vetor serão aplicadas
	int numIteracoes = (planetasNaRota-numConquistas);
	//O tamanho inicial do vetor
	int tamVetor = planetasNaRota+1;
	int i=0, maior=-1, aux;

	while (1)
	{
		//Se o número desejado de iterações foi alcançado a execução para
		if (i==numIteracoes)
			break;
		else
		{
			//Faz a operação de redução do vetor
			aux = identaVetor(distPlanetas, planetasNaRota, 0, planetasNaRota-i);
			i++;
		}

		//Se o número desejado de iterações foi alcançado a execução para
		if (i==numIteracoes)
			break;
		else if (aux <= planetasNaRota-i-1 && i<numIteracoes-1)
		{
			//Se a operação de redução do vetor a partir da próxima posição se aplica, a faz
			aux = identaVetor(distPlanetas, planetasNaRota, aux, planetasNaRota-i);
			i++;
		}
	}

	//Procura o maior item do vetor final para encontrar a solução
	for (i=0; i<=planetasNaRota-numIteracoes; i++)
	{
		if (distPlanetas[i] > maior)
			maior = distPlanetas[i];
	}
	//Imprime a solução
	printf("%d\n", maior);
}
