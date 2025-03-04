#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int divide(int dividend, int divisor) {
    if (dividend == INT_MIN && divisor == -1) {
        return INT_MAX; // Manejo de desbordamiento
    }
    
    int negativo = (dividend < 0) ^ (divisor < 0) ? -1 : 1; // Determinar el signo del resultado
    
    long long a = llabs((long long)dividend);
    long long b = llabs((long long)divisor);
    long long resultado = 0;
    
    while (a >= b) {
        long long temp = b, multiplo = 1;
        while (a >= (temp << 1)) {
            temp <<= 1;
            multiplo <<= 1;
        }
        a -= temp;
        resultado += multiplo;
    }
    
    return negativo * resultado;
}

int main() {
    int dividend, divisor;
    printf("Ingrese el dividendo: ");
    scanf("%d", &dividend);
    printf("Ingrese el divisor: ");
    scanf("%d", &divisor);
    
    if (divisor == 0) {
        printf("Error: División por cero no permitida.\n");
        return 1;
    }
    
    int resultado = divide(dividend, divisor);
    printf("Resultado: %d\n", resultado);
    
    return 0;
}
