
//------------------------------ Include

#include <stdio.h>
#include <stdlib.h>


//------------------------------ Struct

/*Estutura usada para a arvore de possibilidades */
typedef struct arvore * pArvore;

typedef struct arvore{
	int valor;
	pArvore naoCome, come;
}arvore;


/* Estutura usada para armazenar as instancias
	e seus respectivos resultados */
typedef struct entrada * pEntrada;

typedef struct entrada{
	int limiteCal;
	int numAlimentos;
	int * calorias;
	int resultado;
}entrada;


//------------------------------ Headers

void fazArvore(pArvore tree, int * calorias, int valorPai, int nivel,
	int limite, int come, int numAlimentos, int * achou);

void liberaArvore(pArvore tree);

void central (pEntrada dados);

void * centralParalelizado (void * dadosV);
