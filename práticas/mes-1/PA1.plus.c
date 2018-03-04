#include <stdio.h>
#include <stdlib.h>


int ** estruturaGrafo (int numVertices)
{
	int i, j;
	int ** grafo = (int**) malloc (sizeof(int*) * (numVertices+1));

	for (i=0; i<=numVertices; i++)
	{
		grafo[i] = (int*) malloc(sizeof(int) * (numVertices+1));
		for (j=0; j<=numVertices; j++)
			grafo[i][j] = 0;
	}

	return grafo;
}


void verificaLacos (int numVertices, int numArestas)
{
	int i;
	int a, b;
	int numArestasParticip=0, numVerticesParticip=0;
	
	int ** grafo = estruturaGrafo(numVertices);
	int vetor[numVertices+1];

	for (i=0; i<=numVertices; i++)
		vetor[i]=0;

	for (i=0; i<numArestas; i++)
	{
		scanf("%d %d", &a ,&b);
		
		if (grafo[a][b]==0)
		{	
			numArestasParticip ++;
			grafo[a][b] = 1;
			vetor[a-1] = vetor[b-1] = 1;
		}
	}

	for (i=0; i<numVertices; i++)
	{
		if (vetor[i]==1)
			numVerticesParticip++;
	}

	printf("\nArestas: %d\nVertices: %d\n", numArestasParticip, numVerticesParticip);

	if (numArestasParticip >= numVerticesParticip)
		printf("SIM\n");	
	else
		printf("NAO\n");
}


int main ()
{
	int numCasos, numVertices, numArestas, i;

	scanf ("%d", &numCasos);
	
	for (i=0; i<numCasos; i++)
	{
		scanf ("%d %d", &numVertices, &numArestas);
		verificaLacos(numVertices, numArestas);
	}
	return 1;
}