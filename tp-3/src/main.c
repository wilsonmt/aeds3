
//------------------------------ Include

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "functions.h"


//------------------------------ Main

int main(int argc, char const *argv[])
{

    int numThreads, numInstancias, i, j=0, k;
    char * parte;
    char * entrada = (char *) calloc (2000, sizeof(char));
    /* Armazena o numero de threads que foi passado por parametro */
	if (argc == 3)
	{
		if (strcmp(argv[1], "-t")==0)
            numThreads = atoi(argv[2]);
	}
    /* O numero de instancias e armazenado*/
    scanf("%d\n", &numInstancias);
    /* Cria-se um vetor do tamanho do numero de entradas com o intuito
        de salvar todas as entradas e seus respectivos resultados */
    pEntrada dados;
    dados = (pEntrada) calloc (numInstancias, sizeof(entrada));
    /* Aloca o espaco para cada instancia e coleta o dado ao mesmo tempo */
    for (i=0; i<numInstancias; i++)
    {
        scanf("%d\n", &dados[i].limiteCal);
        dados[i].calorias = (int *) calloc (301, sizeof(int));
        dados[i].numAlimentos = 0;
        fgets(entrada, 2000, stdin);
        parte = (char*)strtok(entrada, " \n\0");
        while(parte != NULL)
        {
            dados[i].calorias[dados[i].numAlimentos] = atoi(parte);
            dados[i].numAlimentos++;
            parte = (char*)strtok(NULL, " \n\0");
        }
    }

    /* Cria-se um vetor de threads */
    pthread_t * threads;
    threads = (pthread_t *) calloc(numThreads, sizeof(pthread_t));
    /* Aloca todos os algoritmos de acordo com as threads*/
    for (i=0; i<numInstancias; i++)
    {
        if (j < numThreads)
        {
            pthread_create (&threads[j], NULL,
                centralParalelizado, (void *)&dados[i]);
        }
        else if (j == numThreads)
        {
            for (k=0; k < numThreads; k++)
                pthread_join (threads[k], NULL);
            j=0;
            pthread_create (&threads[j], NULL,
                centralParalelizado, (void *)&dados[i]);
        }

        if (i == numInstancias-1)
        {
            for (k=0; k <= j; k++)
                pthread_join (threads[k], NULL);
        }
        j++;
    }
    /* Imprime-se o resultado de cada instancia */
    for (i=0; i<numInstancias; i++)
    {
        if (dados[i].resultado == 1)
            printf("sim\n");
        else if (dados[i].resultado == 0)
            printf("nao\n");
    }

	return 1;
}
