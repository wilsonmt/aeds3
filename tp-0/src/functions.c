# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "functions.h"


// ---------------------- Funções Lista
	


		// ------ Função auxiliar do qsort para ordenar strings
		
		char comparaQSortString(char * a, char * b)
		{
			if (*a > *b)
				return 1;
			else if (*a == *b)
				return 0;
			else if (*a < *b)
				return -1;

			return 0;
		}


		// ------ Função auxiliar do qsort para ordenar um vetor de inteiros

		int comparaQSortInt(int * a, int * b)
		{
			if (*a < *b)
				return 1;
			else if (*a == *b)
				return 0;
			else if (*a > *b)
				return -1;

			return 0;
		}


		// ------ Função para inserir uma nova palavra na lista

		void insereNovaPalavra (char * palavra, int tam, pontPalavras lista)
		{
			int i;
			//Aloca espaço para a estrutura palavras
			pontPalavras novaPalavra = (pontPalavras) calloc (1, sizeof(palavras));
			//Aloca espaço para o vetor de caracteres de acordo com o tamanho da palavra
			novaPalavra->palavra = (char *) calloc ((tam+1), sizeof(char));
			
			//Copia a palavra			
			for (i=0; i<tam; i++)
				novaPalavra->palavra[i] = palavra[i];
			
			//Número inicial de repetições é 1
			novaPalavra->numRepeticoes = 1;
			//Atribui a struct à lista
			lista->proximo = novaPalavra;
		}


		/* ------ Função que contabiliza uma nova palavra na lista
		podendo acrescentar o número de repetições ou inserir uma nova palavra */

		int contabiliza (char * palavra, int tam, pontPalavras lista)
		{
			//Ordena a palavra
			qsort (palavra, tam, sizeof(char), (void *)comparaQSortString);

			if (lista->proximo == NULL)
			{
				//Insere a palavra se a lista está vazia
				insereNovaPalavra(palavra, tam, lista);
				return 1;
			}
			
			//Se a execução não parou acima, ela continua abaixo
			pontPalavras aux = lista->proximo;

			//Compara com as palavras da lista
			while(aux != NULL)
			{
				if (strcmp(aux->palavra, palavra)==0)
				{
					//Se a palavra já existe na lista só soma no contador
					aux->numRepeticoes++;
					return 0;
				}
				if (aux->proximo == NULL)
				{
					//Se não existe na lista, insere a palavra no fim da lista
					insereNovaPalavra(palavra, tam, aux);
					return 1;
				}
				aux = aux->proximo;
			}
			return 0;
		}


		/* ------ Função que estrutura a lista, ou seja, pega uma string caractere por caractere, 
				quando chega ao fim (palavra), chama a função contabiliza, para que a nova palavra seja contabilizada na lista*/

		int estruturaLista(pontPalavras lista)
		{
			/*Aloca um vetor de caracteres de 51 posições (deixei fixo pois é pouco espaço, se tornando desnecessário o realloc)*/
			char * aux = (char *) calloc (51, sizeof(char));
			//numPalavras conta quantas palavras diferentes estão na lista, se torna importante na hora de imprimir			
			int i, tam=0, numPalavras=0;

			for (i=0; i<51; i++)
			{
				//Pega caractere por caractere
				scanf("%c", &aux[i]);
				if (aux[i]==' ')
				{	
					//Se é espaço contabiliza a palavra e continua a execução
					aux[i] = '\0';
					numPalavras += contabiliza(aux, tam, lista);
					tam = 0;
					i = -1;
				}
				else if (aux[i]=='\n')
				{
					//Se é \n contabiliza a palavra e para a execução
					aux[i]='\0';
					numPalavras += contabiliza(aux, tam, lista);
					tam = 0;
					break;
				}
				else 
				{
					tam++;
				}
			}
			free(aux);
			return numPalavras;
		}


		/* ------ Libera toda a lista, tanto as palavras que foram alocadas dinamicamente
			dentro da lista quanto os campos da lista propriamente dita */

		void liberaLista (pontPalavras lista)
		{
			pontPalavras palavra;
			pontPalavras aux;
			palavra = lista->proximo; 

			while (palavra != NULL)
			{	
				//Libera o vetor de caracteres presente na struct e a struct em si
				aux = palavra->proximo;
				free (palavra->palavra);
				free (palavra);
				palavra = aux;
			}
			//No final libera a lista como um todo
			free(lista);
			lista = NULL;
		}






// ---------------------- Funções Vetor



		// ------ Ordena e imprime um vetor de inteiros

		void imprimeVetor(int * vetor, int tamVetor)
		{
			//Ordena o vetor
			qsort (vetor, tamVetor, sizeof(int), (void *)comparaQSortInt);

			int i;
			//Imprime posição por posição, imprime espaço depois de cada valor, exceto no último		
			for (i=0; i<tamVetor; i++)
			{
				printf("%d", vetor[i]);
				if (i!=tamVetor-1)
					printf(" ");
			}
			printf("\n");
		}


		// ------ Cria um vetor, popula ele com o campo numRepeticoes da lista e chama a função imprimeVetor

		void fazVetor(pontPalavras lista, int tamVetor)
		{
			//Aloca o vetor com o tamanho necessário
			int * vetor = (int *) calloc (tamVetor+1, sizeof(int));

			pontPalavras aux = lista->proximo;
			int i=0;
			
			//Pega cada campo de numRepeticoes e coloca no vetor
			for (i=0; i<tamVetor; i++)
			{
				vetor[i] = aux->numRepeticoes;
				aux = aux->proximo;
			}
			//Chama a função pra imprimir o vetor e depois libera ele
			imprimeVetor(vetor, tamVetor);
			free(vetor);
		}
