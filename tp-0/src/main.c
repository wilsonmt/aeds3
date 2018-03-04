# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "functions.h"


// ---------------------- Main

	int main()
	{
		//lista que sera usada durante toda a execução do programa
		pontPalavras lista;

		int numExecucoes, i;
		int tamVetor;

		//numero de linhas que serao tratadas para verificar se existem anagramas
		scanf("%d\n", &numExecucoes);
		
		//os comandos abaixo sao executados uma vez pra cada linha
		for (i=0; i<numExecucoes; i++)
		{
			//a primeira posicao da lista e alocada
			lista = (pontPalavras) calloc (1, sizeof(palavras));
			//nesta linha a lista e estruturada e o tamanho dela tambem
			tamVetor = estruturaLista(lista);
			//o vetor e montado com o tamanho da lista, populado e impresso
			fazVetor(lista, tamVetor);
			//a lista e liberada
			liberaLista(lista);
		}
		//fim da execucao
		return 0;
	}