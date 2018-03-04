#include <stdio.h>
#include <stdlib.h>


typedef struct aresta
{
	int a, b;
	int peso;
}aresta;

int comparaQSort(aresta * a, aresta * b)
{
	if (a->peso > b->peso)
		return 1;	
	else if (a->peso == b->peso)
		return 0;
	else if (a->peso < b->peso)
		return -1;
}

int encontra(int * vetor, int a)
{
	if(vetor[a] != a)
		vetor[a] = encontra(vetor, vetor[a]);
	else
		return a;
}

void junta(int * vetor, int a, int b)
{
	vetor[encontra(vetor, a)] = encontra(vetor, b);
}

void kruskal(aresta * arestas, int numArestas, int numVertices, int pesoTotal)
{
	int i, economia, pesoUsado=0;
	int * vetor = (int *) calloc (numVertices+1, sizeof(int));

	qsort (arestas, numArestas, sizeof(aresta), (void *)comparaQSort);
	
	for (i=0; i<numVertices; i++)
		vetor[i]=i;	

	for (i=0; i<numArestas; i++)
	{
		if (encontra(vetor, arestas[i].a) != encontra(vetor, arestas[i].b))
		{
			junta(vetor, arestas[i].a, arestas[i].b);
			pesoUsado += arestas[i].peso;
		}
	}

	economia = pesoTotal - pesoUsado;
	printf("%d\n", economia);
	free (vetor);
}


int main()
{
	
	int numVertices, numArestas, i, pesoTotal;
	aresta * arestas = (aresta *) calloc (1, sizeof(aresta));

	while (1)
	{
		scanf("%d %d", &numVertices, &numArestas);

		if (numVertices==0)
			break;

		arestas = (aresta *) realloc (arestas,  (numArestas+1) * sizeof(aresta));
		pesoTotal = 0;

		for (i=0; i<numArestas; i++)
		{
			scanf ("%d %d %d", &arestas[i].a, &arestas[i].b, &arestas[i].peso);
			pesoTotal += arestas[i].peso;
		}
		
		kruskal (arestas, numArestas, numVertices, pesoTotal);
	}

	free (arestas);
	return 1;
}