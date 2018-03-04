#include <stdio.h>
#include <string.h>
#include <math.h>

int verificaNumero(int numero)
{
    int digitos;
    int unidade, dezena, centena, milhar;
    int resultado;

    if (numero >= 1000)
        digitos = 4;
    else if (numero >= 100)
        digitos = 3;
    else
        digitos = 2;

    if (digitos == 2)
    {
        unidade = numero%10;
        dezena = numero/10;
        if (unidade == dezena)
            resultado = 0;
        else
            resultado = 1;
    }
    else if (digitos == 3)
    {
        unidade = numero%10;
        dezena = (numero%100)/10;
        centena = numero/100;
        if (unidade == dezena || unidade == centena || dezena == centena)
            resultado = 0;
        else
            resultado = 1;
    }
    else if (digitos == 4)
    {
        unidade = numero%10;
        dezena = (numero%100)/10;
        centena = (numero%1000)/100;
        milhar = (numero%10000)/1000;
        if (unidade == dezena || unidade == centena || unidade == milhar || dezena == centena || dezena == milhar || centena == milhar)
            resultado = 0;
        else
            resultado = 1;
    }

    return resultado;
}

void fazVetor(int * vetor)
{
    int i;

    for (i=0; i<11; i++)
        vetor[i] = 1;
    for (i=11; i<=5000; i++)
        vetor[i] = verificaNumero(i);
}


int calcula(int inicial, int final, int * vetor)
{
    int i, resultado=0;

    for (i=inicial; i<=final; i++)
    {
        if (vetor[i] == 1)
            resultado ++;
    }

    return resultado;
}


int main()
{
    int vetor[5001];
    int inicial, final, resultado, i=1;
    fazVetor(vetor);

    while( scanf("%d %d", &inicial, &final) != EOF)
    {
        resultado = calcula(inicial, final, vetor);
        printf("%d\n", resultado);
    }
    return 0;
}
