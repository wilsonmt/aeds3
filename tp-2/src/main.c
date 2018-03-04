
//------------------------------ Include

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


//------------------------------ Main

int main(int argc, char const *argv[])
{

	int numInstancias, planetasNaRota, numConquistas, i, j;
	int * distPlanetas;

	scanf("%d", &numInstancias);

	for(i=0; i<numInstancias; i++)
	{

		scanf("%d %d", &planetasNaRota, &numConquistas);
		distPlanetas = (int *) calloc (planetasNaRota+2, sizeof(int));

		for (j=0; j<=planetasNaRota; j++)
			scanf("%d", &distPlanetas[j]);

		if (argc == 3)
		{
			if (strcmp(argv[1], "-a")==0)
			{
				if (strcmp(argv[2], "FB")==0)
					forcaBruta(distPlanetas, planetasNaRota, numConquistas);
				else if (strcmp(argv[2], "PD")==0)
					algoritmoGuloso(distPlanetas, planetasNaRota, numConquistas);
				else if (strcmp(argv[2], "AG")==0)
					algoritmoGuloso(distPlanetas, planetasNaRota, numConquistas);
				else
					printf("Parâmetro inválido\n");
			}
			else
				printf("Parâmetro inválido\n");
		}
		else
			printf("Parâmetro inválido\n");

		free (distPlanetas);
	}

	return 0;
}
