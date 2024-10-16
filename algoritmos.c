#include "algoritmos.h"
#include <stdlib.h>  

// Função auxiliar para troca de elementos e contagem de trocas
// A função 'trocar' troca os valores de duas posições no array e incrementa o contador de trocas
void trocar(int *a, int *b, long long int *trocas) {
    int temp = *a;
    *a = *b;
    *b = temp;
    (*trocas)++;
}

/*-------------------- INSERTION SORT -------------------- */

// Função de ordenação por inserção
// Percorre o array, insere cada elemento na posição correta, 
// incrementa o número de comparações e trocas quando necessário
void ordenacao_insercao(int arr[], int n, long long int *trocas, long long int *comparacoes) {
    for (int i = 1; i < n; i++) {
        int chave = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > chave) {
            (*comparacoes)++;
            arr[j + 1] = arr[j];  // Apenas deslocamento
            j--;
        }
        (*comparacoes)++;  // Para a comparação que falhou no while
        arr[j + 1] = chave;  // Coloca a chave na posição correta
        (*trocas)++;  // Conta como uma troca aqui
    }
}


/*-------------------- SELECTION SORT -------------------- */

// Função de ordenação por seleção
// A cada iteração, encontra o menor elemento e o troca de lugar com o primeiro elemento não ordenado
void ordenacao_selecao(int arr[], int n, long long int *trocas, long long int *comparacoes) {
    for (int i = 0; i < n - 1; i++) {
        int indice_minimo = i;

        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (arr[j] < arr[indice_minimo]) {
                indice_minimo = j;
            }
        }

        if (indice_minimo != i) {
            trocar(&arr[indice_minimo], &arr[i], trocas);  // Troca apenas se necessário
        }
    }
}



/*-------------------- MERGE SORT -------------------- */

// Função auxiliar que faz o merge de dois subarrays
// Durante o merge, conta comparações e trocas
void merge(int arr[], int l, int m, int r, long long int *trocas, long long int *comparacoes) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Cria arrays temporários para armazenar os subarrays
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    // Copia os dados para os arrays temporários L e R
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    // Mescla os subarrays L e R de volta ao array principal
    while (i < n1 && j < n2) {
        (*comparacoes)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        (*trocas)++;
        k++;
    }

    // Copia os elementos restantes de L, se houver
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        (*trocas)++;
    }

    // Copia os elementos restantes de R, se houver
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        (*trocas)++;
    }

    // Libera a memória alocada para os arrays temporários
    free(L);
    free(R);
}

// Função recursiva que divide o array e chama a função 'merge' para mesclar os subarrays
void ordenacao_merge(int arr[], int l, int r, long long int *trocas, long long int *comparacoes) {
    if (l < r) {
        int m = l + (r - l) / 2;
        ordenacao_merge(arr, l, m, trocas, comparacoes);
        ordenacao_merge(arr, m + 1, r, trocas, comparacoes);
        merge(arr, l, m, r, trocas, comparacoes);
    }
}


/*-------------------- HEAP SORT -------------------- */

// Função auxiliar 'heapify' para reorganizar o array como uma heap (árvore binária)
void heapify(int arr[], int n, int i, long long int *trocas, long long int *comparacoes) {
    int maior = i;   // Inicializa o maior como raiz
    int esq = 2 * i + 1;   // Filho à esquerda
    int dir = 2 * i + 2;   // Filho à direita

    // Se o filho da esquerda for maior que a raiz
    if (esq < n && arr[esq] > arr[maior]) {
        maior = esq;
        (*comparacoes)++;
    }
    // Se o filho da direita for maior que a raiz
    if (dir < n && arr[dir] > arr[maior]) {
        maior = dir;
        (*comparacoes)++;
    }

    // Se o maior não for a raiz, troca e continua heapify
    if (maior != i) {
        trocar(&arr[i], &arr[maior], trocas);
        heapify(arr, n, maior, trocas, comparacoes);
    }
}

// Função de ordenação por heap
// Cria uma heap a partir do array e realiza a ordenação trocando elementos
void ordenacao_heap(int arr[], int n, long long int *trocas, long long int *comparacoes) {
    // Constrói a heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, trocas, comparacoes);
    }
    // Extrai um por um os elementos da heap
    for (int i = n - 1; i > 0; i--) {
        trocar(&arr[0], &arr[i], trocas);  // Move o maior elemento para o final
        heapify(arr, i, 0, trocas, comparacoes);  // Chama heapify na heap reduzida
    }
}


/*-------------------- QUICK SORT -------------------- */

// Função que particiona o array com base em um pivô
// Organiza os elementos menores que o pivô à esquerda e os maiores à direita
int particionar(int arr[], int low, int high, long long int *trocas, long long int *comparacoes) {
    int pivot = arr[high];  // Seleciona o último elemento como pivô
    int i = low - 1;        // Índice do menor elemento

    for (int j = low; j <= high - 1; j++) {
        if (++(*comparacoes) && arr[j] < pivot) {
            i++;
            trocar(&arr[i], &arr[j], trocas);
        }
    }

    trocar(&arr[i + 1], &arr[high], trocas);  // Coloca o pivô na posição correta
    return (i + 1);  // Retorna o índice do pivô
}


// Função para selecionar o pivô aleatoriamente e chamar a função de partição
int particionar_com_pivo_aleatorio(int arr[], int low, int high, long long int *trocas, long long int *comparacoes) {
    int random_pivot = low + rand() % (high - low + 1);  // Seleciona o pivô aleatoriamente
    trocar(&arr[random_pivot], &arr[high], trocas);  // Coloca o pivô no final
    return particionar(arr, low, high, trocas, comparacoes);  // Chama a função de partição
}

// Função de Quick Sort com pivô aleatório
// Chama recursivamente a função de partição e ordena os subarrays
void ordenacao_quick_aleatorio(int arr[], int low, int high, long long int *trocas, long long int *comparacoes) {
    while (low < high) {
        int pi = particionar_com_pivo_aleatorio(arr, low, high, trocas, comparacoes);

        // Ordena o menor subarray primeiro para otimizar a recursão
        if (pi - low < high - pi) {
            ordenacao_quick_aleatorio(arr, low, pi - 1, trocas, comparacoes);
            low = pi + 1;  // Continua com o subarray maior
        } else {
            ordenacao_quick_aleatorio(arr, pi + 1, high, trocas, comparacoes);
            high = pi - 1;  // Continua com o subarray menor
        }
    }
}

