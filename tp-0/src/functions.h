# include <stdio.h>
# include <stdlib.h>
# include <string.h>


// ---------------------- Struct
		
		typedef struct palavras * pontPalavras;

		typedef struct palavras
		{
			char * palavra;
			int numRepeticoes;
			pontPalavras proximo;
		}palavras;

// ---------------------- Headers

		char comparaQSortString(char * a, char * b);

		int comparaQSortInt(int * a, int * b);

		void insereNovaPalavra (char * palavra, int tam, pontPalavras lista);

		int contabiliza (char * palavra, int tam, pontPalavras lista);

		int estruturaLista(pontPalavras lista);

		void liberaLista (pontPalavras lista);

		void imprimeVetor(int * vetor, int tamVetor);

		void fazVetor(pontPalavras lista, int tamVetor);