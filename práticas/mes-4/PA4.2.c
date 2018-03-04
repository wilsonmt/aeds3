#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void imprime(int tamTexto, char entrada[10001])
{

    char alfabeto[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int posicao, i;
    char escolhido;

    char * parte;
    parte = (char*)strtok(entrada, " \n\0");

    while(parte != NULL)
    {
        posicao = atoi(parte)-1;
        printf("%c", alfabeto[posicao]);

        escolhido = alfabeto[posicao];
        for(i=posicao; i>0; i--)
            alfabeto[i] = alfabeto[i-1];
        alfabeto[0] = escolhido;

        parte = (char*)strtok(NULL, " \n\0");
    }
    printf("\n\n");
}

int main()
{
    int tamTexto, contador=0;
    char entrada[10001];

    while (1)
    {
        scanf("%d\n", &tamTexto);
        if (tamTexto == 0)
            break;
        else
        {
            contador++;
            printf("Instancia %d\n", contador);
            fgets(entrada, 10001, stdin);
            imprime(tamTexto, entrada);
        }
    }
    return 1;
}
