# include <stdio.h>
# include <math.h>

void calculaTrabalho (int numHabitantes)
{
	int demandas[numHabitantes+1];
	long long trabalho = 0;
	int i, aux = 0;

	for(i=0; i<numHabitantes; i++)
	{
		scanf("%d", &demandas[i]);

		demandas[i] += aux;
		trabalho += abs(demandas[i]);
		aux = demandas[i];
	}

	printf("%lli\n", trabalho);
}



int main()
{
	int numHabitantes;

	while (1)
	{
		scanf("%d", &numHabitantes);
		if (numHabitantes > 0)
			calculaTrabalho(numHabitantes);
		else
			break;
	}

	return 1;
}
