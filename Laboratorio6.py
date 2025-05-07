# Pérez Baeza Janiz Jatziri

def es_primo(n):
    if n < 2:
        return False
    for i in range(2, int(n**0.5)+1):
        if n % i == 0:
            return False
    return True

def generar_fibonacci_filtrado(k):
    fib = [0, 1]
    i = 2
    while True:
        siguiente = fib[-1] + fib[-2]
        if siguiente > k:
            break
        fib.append(siguiente)
        i += 1
    # Filtrar posiciones que sean primos (la posición comienza en 1)
    fib_filtrado = [fib[i] for i in range(len(fib)) if not es_primo(i+1)]
    return fib_filtrado

def calcular_k(dia, mes, anio):
    return (dia * 100) + (mes * 10) + (anio % 100)

def encontrar_min_fib_suma(k, fib_seq):
    resultado = []
    i = len(fib_seq) - 1
    while k > 0 and i >= 0:
        if fib_seq[i] <= k:
            resultado.append(fib_seq[i])
            k -= fib_seq[i]
        i -= 1
    return resultado

# Datos de nacimiento (puedes cambiar estos valores)
dia_nacimiento = 25
mes_nacimiento = 12
anio_nacimiento = 1995

# Paso 1: Calcular K
K = calcular_k(dia_nacimiento, mes_nacimiento, anio_nacimiento)
print(f"Valor de K: {K}")

# Paso 2: Generar secuencia de Fibonacci filtrada
fibonacci_filtrado = generar_fibonacci_filtrado(K)
print("Secuencia de Fibonacci filtrada (sin posiciones primas):")
print(fibonacci_filtrado)

# Paso 3: Encontrar la combinación mínima de términos
terminos_usados = encontrar_min_fib_suma(K, fibonacci_filtrado)
print("Términos usados para sumar K:")
print(terminos_usados)
print(f"Cantidad mínima de términos: {len(terminos_usados)}")

