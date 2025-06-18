#include <stdio.h>

#define TOTAL_ITEMS 4
#define LIMITE_PESO 4

int main() {
    int peso[TOTAL_ITEMS] = {1, 1, 3, 4}; // iPhone, guitarra, laptop, estéreo
    int beneficio[TOTAL_ITEMS] = {2000, 1500, 2000, 3000};
    char* articulos[TOTAL_ITEMS] = {"iPhone", "Guitarra", "Laptop", "Estéreo"};

    int tabla[TOTAL_ITEMS + 1][LIMITE_PESO + 1];

    // Construcción de la tabla dinámica
    for (int item = 0; item <= TOTAL_ITEMS; item++) {
        for (int cap = 0; cap <= LIMITE_PESO; cap++) {
            if (item == 0 || cap == 0) {
                tabla[item][cap] = 0;
            } else if (peso[item - 1] <= cap) {
                int con_item = beneficio[item - 1] + tabla[item - 1][cap - peso[item - 1]];
                int sin_item = tabla[item - 1][cap];
                tabla[item][cap] = (con_item > sin_item) ? con_item : sin_item;
            } else {
                tabla[item][cap] = tabla[item - 1][cap];
            }
        }
    }

    // Resultado final
    printf("Máximo valor posible en la mochila: $%d\n", tabla[TOTAL_ITEMS][LIMITE_PESO]);

    // Rastreo de los artículos incluidos
    int capacidad = LIMITE_PESO;
    printf("Artículos seleccionados para la mochila:\n");
    for (int i = TOTAL_ITEMS; i > 0 && capacidad > 0; i--) {
        if (tabla[i][capacidad] != tabla[i - 1][capacidad]) {
            printf("-> %s\n", articulos[i - 1]);
            capacidad -= peso[i - 1];
        }
    }

    return 0;
}


