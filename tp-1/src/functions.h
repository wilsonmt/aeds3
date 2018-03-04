# include <stdio.h>
# include <stdlib.h>


//----------------------------- Struct


	typedef struct nos * pNos;
	typedef struct cabeca * pCabeca;

	typedef struct nos{
		int destino;
		float probIncendio;
		pNos proximo;
	}nos;

	typedef struct cabeca{
		int tam;
		int elegivel;
		pNos primeiro;
	}cabeca;



//----------------------------- Headers


		void defineRotas (pCabeca lista, int tam, int inicial, int distanciaMax);

		void maiorProbNaoIncendio (pCabeca lista, int tam, int inicial, int final);

		pCabeca alocaLista(int numQuarteiroes);

		void liberaLista (pCabeca lista, int tam);

		void insere(pCabeca lista, int inicial, int final, float probIncendio);

		void insereRuas(pCabeca lista, int numRuas);

		void insereBombeiros(pCabeca lista, int numBombeiros, int numQuarteiroes, int distanciaMax, int saida, int chegada);
