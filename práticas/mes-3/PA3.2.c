#include <stdio.h>

int main()
{

	// Estruturação, ou seja, guardando os dados
	int i;
	int fibonacci[41];
	int chamadas[41];

	fibonacci[0] = 0;
	fibonacci[1] = 1;
	chamadas[0] = 0;
	chamadas[1] = 0;

	for (i=2; i<40;i++)
	{
		fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
		chamadas[i] = chamadas[i-1]+chamadas[i-2]+1;
	}

	for (i=0; i<40; i++)
		chamadas[i] = chamadas[i] * 2;


	// Acesso aos dados previamente calculados

	int numChamadas, posicao;
	scanf("%d\n", &numChamadas);

	for(i=0; i<numChamadas; i++)
	{
		scanf("%d\n", &posicao);
		printf("fib(%d) = %d calls = %d\n", posicao, chamadas[posicao], fibonacci[posicao]);
	}
	return 1;
}
