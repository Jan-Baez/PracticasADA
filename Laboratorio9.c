#include <stdio.h>

// Función para calcular el agua acumulada entre las alturas
int calcularAgua(int* elevaciones, int tam) {
    if (tam < 3) return 0;

    int inicio = 0;
    int fin = tam - 1;
    int maxIzq = 0, maxDer = 0;
    int aguaTotal = 0;

    while (inicio < fin) {
        if (elevaciones[inicio] < elevaciones[fin]) {
            if (elevaciones[inicio] >= maxIzq) {
                maxIzq = elevaciones[inicio];
            } else {
                aguaTotal += maxIzq - elevaciones[inicio];
            }
            inicio++;
        } else {
            if (elevaciones[fin] >= maxDer) {
                maxDer = elevaciones[fin];
            } else {
                aguaTotal += maxDer - elevaciones[fin];
            }
            fin--;
        }
    }

    return aguaTotal;
}

int main() {
    int cantidad;
    printf("¿Cuántas posiciones deseas ingresar? ");
    scanf("%d", &cantidad);

    if (cantidad <= 0) {
        printf("Cantidad no válida. Intenta con un número mayor a cero.\n");
        return 1;
    }

    int barras[cantidad];
    printf("Introduce los valores de elevación para cada posición:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("Posición %d: ", i + 1);
        scanf("%d", &barras[i]);
    }

    int resultado = calcularAgua(barras, cantidad);
    printf("Resultado: Se pueden almacenar %d unidades de agua.\n", resultado);

    return 0;
}

