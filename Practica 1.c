#include <stdio.h>
#include <stdbool.h>

// Función auxiliar para invertir el número
int invertirNumero(int numero) {
    int inverso = 0;
    while (numero > 0) {
        int digito = numero % 10;
        inverso = inverso * 10 + digito;
        numero /= 10;
    }
    return inverso;
}

// Función que verifica si un número es palíndromo
bool esPalindromo(int numero) {
    // Los números negativos no se consideran palíndromos
    if (numero < 0) {
        return false;
    }
    
    // Se invierte el número y se compara con el original
    return (numero == invertirNumero(numero));
}

int main(void) {
    int num;
    
    printf("Ingresa un número entero: ");
    scanf("%d", &num);
    
    if (esPalindromo(num)) {
        printf("El número %d es palíndromo.\n", num);
    } else {
        printf("El número %d no es palíndromo.\n", num);
    }
    
    return 0;
}
