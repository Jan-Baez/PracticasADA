#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mapeo de dígitos a letras (según el teclado de un teléfono)
const char* mapping[] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

// Función recursiva que genera las combinaciones posibles
void backtrack(const char* digits, int index, char* current, char** result, int* returnSize) {
    // Caso base: cuando hemos recorrido todos los dígitos
    if (index == strlen(digits)) {
        result[*returnSize] = (char*)malloc(strlen(current) + 1);
        strcpy(result[*returnSize], current);
        (*returnSize)++;
        return;
    }

    int digit = digits[index] - '0';  // Convertir el carácter a su valor numérico
    const char* letters = mapping[digit]; // Obtener las letras correspondientes a ese dígito

    // Iterar sobre las letras correspondientes al dígito actual
    for (int i = 0; letters[i] != '\0'; i++) {
        current[index] = letters[i];  // Asignar la letra al índice correspondiente
        backtrack(digits, index + 1, current, result, returnSize); // Llamada recursiva
    }
}

// Función principal que prepara y devuelve las combinaciones posibles
char** letterCombinations(const char* digits, int* returnSize) {
    if (!digits || strlen(digits) == 0) {
        *returnSize = 0;
        return NULL;  // No hay combinaciones si no se pasan dígitos
    }

    // Calcular el número máximo de combinaciones posibles
    int maxCombinations = 1;
    for (int i = 0; digits[i] != '\0'; i++) {
        int digit = digits[i] - '0';
        maxCombinations *= strlen(mapping[digit]); // Multiplicar por el número de letras posibles por cada dígito
    }

    // Reservar memoria para almacenar todas las combinaciones
    char** result = (char**)malloc(maxCombinations * sizeof(char*));
    char current[strlen(digits) + 1];
    current[strlen(digits)] = '\0';  // Inicializar la cadena con un valor nulo

    *returnSize = 0;
    backtrack(digits, 0, current, result, returnSize);  // Iniciar el proceso recursivo

    return result;
}

int main() {
    char digits[6];  // Ajuste para permitir hasta 5 dígitos (más el carácter nulo)
    printf("Ingrese los dígitos (de 2 a 9): ");
    scanf("%5s", digits);  // Limitar la entrada a 5 caracteres

    int returnSize = 0;
    char** result = letterCombinations(digits, &returnSize);

    printf("Combinaciones posibles:\n");
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", result[i]);
        free(result[i]);  // Liberar la memoria de cada combinación
    }
    free(result);  // Liberar la memoria de la lista de resultados

    return 0;
}
