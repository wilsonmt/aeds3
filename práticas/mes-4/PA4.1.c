#include <stdio.h>
#include <stdlib.h>


void calculaPossibilidade (int motoristas, int capacidade, int * chegada, int * saida, int * tempo)
{
    int i, j, flag=0;

    for (i=0; i<100000; i++)
        tempo[i] = 0;


    for (i=0; i<motoristas; i++)
    {
        scanf("%d %d", &chegada[i], &saida[i]);
        for (j=chegada[i]; j<saida[i]; j++)
            tempo[j]++;
    }

    for (i=0; i<100000; i++)
    {
        if (tempo[i] > capacidade)
        {
            flag = 1;
            break;
        }
    }

    if (flag==0)
    {
        for (i=0; i<motoristas; i++)
        {
            if (flag)
                break;

            for (j=i; j<motoristas; j++)
            {
                if (saida[i] > chegada[j])
                {
                    if (saida[i] < saida[j])
                    {
                        flag = 1;
                        break;
                    }
                }
            }
        }
    }

    if (flag)
        printf("Nao\n");
    else
        printf("Sim\n");
}

int main ()
{
    int motoristas, capacidade;
    int chegada[10000], saida[10000], tempo[100000];

    while (1)
    {
        scanf("%d %d\n", &motoristas, &capacidade);
        if (motoristas == 0 && capacidade==0)
            break;
        else
            calculaPossibilidade (motoristas, capacidade, chegada, saida, tempo);
    }
    return 1;
}
