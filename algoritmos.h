#ifndef ALGORITMOS_H
#define ALGORITMOS_H

// Definição da estrutura para armazenar métricas
typedef struct {
    long long comparacoes;  // Número de comparações realizadas
    long long trocas;       // Número de trocas realizadas
    double tempo;           // Tempo de execução do algoritmo
} Metricas;

// Declaração das funções de algoritmos de ordenação
void ordenacao_insercao(int arr[], int n, long long int *trocas, long long int *comparacoes);
void ordenacao_selecao(int arr[], int n, long long int *trocas, long long int *comparacoes);
void ordenacao_merge(int arr[], int l, int r, long long int *trocas, long long int *comparacoes);
void ordenacao_heap(int arr[], int n, long long int *trocas, long long int *comparacoes);
void ordenacao_quick_aleatorio(int arr[], int low, int high, long long int *trocas, long long int *comparacoes);

// Declaração da função preencher_array
void preencher_array(int arr[], int n, int metodo);

#endif // ALGORITMOS_H
