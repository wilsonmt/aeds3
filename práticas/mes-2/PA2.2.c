#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void primeira(char linha[1001], int tam)
{
	int i, aux;
	for (i=0; i<tam; i++)
	{
		aux = linha[i];
	
		if (aux>=65 && aux<=122)
		{
			aux += 3;
			linha[i] = aux;
		}
	}
} 

void segunda(char linha[1001], int tam)
{
	char aux;
	int i, j = tam;

	for (i=0; i<tam/2; i++)
	{
		j--;
		aux = linha[i];
		linha[i] = linha[j];
		linha[j] = aux; 
	}
}

void terceira(char linha[1001], int tam)
{
	int i, aux;

	for (i=tam/2; i<tam; i++)
	{
		aux = linha[i];
		aux -= 1;
		linha[i] = aux;
	}
}


void calcula(char linha[1001])
{
	int tam = strlen(linha)-1;
	primeira(linha, tam);
	segunda(linha, tam);
	terceira(linha, tam);
	printf("%s", linha);
}


int main()
{
	int numCasosTeste, i;
	char linha[1001];

	scanf("%d\n", &numCasosTeste);

	for (i=0; i<numCasosTeste; i++)
	{
		fgets (linha, 1001, stdin);
		calcula(linha);
	}
	return 0;
}