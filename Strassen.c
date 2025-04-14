#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 256

int **allocate_matrix(int size) {
    int **matrix = malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
        matrix[i] = malloc(size * sizeof(int));
    return matrix;
}

void free_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}

void fill_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = rand() % 10;
}

void add(int **A, int **B, int **result, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = A[i][j] + B[i][j];
}

void sub(int **A, int **B, int **result, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = A[i][j] - B[i][j];
}

void strassen(int **A, int **B, int **C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;
    int **A11 = allocate_matrix(newSize);
    int **A12 = allocate_matrix(newSize);
    int **A21 = allocate_matrix(newSize);
    int **A22 = allocate_matrix(newSize);
    int **B11 = allocate_matrix(newSize);
    int **B12 = allocate_matrix(newSize);
    int **B21 = allocate_matrix(newSize);
    int **B22 = allocate_matrix(newSize);
    int **C11 = allocate_matrix(newSize);
    int **C12 = allocate_matrix(newSize);
    int **C21 = allocate_matrix(newSize);
    int **C22 = allocate_matrix(newSize);
    int **M1 = allocate_matrix(newSize);
    int **M2 = allocate_matrix(newSize);
    int **M3 = allocate_matrix(newSize);
    int **M4 = allocate_matrix(newSize);
    int **M5 = allocate_matrix(newSize);
    int **M6 = allocate_matrix(newSize);
    int **M7 = allocate_matrix(newSize);
    int **A_result = allocate_matrix(newSize);
    int **B_result = allocate_matrix(newSize);

    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }

    add(A11, A22, A_result, newSize); add(B11, B22, B_result, newSize); strassen(A_result, B_result, M1, newSize);
    add(A21, A22, A_result, newSize); strassen(A_result, B11, M2, newSize);
    sub(B12, B22, B_result, newSize); strassen(A11, B_result, M3, newSize);
    sub(B21, B11, B_result, newSize); strassen(A22, B_result, M4, newSize);
    add(A11, A12, A_result, newSize); strassen(A_result, B22, M5, newSize);
    sub(A21, A11, A_result, newSize); add(B11, B12, B_result, newSize); strassen(A_result, B_result, M6, newSize);
    sub(A12, A22, A_result, newSize); add(B21, B22, B_result, newSize); strassen(A_result, B_result, M7, newSize);

    add(M1, M4, A_result, newSize); sub(A_result, M5, B_result, newSize); add(B_result, M7, C11, newSize);
    add(M3, M5, C12, newSize);
    add(M2, M4, C21, newSize);
    sub(M1, M2, A_result, newSize); add(A_result, M3, B_result, newSize); add(B_result, M6, C22, newSize);

    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }

    free_matrix(A11, newSize); free_matrix(A12, newSize); free_matrix(A21, newSize); free_matrix(A22, newSize);
    free_matrix(B11, newSize); free_matrix(B12, newSize); free_matrix(B21, newSize); free_matrix(B22, newSize);
    free_matrix(C11, newSize); free_matrix(C12, newSize); free_matrix(C21, newSize); free_matrix(C22, newSize);
    free_matrix(M1, newSize);  free_matrix(M2, newSize);  free_matrix(M3, newSize);  free_matrix(M4, newSize);
    free_matrix(M5, newSize);  free_matrix(M6, newSize);  free_matrix(M7, newSize);
    free_matrix(A_result, newSize); free_matrix(B_result, newSize);
}

int main() {
    srand(time(NULL));
    int **A = allocate_matrix(N);
    int **B = allocate_matrix(N);
    int **C = allocate_matrix(N);
    fill_matrix(A, N);
    fill_matrix(B, N);

    clock_t start = clock();
    strassen(A, B, C, N);
    clock_t end = clock();

    printf("Tiempo de multiplicación de Strassen: %.2f segundos\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);
    return 0;
}
