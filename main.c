#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Insertion Sort
void insertionSort(int V[], int n) {
    int i, j, aux1;
    for (i = 1; i < n; i++) {
        aux1 = V[i];
        for (j = i - 1; j >= 0 && V[j] > aux1; j--) {
            V[j + 1] = V[j];
        }
        V[j + 1] = aux1;
    }
}

// Selection Sort
void selectionSort(int V[], int n) {
    int i, j, menor, aux2;
    for (i = 0; i < n - 1; i++) {
        menor = i;
        for (j = i + 1; j < n; j++) {
            if (V[j] < V[menor]) {
                menor = j;
            }
        }
        aux2 = V[menor];
        V[menor] = V[i];
        V[i] = aux2;
    }
}

// Função para printar o array em um arquivo
void printarArray(int V[], int n, FILE *file) {
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", V[i]);
    }
    fprintf(file, "\n");
}

// Função para escrever o vetor ordenado em um arquivo de saída
int arquivoSaida(const char *filename, int V[], int n) {
    FILE *outputFile = fopen(filename, "w");
    if (outputFile == NULL) {
        perror("Erro ao criar o arquivo de saída");
        return 1;
    }
    printarArray(V, n, outputFile);
    fclose(outputFile);
    return 0;
}

// Main
int main() {
    FILE *file;
    int n, i;
    clock_t inicio, fim;
    double tempoInsertion, tempoSelection;

    // Para ler outros arquivos, alterar aqui:
    const char *arquivo = "num.1000.1.in"; 
    file = fopen(arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!");
        return 1;
    }

    fscanf(file, "%d", &n);
    int *V = (int *)malloc(n * sizeof(int));
    if (V == NULL) {
        printf("Erro na alocacao de memoria\n");
        fclose(file);
        return 1;
    }

    for (i = 0; i < n; i++) { // Ler o arquivo de entrada
        fscanf(file, "%d", &V[i]);
    }
    fclose(file);

    int *V_copy = (int *)malloc(n * sizeof(int));
    if (V_copy == NULL) {
        printf("Erro na alocacao de memoria\n");
        free(V);
        return 1;
    }

    for (i = 0; i < n; i++) {
        V_copy[i] = V[i];
    }

    // Tempo do Insertion Sort
    inicio = clock();
    insertionSort(V, n);
    fim = clock();
    tempoInsertion = ((double) (fim - inicio)) / CLOCKS_PER_SEC;

    printf("Array ordenado utilizando Insertion Sort: \n");
    printarArray(V, n, stdout);
    printf("\n");
    printf("Insertion Sort levou %f segundos para executar \n", tempoInsertion);

    // Tempo do Selection Sort
    inicio = clock();
    selectionSort(V_copy, n);
    fim = clock();
    tempoSelection = ((double) (fim - inicio)) / CLOCKS_PER_SEC;

    printf("Array ordenado utilizando Selection Sort: \n");
    printarArray(V_copy, n, stdout);
    printf("\n");
    printf("Selection Sort levou %f segundos para executar \n", tempoSelection);

    // Comparando Insertion Sort e Selection Sort
    if (tempoInsertion < tempoSelection) {
        printf("Insertion Sort foi mais rápido.\n");
    } else if (tempoInsertion > tempoSelection) {
        printf("Selection Sort foi mais rápido.\n");
    } else {
        printf("Ambos levaram o mesmo tempo.\n");
    }

    // Escreve o vetor ordenado por Insertion Sort em um arquivo de saída
    if (arquivoSaida("insertion_sort.txt", V, n) != 0) {
        free(V);
        free(V_copy);
        return 1; 
    }

    // Escreve o vetor ordenado por Selection Sort em um arquivo de saída
    if (arquivoSaida("selection_sort.txt", V_copy, n) != 0) {
        free(V);
        free(V_copy);
        return 1; 
    }

    free(V);
    free(V_copy);

    return 0;
}
