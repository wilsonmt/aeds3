#include <stdio.h>
#include <stdlib.h>

void calcula(char linha[1100])
{
	int i, aux, alfabeto[27];

	for (i=0; i<27; i++)
		alfabeto[i]=0;

	for (i=0; linha[i]!='\0'; i++)
	{
		aux = (int)linha[i];
		aux -= 97;
		if (aux>=0 && aux<=27)
			alfabeto[aux]=1;
	}
	aux=0;

	for (i=0; i<=27; i++)
	{
		if (alfabeto[i]==1)
			aux++;
	}
	
	if (aux == 26)
		printf("frase completa\n");
	else if (aux >= 13)
		printf("frase quase completa\n");
	else 
		printf("frase mal elaborada\n");
}


int main()
{
	int numCasosTeste, i;
	char linha[1100];
	scanf("%d\n", &numCasosTeste);

	for (i=0; i<numCasosTeste; i++)
	{
		fgets (linha, 1100, stdin);
		calcula(linha);
	}
	return 0;
}