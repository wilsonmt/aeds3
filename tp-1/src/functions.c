# include <stdio.h>
# include <stdlib.h>
# include "functions.h"



//----------------------------- Grafo


	//------------------------- Define quais são os nós elegíveis para participar do caminho


			void defineRotas (pCabeca lista, int tam, int inicial, int distanciaMax)
			{

				// Cria vetor que marca se um vértice foi visitado ou não
				int * visitados = (int *) calloc (tam+1, sizeof(int));
				// Cria vetores que armazenará a menor distância para cada vértice
				int * distancia = (int *) calloc (tam+1, sizeof(int));

				int i, anterior, marcou, menorValor, atual;
				pNos aux;

				// Inicializa o vetor distancia
				for (i=0; i<tam; i++)
					distancia[i]=-1;

				// A distância do inicial para ele próprio é zero
				distancia[inicial] = 0;

				// Percorre todo o vetor para encontrar um quarteirão que ainda não possui a menor distância calculada
				while  (1)
				{
					menorValor = -1;
					for (i=0; i<tam; i++)
					{
						if (visitados[i]==0)
						{
							if (distancia[i]!=-1 && (distancia[i]<menorValor || menorValor==-1))
							{
								menorValor = distancia[i];
								atual = i;
							}
						}
					}

					// Se a distância é diferente de -1 e o vértice ainda não foi visitado, ele é selecionado
					if (menorValor != -1)
					{

						// O vértice é marcado como visitado
						visitados[atual]=1;
						aux = lista[atual].primeiro;
						anterior = atual;

						// Percorre-se por todos os vizinhos do vértice
						while (aux != NULL)
						{

							/* Se um vizinho não foi visitado e não teve a distância calculada (valor -1)
								ou a distância previamente calculada é maior do que a atual, o valor recebe o atual*/
							if (visitados[aux->destino]==0)
							{
								if (distancia[aux->destino]==-1 ||distancia[aux->destino] > distancia[anterior]+1)
								{
									marcou = 1;
									distancia[aux->destino] = distancia[anterior] + 1;
								}
							}
							aux = aux->proximo;
						}
					}
					else
						break;
				}

				/* O vetor externo que guarda a menor distância de um vértice para um bombeiro qualquer
					é atualizado aqui, o menor valor para cada posição entre o gerado acima e o externo é mantido,
					garantindo que o vetor externo sempre guarde a menor distância */
				for (i=0; i<tam; i++)
				{
					if (distancia[i] <= distanciaMax)
						lista[i].elegivel = 1;
				}

				// Os vetores dinâmicos declarados na função recebem free
				free (visitados);
				free(distancia);
			}



	//------------------------- Calcula o caminho com menor probabilidade de incêndio e imprime o mesmo


			void maiorProbNaoIncendio (pCabeca lista, int tam, int inicial, int final)
			{

				// Cria vetor que marca se um vértice foi visitado ou não
				int * visitados = (int *) calloc (tam+1, sizeof(int));
				// Cria vetor que guarda o vértice anterior de cada vértice no caminho
				int * caminhos = (int *) calloc (tam+1, sizeof(int));
				// Cria vetor que armazena as maiores probabilidades de não haver incêndio
				float * probNaoIncendio = (float *) calloc (tam+1, sizeof(float));

				int i, j, atual = inicial;
				float maiorProb, valor;
				pNos aux;

				// Inicializa o vetor probNaoIncendio
				for (i=0; i<tam; i++)
					probNaoIncendio[i] = caminhos[i] = -1;

				/* A probabilidade de não enfrentar um incêndio no primeiro quarteirão é 100%
					tendo em vista que ainda não se saiu do lugar */
				probNaoIncendio[inicial] = 1;

				while (1)
				{

					/* O trecho abaixo seleciona qual será o quarteirão a ser tratado,
						o mesmo deve ter a maior probabilidade de não haver incêndio */

					maiorProb = 0;

					for (i=0; i<tam; i++)
					{
						if (visitados[i]==0)
						{
							if (probNaoIncendio[i]!=-1 && probNaoIncendio[i]>maiorProb && lista[i].elegivel==1)
							{
								maiorProb = probNaoIncendio[i];
								atual = i;
							}
						}
					}

					/* Se algum vértice foi selecionado então o código avança */
					if (maiorProb!=0)
					{

						// O vértice é marcado como visitado
						visitados[atual] = 1;
						aux = lista[atual].primeiro;

						// Os vizinhos do vértice que foi selecionado têm suas probabilidades de incêndio calculadas
						while (aux != NULL)
						{

							if (visitados[aux->destino]==0 && lista[aux->destino].elegivel==1)
							{
								valor = 1 - aux->probIncendio;

								/* Se a probabilidade de não haver incêndio para o vértice não foi calculada antes
									ou se a calculada nesta iteração é maior, a mesma é atribuída ao vértice*/
								if (probNaoIncendio[aux->destino]==-1 || probNaoIncendio[aux->destino]<(probNaoIncendio[atual]*valor))
								{
									probNaoIncendio[aux->destino] = probNaoIncendio[atual] * valor;
									// A linha abaixo guarda qual foi o vértice anterior ao 'aux->destino' no menor caminho
									caminhos[aux->destino] = atual;
								}
								// Se houve empate, a menor ordem lexicográfica é escolhida
								else if (probNaoIncendio[aux->destino] == (probNaoIncendio[atual]*valor))
								{
									if (aux->destino < atual)
									{
										probNaoIncendio[aux->destino] = probNaoIncendio[atual] * valor;
										// A linha abaixo guarda qual foi o vértice anterior ao 'aux->destino' no menor caminho
										caminhos[aux->destino] = atual;
									}
								}
							}
							aux = aux->proximo;
						}
					}
					// Se não houve nenhuma atribuição de maiorProb nessa iteração, significa que a execução chega ao fim
					else
						break;
				}

				if (probNaoIncendio[final] == -1)
					printf("-1\n");
				else
				{
					// Será alocado o caminho do bombeiro
					int * caminhoFinal = (int *) calloc (tam, sizeof(int));

					// É impresso na tela a menor probabilidade de haver incêndio em um caminho começando em
					printf("%.2f", 1-probNaoIncendio[final]);

					int tamCF = 1;

					/* Calculamos o caminho na ordem inversa, tendo em vista que
						o vetor de caminhos armazena o item anterior, e não o próximo */
					caminhoFinal[0] = final;

					// Popula o vetor com o caminho até chegar ao vértice inicial
					while (caminhoFinal[tamCF-1]!=-1 && caminhoFinal[tamCF-1]!=inicial)
					{
						caminhoFinal[tamCF] = caminhos[caminhoFinal[tamCF-1]];
						tamCF++;
					}

					// O vetor é impresso na ordem inversa, ficando correto na ordem de caminho
					for (i=tamCF-1; i>=0; i--)
						printf(" %d", caminhoFinal[i]);
					printf("\n");

					free (caminhoFinal);

				}

				// Tudo o que foi alocado na função é liberado na memória
				free (visitados);
				free (caminhos);
				free (probNaoIncendio);
			}



//----------------------------- Funções lista


	//------------------------- Aloca espaço na memória para um vetor de listas de tamanho 'numQuarteiroes'

			pCabeca alocaLista(int numQuarteiroes)
			{
				pCabeca lista = (pCabeca) calloc (numQuarteiroes, sizeof(cabeca));
				return lista;
			}


	//------------------------- Libera da memória a lista alocada que foi passada como parâmetro

			void liberaLista (pCabeca lista, int tam)
			{
				pNos quarteirao, aux;
				int i;

				for (i=0; i<tam; i++)
				{
					quarteirao = lista[i].primeiro;

					while (quarteirao != NULL)
					{
						aux = quarteirao->proximo;
						free (quarteirao);
						quarteirao = aux;
					}
				}

				free(lista);
				lista = NULL;
			}


	//------------------------- Insere um item na lista

			void insere(pCabeca lista, int inicial, int final, float probIncendio)
			{

				// Aloca o espaço para um item ser alocado
				pNos novo = (pNos) calloc (1, sizeof(nos));
				// O item recebe os valores que foram passados como parâmetro
				novo->destino = final;
				novo->probIncendio = probIncendio;
				novo->proximo = NULL;

				// O tamanho da lista referente ao item que será inserido é acrescido em um
				lista[inicial].tam++;

				// Se a lista está vazia insere na primeira posição
				if (lista[inicial].primeiro == NULL)
					lista[inicial].primeiro = novo;
				// Se não insere após o primeiro, respeitando a posição de que os item estão sempre em ordem crescente
				else
				{
					pNos aux = lista[inicial].primeiro;

					while (aux->proximo != NULL)
					{
						if (aux->proximo->destino > final)
							break;
						else
							aux = aux->proximo;
					}

					novo->proximo = aux->proximo;
					aux->proximo = novo;
				}
			}


	//------------------------- Pega os dados para inserir uma rua na lista de adjacências

			void insereRuas(pCabeca lista, int numRuas)
			{
				int inicial, final, i;
				float probIncendio;

				for (i=0; i<numRuas; i++)
				{
					// Os dados são pegos no formato da entrada do programa e inseridos na lista
					scanf("%d %d %f", &inicial, &final, &probIncendio);
					// Duas inserções pois as ruas são de mão dupla
					insere(lista, inicial, final, probIncendio);
					insere(lista, final, inicial, probIncendio);
				}
			}


	/*------------------------- Marca os nós onde existem bombeiros,
					no final remove aqueles que não podem ser alcançados
					por ter uma distância maior do que a mínima */

			void insereBombeiros(pCabeca lista, int numBombeiros, int numQuarteiroes, int distanciaMax, int saida, int chegada)
			{

				// O vetor 'menoresDistâncias' armazenará a distância de cada quarteirão para o bombeiro mais próximo
				int i, local;

				// O vetor é inicializado
				for (i=0; i<numQuarteiroes; i++)
					lista[i].elegivel = 0;

				// A cada inserção de um bombeiro o vetor 'menoresDistâncias' é atualizado
				for (i=0; i<numBombeiros; i++)
				{
					scanf("%d", &local);
					defineRotas(lista, numQuarteiroes, local, distanciaMax);
				}

				// Se a distância até a chegada para um corpo de bombeiros excede o máximo, não é possível concluir o trajeto
				if (lista[chegada].elegivel == 0)
					printf("-1\n");
				else
					maiorProbNaoIncendio (lista, numQuarteiroes, saida, chegada);
			}
