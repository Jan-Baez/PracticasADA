#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 256

int **allocate_matrix() {
    int **matrix = malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
        matrix[i] = malloc(N * sizeof(int));
    return matrix;
}

void free_matrix(int **matrix) {
    for (int i = 0; i < N; i++)
        free(matrix[i]);
    free(matrix);
}

void fill_matrix(int **matrix) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = rand() % 10;
}

void traditional_multiply(int **A, int **B, int **C) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

int main() {
    srand(time(NULL));
    int **A = allocate_matrix();
    int **B = allocate_matrix();
    int **C = allocate_matrix();
    fill_matrix(A);
    fill_matrix(B);

    clock_t start = clock();
    traditional_multiply(A, B, C);
    clock_t end = clock();

    printf("Tiempo de multiplicación tradicional: %.2f segundos\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    return 0;
}


