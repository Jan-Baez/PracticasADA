#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 256

int **allocate_matrix() {
    int **matrix = malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
        matrix[i] = calloc(N, sizeof(int)); // IMPORTANTE: Inicializamos en 0
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

void dac_recursive(int **A, int **B, int **C, int rowA, int colA, int rowB, int colB, int rowC, int colC, int size) {
    if (size == 1) {
        C[rowC][colC] += A[rowA][colA] * B[rowB][colB];
        return;
    }

    int half = size / 2;

    dac_recursive(A, B, C, rowA, colA, rowB, colB, rowC, colC, half);
    dac_recursive(A, B, C, rowA, colA + half, rowB + half, colB, rowC, colC, half);

    dac_recursive(A, B, C, rowA, colA, rowB, colB + half, rowC, colC + half, half);
    dac_recursive(A, B, C, rowA, colA + half, rowB + half, colB + half, rowC, colC + half, half);

    dac_recursive(A, B, C, rowA + half, colA, rowB, colB, rowC + half, colC, half);
    dac_recursive(A, B, C, rowA + half, colA + half, rowB + half, colB, rowC + half, colC, half);

    dac_recursive(A, B, C, rowA + half, colA, rowB, colB + half, rowC + half, colC + half, half);
    dac_recursive(A, B, C, rowA + half, colA + half, rowB + half, colB + half, rowC + half, colC + half, half);
}

int main() {
    srand(time(NULL));

    int **A = allocate_matrix();
    int **B = allocate_matrix();
    int **C = allocate_matrix();

    fill_matrix(A);
    fill_matrix(B);

    clock_t start = clock();
    dac_recursive(A, B, C, 0, 0, 0, 0, 0, 0, N);
    clock_t end = clock();

    printf("Tiempo de multiplicación DaC: %.2f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    return 0;
}



