#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>
#include <math.h>
#include "algoritmos.h"

#define QTD_EXECUCOES 50  // Define a quantidade de execuções que serão realizadas

// Função para construir o nome do arquivo
void construirNomeArquivo(char *nome, char *ordenacao, int metodo, int tamanho) {
    char tipoPreenchimentoString[12];
    
    // Define o tipo de preenchimento com base no método
    if (metodo == 1) {
        strcpy(tipoPreenchimentoString, "aleatorio");
    } else if (metodo == 2) {
        strcpy(tipoPreenchimentoString, "crescente");
    } else {
        strcpy(tipoPreenchimentoString, "decrescente");
    }
    
    // Constrói o nome do arquivo com base no tipo de ordenação, método e tamanho
    sprintf(nome, "%s_%s_%d", ordenacao, tipoPreenchimentoString, tamanho);
}

// Função para calcular 3^n
int calcular_tamanho(int n) {
    int resultado = 1;
    
    // Calcula 3 elevado à potência n
    for (int i = 0; i < n; i++) {
        resultado *= 3;
    }
    
    return resultado;
}

// Função para preencher o array conforme o método escolhido
void preencher_array(int arr[], int n, int metodo) {
    switch (metodo) {
        case 1: // Aleatório
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % n; // Preenche o array com valores aleatórios entre 0 e n-1
            }
            break;
        case 2: // Crescente
            for (int i = 0; i < n; i++) { // Preenche o array com valores em ordem crescente
                arr[i] = i;
            }
            break;
        case 3: // Decrescente
            for (int i = 0; i < n; i++) { // Preenche o array com valores em ordem decrescente
                arr[i] = n - i - 1;
            }
            break;
        default:
            printf("Método inválido para preenchimento do array.\n");
            break;
    }
}

// Função para calcular o desvio padrão para valores do tipo double
double calcular_desvio_padrao(double valores[], int n, double media) {
    double soma = 0.0;
    
    // Calcula a soma dos quadrados das diferenças entre cada valor e a média
    for (int i = 0; i < n; i++) {
        soma += pow(valores[i] - media, 2);
    }
    
    // Retorna a raiz quadrada da variância (desvio padrão)
    return sqrt(soma / n);
}

// Função para calcular o desvio padrão para valores do tipo long long int convertidos para double
double calcular_desvio_padrao_ll(long long int valores[], int n, double media) {
    double soma = 0.0;
    
    // Calcula a soma dos quadrados das diferenças, convertendo valores para double
    for (int i = 0; i < n; i++) {
        soma += pow((double)valores[i] - media, 2); // Conversão explícita para double
    }
    
    // Retorna o desvio padrão
    return sqrt(soma / n);
}

int main() {
    // Tamanhos de vetor para os quais o algoritmo será executado (3^n)
    int tamanhos[] = {8, 9, 10, 11, 12, 13, 14, 15, 16, 17}; 
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]); // Calcula o número de tamanhos
    int metodo, algoritmo;
    
    srand(time(0)); // Inicializa o gerador de números aleatórios com base no tempo atual

    while (true) {
        // Menu de seleção para método de preenchimento e algoritmo de ordenação
        printf("\n--- MENU ---\n");
        printf("1. Método Aleatório\n");
        printf("2. Método Crescente\n");
        printf("3. Método Decrescente\n");
        printf("Escolha o método (1-3): ");
        scanf("%d", &metodo);

        printf("\nEscolha o Algoritmo de Ordenação:\n");
        printf("1. Ordenação por Inserção\n");
        printf("2. Ordenação por Seleção\n");
        printf("3. Ordenação por Intercalação (Merge Sort)\n");
        printf("4. Ordenação por Heap (Heap Sort)\n");
        printf("5. Quick Sort\n");
        printf("Escolha o algoritmo (1-5): ");
        scanf("%d", &algoritmo);

        // Iterar por cada tamanho de vetor (3^8 até 3^17)
        for (int i = 0; i < num_tamanhos; i++) {
            int n = calcular_tamanho(tamanhos[i]); // Calcula o tamanho do vetor
            printf("Gerando resultados para tamanho do vetor: 3^%d = %d\n", tamanhos[i], n);

            long long int media_trocas = 0, media_comparacoes = 0;
            double media_tempo = 0.0;

            // Arrays para armazenar os resultados das execuções
            double tempos[QTD_EXECUCOES];
            long long int trocas[QTD_EXECUCOES];
            long long int comparacoes[QTD_EXECUCOES];

            // Constrói o nome do arquivo para salvar os resultados
            char nome_arquivo[50];
            construirNomeArquivo(nome_arquivo, 
                                 (algoritmo == 1 ? "insercao" : algoritmo == 2 ? "selecao" : 
                                  algoritmo == 3 ? "merge" : algoritmo == 4 ? "heap" : "quick"), 
                                 metodo, n);

            // Abre o arquivo para escrever os resultados
            FILE *arquivo = fopen(nome_arquivo, "a");
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
                continue;
            }

            // Executar o algoritmo QTD_EXECUCOES vezes
            for (int exec = 0; exec < QTD_EXECUCOES; exec++) {
                // Alocação dinâmica do vetor principal
                int *arr = (int*)malloc(n * sizeof(int));
                if (arr == NULL) {
                    printf("Erro ao alocar memória para o vetor de tamanho %d. Pulando para o próximo tamanho.\n", n);
                    continue;
                }

                // Preenche o array com base no método escolhido
                preencher_array(arr, n, metodo);

                long long int trocas_exec = 0, comparacoes_exec = 0;
                struct timeval inicio, fim;

                // Inicia a contagem de tempo
                gettimeofday(&inicio, NULL);
                switch (algoritmo) {
                    case 1:
                        ordenacao_insercao(arr, n, &trocas_exec, &comparacoes_exec); // Algoritmo Insertion Sort
                        break;
                    case 2:
                        ordenacao_selecao(arr, n, &trocas_exec, &comparacoes_exec); // Algoritmo Selection Sort
                        break;
                    case 3:
                        ordenacao_merge(arr, 0, n - 1, &trocas_exec, &comparacoes_exec); // Merge Sort
                        break;
                    case 4:
                        ordenacao_heap(arr, n, &trocas_exec, &comparacoes_exec); // Heap Sort
                        break;
                    case 5:
                        ordenacao_quick_aleatorio(arr, 0, n - 1, &trocas_exec, &comparacoes_exec); // Quick Sort com pivô aleatório
                        break;
                    default:
                        printf("Opção de algoritmo inválida.\n");
                        free(arr);
                        continue;
                }
                gettimeofday(&fim, NULL); // Fim da contagem de tempo

                // Calcula o tempo de execução em segundos
                double tempo_execucao = (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1000000.0;

                // Armazena os resultados da execução atual
                trocas[exec] = trocas_exec;
                comparacoes[exec] = comparacoes_exec;
                tempos[exec] = tempo_execucao;

                media_trocas += trocas_exec;
                media_comparacoes += comparacoes_exec;
                media_tempo += tempo_execucao;

                // Escreve os resultados da execução no arquivo
                fprintf(arquivo, "Execucao %d\n", exec + 1);
                fprintf(arquivo, "Tempo de Execução (segundos): %.6f ", tempo_execucao);
                fprintf(arquivo, "Comparações: %lld ", comparacoes_exec);
                fprintf(arquivo, "Trocas: %lld\n\n", trocas_exec);

                // Libera a memória do array após cada execução
                free(arr);
            }

            // Calcula as médias dos resultados
            media_trocas /= QTD_EXECUCOES;
            media_comparacoes /= QTD_EXECUCOES;
            media_tempo /= QTD_EXECUCOES;

            // Calcula os valores de desvio padrão para o tempo de execução, número de trocas e comparações.

            double desvio_tempo = calcular_desvio_padrao(tempos, QTD_EXECUCOES, media_tempo);
            double desvio_trocas = calcular_desvio_padrao_ll(trocas, QTD_EXECUCOES, media_trocas);
            double desvio_comparacoes = calcular_desvio_padrao_ll(comparacoes, QTD_EXECUCOES, media_comparacoes);

            // Escreve as médias e desvios padrões no arquivo
            fprintf(arquivo, "Média do tempo de Execução (segundos): %.6f\n", media_tempo);
            fprintf(arquivo, "Desvio Padrão de Tempo (segundos): %.6f\n", desvio_tempo);
            fprintf(arquivo, "Média de Comparações: %lld\n", media_comparacoes);
            fprintf(arquivo, "Desvio Padrão de Comparações: %.6f\n", desvio_comparacoes);
            fprintf(arquivo, "Média de Trocas: %lld\n", media_trocas);
            fprintf(arquivo, "Desvio Padrão de Trocas: %.6f\n", desvio_trocas);

            // Fecha o arquivo após salvar os resultados
            fclose(arquivo);
        }
    }
    return 0;
}

