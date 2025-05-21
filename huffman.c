#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARACTERES 256

// Nodo del árbol Huffman
typedef struct NodoHuff {
    char simbolo;
    int freq;
    struct NodoHuff *izq, *der;
} NodoHuff;

// MinHeap para construir el árbol
typedef struct {
    int cantidad;
    NodoHuff* elementos[CARACTERES];
} MonticuloMinimo;

char* codigosHuff[CARACTERES];  // Almacena códigos Huffman por caracter
int bitsOriginal = 0;
int bitsComprimidos = 0;

// Crear nuevo nodo
NodoHuff* nuevoNodo(char simbolo, int frecuencia) {
    NodoHuff* nodo = (NodoHuff*)malloc(sizeof(NodoHuff));
    nodo->simbolo = simbolo;
    nodo->freq = frecuencia;
    nodo->izq = nodo->der = NULL;
    return nodo;
}

// Intercambiar dos nodos en el montículo
void intercambiar(NodoHuff** a, NodoHuff** b) {
    NodoHuff* temp = *a;
    *a = *b;
    *b = temp;
}

// Reajustar montículo mínimo desde índice i
void heapify(MonticuloMinimo* monticulo, int i) {
    int menor = i;
    int izquierda = 2*i + 1;
    int derecha = 2*i + 2;

    if (izquierda < monticulo->cantidad && monticulo->elementos[izquierda]->freq < monticulo->elementos[menor]->freq)
        menor = izquierda;
    if (derecha < monticulo->cantidad && monticulo->elementos[derecha]->freq < monticulo->elementos[menor]->freq)
        menor = derecha;

    if (menor != i) {
        intercambiar(&monticulo->elementos[i], &monticulo->elementos[menor]);
        heapify(monticulo, menor);
    }
}

// Extraer el nodo con menor frecuencia
NodoHuff* extraerMinimo(MonticuloMinimo* monticulo) {
    NodoHuff* temp = monticulo->elementos[0];
    monticulo->elementos[0] = monticulo->elementos[--monticulo->cantidad];
    heapify(monticulo, 0);
    return temp;
}

// Insertar un nodo en el montículo
void insertarMonticulo(MonticuloMinimo* monticulo, NodoHuff* nodo) {
    int i = monticulo->cantidad++;
    while (i && nodo->freq < monticulo->elementos[(i - 1) / 2]->freq) {
        monticulo->elementos[i] = monticulo->elementos[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    monticulo->elementos[i] = nodo;
}

// Crear y construir montículo con frecuencias dadas
MonticuloMinimo* crearMonticulo(int frecuencias[]) {
    MonticuloMinimo* monticulo = (MonticuloMinimo*)malloc(sizeof(MonticuloMinimo));
    monticulo->cantidad = 0;
    for (int i = 0; i < CARACTERES; i++) {
        if (frecuencias[i] > 0) {
            monticulo->elementos[monticulo->cantidad++] = nuevoNodo(i, frecuencias[i]);
        }
    }
    for (int i = (monticulo->cantidad / 2) - 1; i >= 0; i--) {
        heapify(monticulo, i);
    }
    return monticulo;
}

// Construir árbol de Huffman a partir de frecuencias
NodoHuff* construirArbolHuff(int frecuencias[]) {
    MonticuloMinimo* monticulo = crearMonticulo(frecuencias);
    while (monticulo->cantidad > 1) {
        NodoHuff* izquierdo = extraerMinimo(monticulo);
        NodoHuff* derecho = extraerMinimo(monticulo);

        NodoHuff* nuevo = nuevoNodo('$', izquierdo->freq + derecho->freq);
        nuevo->izq = izquierdo;
        nuevo->der = derecho;

        insertarMonticulo(monticulo, nuevo);
    }
    return extraerMinimo(monticulo);
}

// Generar códigos Huffman recursivamente
void generarCodigos(NodoHuff* raiz, char* arreglo, int tope) {
    if (raiz->izq) {
        arreglo[tope] = '0';
        generarCodigos(raiz->izq, arreglo, tope + 1);
    }
    if (raiz->der) {
        arreglo[tope] = '1';
        generarCodigos(raiz->der, arreglo, tope + 1);
    }
    if (!raiz->izq && !raiz->der) {
        arreglo[tope] = '\0';
        codigosHuff[(unsigned char)raiz->simbolo] = strdup(arreglo);
    }
}

// Codificar archivo de texto
void codificarArchivo(const char* archivoEntrada, const char* archivoSalida) {
    FILE* entrada = fopen(archivoEntrada, "r");
    FILE* salida = fopen(archivoSalida, "w");
    int caracter;
    while ((caracter = fgetc(entrada)) != EOF) {
        bitsOriginal += 8;
        if (codigosHuff[caracter]) {
            fputs(codigosHuff[caracter], salida);
            bitsComprimidos += strlen(codigosHuff[caracter]);
        }
    }
    fclose(entrada);
    fclose(salida);
}

// Decodificar archivo usando árbol Huffman
void decodificarArchivo(const char* archivoCodificado, NodoHuff* raiz) {
    FILE* entrada = fopen(archivoCodificado, "r");
    printf("\n[Texto decodificado]: ");
    NodoHuff* actual = raiz;
    int caracter;
    while ((caracter = fgetc(entrada)) != EOF) {
        if (caracter == '0') actual = actual->izq;
        else if (caracter == '1') actual = actual->der;

        if (!actual->izq && !actual->der) {
            putchar(actual->simbolo);
            actual = raiz;
        }
    }
    printf("\n");
    fclose(entrada);
}

int main() {
    FILE* archivo = fopen("entrada.txt", "r");
    if (!archivo) {
        printf("Error al abrir archivo entrada.txt\n");
        return 1;
    }

    int frecuencias[CARACTERES] = {0};
    int c;
    while ((c = fgetc(archivo)) != EOF) {
        frecuencias[c]++;
    }
    fclose(archivo);

    NodoHuff* raiz = construirArbolHuff(frecuencias);

    char arregloCodigos[100];
    generarCodigos(raiz, arregloCodigos, 0);

    codificarArchivo("entrada.txt", "codificado.txt");

    printf("Bits en original: %d\n", bitsOriginal);
    printf("Bits en comprimido: %d\n", bitsComprimidos);
    printf("Porcentaje de compresión: %.2f%%\n", 100.0 * bitsComprimidos / bitsOriginal);

    decodificarArchivo("codificado.txt", raiz);

    return 0;
}
