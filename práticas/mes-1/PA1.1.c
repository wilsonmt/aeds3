# include <stdio.h>


int ** estruturaGrafo (int numVertices, int numArestas)
{
	
	int i, j, verticePartida, verticeDestino, linha, coluna;
	int ** grafo = (int**) malloc (sizeof(int*) * numVertices);

	for (i=0; i<numVertices; i++)
	{
		grafo[i] = (int*) malloc(sizeof(int) * numVertices);
		for (j=0; j<numVertices; j++)
			grafo[i][j] = 0;
	}

	for (i=0; i<numArestas; i++)
	{
		scanf ("%d %d", &verticePartida, &verticeDestino);
		grafo [verticePartida][verticeDestino] = 1;
	}

	return grafo;
}


void buscaEmProfundidade (int ** grafo, int numVertices, int numArestas)
{

	int i, j, numParticipantes=0, result;

	int participantes[numVertices];
	for (i=0; i<numVertices; i++)
	{
		participantes[i]=0;
	}

	for (i=0; i<numVertices; i++)
	{
		for (j=0; j<numVertices; j++)
		{
			if (grafo[i][j]==1)
			{
				participantes[i]=1;
				participantes[j]=1;
			}
		}
	}

	for (i=0; i<numVertices; i++)
	{
		if (participantes[i]==1)
			numParticipantes++;
	}

	numParticipantes--;
	result = numParticipantes*2;
	printf("%d\n", result);
}


int main ()
{
	int numCasosTeste, nodoInicial, numVertices, numArestas, movimentos, i;
	int ** visitados;
	int ** grafo;
	int * participantes;
	scanf ("%d", &numCasosTeste);
	
	int pilha[50];

	for (i=0; i<numCasosTeste; i++)
	{
		scanf ("%d", &nodoInicial);
		scanf ("%d %d", &numVertices, &numArestas);
		grafo = estruturaGrafo(numVertices, numArestas);
		visitados = grafo;
		pilha[1] = nodoInicial;
		buscaEmProfundidade (grafo, numVertices, numArestas);
	}
}
