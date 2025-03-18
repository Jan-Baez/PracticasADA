#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int sumOfChemistry(int* skill, int n) {
    // Ordenamos el array
    qsort(skill, n, sizeof(int), compare);

    int totalSum = skill[0] + skill[n - 1];
    int sumChemistry = 0;

    // Formamos los equipos
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        int teamSum = skill[i] + skill[j];

        // Si no se cumple la condición de suma total de cada equipo, retornamos -1
        if (teamSum != totalSum) {
            return -1;
        }

        // Calculamos la química del equipo y la sumamos
        sumChemistry += skill[i] * skill[j];
    }

    return sumChemistry;
}

int main() {
    int skill[100];  // Definimos un tamaño máximo para las habilidades
    int n = 0;
    char line[256];

    printf("Ingrese las habilidades de los jugadores:\n");

    // Leer la línea completa de entrada
    fgets(line, sizeof(line), stdin);

    // Procesar la línea para extraer los números
    char *token = strtok(line, " \n");  // Separar por espacios y saltos de línea
    while (token != NULL) {
        skill[n++] = atoi(token);  // Convertir el token a entero y agregarlo al array
        token = strtok(NULL, " \n");  // Obtener el siguiente número
    }

    // Si el número de jugadores no es par, no es posible formar equipos
    if (n % 2 != 0) {
        printf("-1\n");
        return 0;
    }

    // Llamar a la función para calcular la química
    printf("%d\n", sumOfChemistry(skill, n));

    return 0;
}
   