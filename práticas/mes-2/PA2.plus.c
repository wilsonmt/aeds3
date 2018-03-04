#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
 
 
typedef struct menorPalavra
{
    char palavra[100];
}menorPalavra;
 
 
void estrutura(char linha[10001], menorPalavra palavras[27])
{
    char bkp[10001];
    strcpy(bkp, linha);
 
    int inicial;
    int tamPLista, tamPNova;
    int numAbrev = 0;
    int i;
 
    char * palavra;

    palavra = strtok(linha, " \n\0");
 
    while (palavra != NULL)
    {
        inicial = palavra[0] - 97;
        tamPNova = strlen(palavra);
        tamPLista = strlen(palavras[inicial].palavra);
 
        if (tamPNova > tamPLista && tamPNova>2)
            strcpy(palavras[inicial].palavra, palavra);
         
        palavra = strtok(NULL, " \n\0"); 
    }
     
    palavra = strtok(bkp, " \n\0");

 
    while (palavra != NULL)
    {
        inicial = palavra[0] - 97;
 
        if (!strcmp(palavras[inicial].palavra, palavra))
        {
            printf("%c. ", palavra[0]);
            numAbrev++;
        }
        else
            printf("%s ", palavra);
 
        palavra = strtok(NULL, " \n\0"); 
    }
    printf("\n%d\n", numAbrev);
 
    for (i=0; i<27; i++)
    {
        if (palavras[i].palavra[0] != '\0')
            printf("%c.: %s\n", palavras[i].palavra[0], palavras[i].palavra);
    }

}
 
 
int main()
{
    int i;
    char linha[10001];
    menorPalavra palavras[27];
 
    while(1)
    {
 
        fgets (linha, 10001, stdin);
        if (linha[0]=='.' && linha[1]=='\n')
            break;
        else
        {
            for(i=0; i<27; i++)
                palavras[i].palavra[0] = '\0';
            estrutura(linha, palavras);
        }
    }
}