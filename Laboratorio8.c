#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 100003

// Estructura para caché hash
typedef struct CacheNode {
    char clave[61];
    bool resultado;
    struct CacheNode* siguiente;
} CacheNode;

CacheNode* tablaCache[TABLE_SIZE];

// Función de hash simple
unsigned int calcularHash(const char* clave) {
    unsigned int valor = 0;
    while (*clave) {
        valor = (valor * 33 + *clave++) % TABLE_SIZE;
    }
    return valor;
}

// Buscar en cache
bool buscarCache(const char* clave, bool* encontrado) {
    unsigned int indice = calcularHash(clave);
    CacheNode* actual = tablaCache[indice];
    while (actual) {
        if (strcmp(actual->clave, clave) == 0) {
            *encontrado = true;
            return actual->resultado;
        }
        actual = actual->siguiente;
    }
    *encontrado = false;
    return false;
}

// Guardar en cache
void guardarCache(const char* clave, bool valor) {
    unsigned int indice = calcularHash(clave);
    CacheNode* nuevo = malloc(sizeof(CacheNode));
    strcpy(nuevo->clave, clave);
    nuevo->resultado = valor;
    nuevo->siguiente = tablaCache[indice];
    tablaCache[indice] = nuevo;
}

// Verifica si s2 es una versión scramble de s1
bool esScramble(const char* a, const char* b) {
    int longitud = strlen(a);
    if (strcmp(a, b) == 0) return true;
    if (longitud <= 1) return false;

    char claveCache[61];
    snprintf(claveCache, sizeof(claveCache), "%s|%s", a, b);
    bool encontrado;
    bool resultadoPrevio = buscarCache(claveCache, &encontrado);
    if (encontrado) return resultadoPrevio;

    // Revisión rápida: mismas letras
    int letras[26] = {0};
    for (int i = 0; i < longitud; i++) {
        letras[a[i] - 'a']++;
        letras[b[i] - 'a']--;
    }
    for (int i = 0; i < 26; i++) {
        if (letras[i] != 0) {
            guardarCache(claveCache, false);
            return false;
        }
    }

    // Probar divisiones
    for (int i = 1; i < longitud; i++) {
        // Sin intercambio
        if (esScramble(strndup(a, i), strndup(b, i)) &&
            esScramble(a + i, b + i)) {
            guardarCache(claveCache, true);
            return true;
        }

        // Con intercambio
        if (esScramble(strndup(a, i), strndup(b + longitud - i, i)) &&
            esScramble(a + i, strndup(b, longitud - i))) {
            guardarCache(claveCache, true);
            return true;
        }
    }

    guardarCache(claveCache, false);
    return false;
}

int main() {
    char palabra1[31], palabra2[31];

    printf("Introduce la primera cadena: ");
    scanf("%30s", palabra1);
    printf("Introduce la segunda cadena: ");
    scanf("%30s", palabra2);

    if (strlen(palabra1) != strlen(palabra2)) {
        puts("false");
        return 0;
    }

    bool resultado = esScramble(palabra1, palabra2);
    puts(resultado ? "true" : "false");

    return 0;
}

