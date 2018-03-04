# include <stdio.h>
# include <stdlib.h>
# include "functions.h"


//----------------------------- Main

	int main()
	{
		int numExecucoes, numQuarteiroes, numRuas, saida, chegada, distanciaMax, numBombeiros, i, j;
		pCabeca lista;

		// Define o número de execuções
		scanf("%d", &numExecucoes);

		for (i=0; i<numExecucoes; i++)
		{

			scanf("%d %d %d %d %d %d", &numQuarteiroes, &numRuas, &saida, &chegada, &distanciaMax, &numBombeiros);

			// Aloca o vetor de listas no tamanho 'numQuarteiroes'
			lista = alocaLista(numQuarteiroes);

			// Chama a função para inserir as ruas na lista de adjacência
			insereRuas(lista, numRuas);

			/* Após inserir os bombeiros e calcular os quarteirões que podem ser visitados,
				se o  quarteirão final pode ser visitado, a função que calcula o caminho
				de menor porbabilidade de acontecer incêndio até ele é chamada */
			insereBombeiros(lista, numBombeiros, numQuarteiroes, distanciaMax, saida, chegada);

			// Libera tudo que foi alocado
			liberaLista(lista, numQuarteiroes);
		}

		return 1;
	}
