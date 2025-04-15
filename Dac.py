import numpy as np
import time

def add_matrix(A, B):
    n = len(A)
    return [[A[i][j] + B[i][j] for j in range(n)] for i in range(n)]

def sub_matrix(A, B):
    n = len(A)
    return [[A[i][j] - B[i][j] for j in range(n)] for i in range(n)]

def split_matrix(M):
    n = len(M)
    mid = n // 2
    A11 = [row[:mid] for row in M[:mid]]
    A12 = [row[mid:] for row in M[:mid]]
    A21 = [row[:mid] for row in M[mid:]]
    A22 = [row[mid:] for row in M[mid:]]
    return A11, A12, A21, A22

def dac_matrix_multiplication(A, B):
    n = len(A)
    if n == 1:
        return [[A[0][0] * B[0][0]]]
    
    A11, A12, A21, A22 = split_matrix(A)
    B11, B12, B21, B22 = split_matrix(B)

    M1 = dac_matrix_multiplication(A11, B11)
    M2 = dac_matrix_multiplication(A12, B21)
    M3 = dac_matrix_multiplication(A11, B12)
    M4 = dac_matrix_multiplication(A12, B22)
    M5 = dac_matrix_multiplication(A21, B11)
    M6 = dac_matrix_multiplication(A22, B21)
    M7 = dac_matrix_multiplication(A21, B12)
    M8 = dac_matrix_multiplication(A22, B22)

    C11 = add_matrix(M1, M2)
    C12 = add_matrix(M3, M4)
    C21 = add_matrix(M5, M6)
    C22 = add_matrix(M7, M8)

    # Combinar submatrices
    new_matrix = []
    for i in range(n // 2):
        new_matrix.append(C11[i] + C12[i])
    for i in range(n // 2):
        new_matrix.append(C21[i] + C22[i])
    return new_matrix

# Tamaño de la matriz (potencia de 2)
n = 128
A = np.random.randint(0, 10, size=(n, n))
B = np.random.randint(0, 10, size=(n, n))

start = time.time()
C = dac_matrix_multiplication(A, B)
end = time.time()

print(f"Tiempo de ejecución (Divide and Conquer): {end - start:.6f} segundos")
