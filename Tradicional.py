import numpy as np
import time

def traditional_matrix_multiplication(A, B):
    n = len(A)
    C = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            for k in range(n):
                C[i][j] += A[i][k] * B[k][j]
    return C

# Tamaño de la matriz (potencia de 2)
n = 128
A = np.random.randint(0, 10, size=(n, n))
B = np.random.randint(0, 10, size=(n, n))

start = time.time()
C = traditional_matrix_multiplication(A, B)
end = time.time()

print(f"Tiempo de ejecución (Tradicional): {end - start:.6f} segundos")
