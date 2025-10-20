# Algoritmos Embarazosamente Paralelos con OpenMP

Este proyecto contiene implementaciones de algoritmos embarazosamente paralelos (embarrassingly parallel) utilizando OpenMP en C++.

## 📚 ¿Qué son los algoritmos embarazosamente paralelos?

Son problemas que pueden ser divididos en tareas completamente independientes, donde cada tarea no requiere comunicación con las demás. Son ideales para paralelización porque:
- ✅ No hay dependencias entre tareas
- ✅ No requieren sincronización compleja
- ✅ Escalan linealmente con el número de procesadores
- ✅ Implementación simple y directa

**Ejemplos del mundo real:**
- Procesar múltiples imágenes con el mismo filtro
- Renderizar frames independientes de video
- Cálculos científicos sobre datasets independientes
- Validación de múltiples entradas de datos

## 🎯 Ejercicios Implementados

### Ejercicio 1: Filtro a Múltiples Imágenes
**Archivo:** `ejercicio1_filtro_imagenes.cpp`

Aplica un filtro blanco y negro a múltiples imágenes en paralelo. Cada imagen se procesa independientemente.

**Características:**
- 🖼️ Simula procesamiento de 8 imágenes de 800x600 píxeles
- 🎨 Aplica filtro de threshold para blanco/negro (valor > 128 → blanco, sino → negro)
- ⚡ Cada thread procesa una imagen completa
- 📊 Cada píxel se convierte independientemente

**Paralelización:** `#pragma omp parallel for` sobre el bucle de imágenes

---

### Ejercicio 3: Suma de Elementos en Múltiples Vectores
**Archivo:** `ejercicio3_suma_vectores.cpp`

Calcula la suma de elementos en múltiples vectores de forma paralela.

**Características:**
- 📐 Procesa 10 vectores de 1,000,000 de elementos cada uno
- 🔢 Cada vector contiene números aleatorios entre 0-99
- ⚡ Cada vector se suma independientemente (sin reducción compartida)
- 💾 Resultados almacenados en vector de resultados

**Paralelización:** `#pragma omp parallel for` sobre vectores independientes

---

### Ejercicio 4: Búsqueda en Múltiples Vectores
**Archivo:** `ejercicio4_busqueda_vectores.cpp`

Busca un valor específico en múltiples vectores simultáneamente.

**Características:**
- 🔍 Busca el valor 42 en 8 vectores de 500,000 elementos
- 📍 Reporta si el valor fue encontrado y en qué posición
- 🎲 El valor se inserta aleatoriamente en algunos vectores
- ⚡ Cada búsqueda es completamente independiente (búsqueda lineal)

**Paralelización:** `#pragma omp parallel for` sobre búsquedas independientes

---

### Ejercicio 5: Simulación de Caída Libre
**Archivo:** `ejercicio5_caida_libre.cpp`

Simula la caída libre de múltiples objetos desde diferentes alturas (sin resistencia del aire).

**Características:**
- 🪐 Calcula el tiempo de caída para 8 objetos diferentes
- 📐 Usa la fórmula física: **t = √(2h/g)** donde g = 9.81 m/s²
- 💨 Calcula también la velocidad final de impacto: **v = g × t**
- 📊 Muestra estadísticas: objeto más lento y más rápido
- 🎯 Objetos: pelota de tenis, martillo, pluma, ladrillo, balón, moneda, libro, gota de agua

**Paralelización:** `#pragma omp parallel for` sobre cálculos independientes de física

## 🐳 Ejecución en Docker (Recomendado)

### Opción 1: Usando el contenedor japeto/parallel-tools

```bash
# Iniciar el contenedor con volumen montado
docker run -it -v "${PWD}:/home/japeto/app:rw" -w /home/japeto/app japeto/parallel-tools:v64 bash

# Dentro del contenedor, compilar todos los ejercicios
g++ -fopenmp ejercicio1_filtro_imagenes.cpp -o ejercicio1 && \
g++ -fopenmp ejercicio3_suma_vectores.cpp -o ejercicio3 && \
g++ -fopenmp ejercicio4_busqueda_vectores.cpp -o ejercicio4 && \
g++ -fopenmp ejercicio5_caida_libre.cpp -o ejercicio5

# Ejecutar todos los ejercicios
./ejercicio1
./ejercicio3
./ejercicio4
./ejercicio5

# O ejecutar todos en secuencia
./ejercicio1 && echo "" && ./ejercicio3 && echo "" && ./ejercicio4 && echo "" && ./ejercicio5
```

### Opción 2: Comando único (ejecutar y salir)

```bash
docker run --rm -v "${PWD}:/home/japeto/app:rw" -w /home/japeto/app japeto/parallel-tools:v64 bash -c \
  "g++ -fopenmp ejercicio1_filtro_imagenes.cpp -o ejercicio1 && \
   g++ -fopenmp ejercicio3_suma_vectores.cpp -o ejercicio3 && \
   g++ -fopenmp ejercicio4_busqueda_vectores.cpp -o ejercicio4 && \
   g++ -fopenmp ejercicio5_caida_libre.cpp -o ejercicio5 && \
   echo '=== EJECUTANDO TODOS LOS EJERCICIOS ===' && \
   ./ejercicio1 && echo '' && ./ejercicio3 && echo '' && ./ejercicio4 && echo '' && ./ejercicio5"
```

---

## 💻 Compilación Local (sin Docker)

### Windows (con MinGW)
```powershell
g++ -fopenmp ejercicio1_filtro_imagenes.cpp -o ejercicio1.exe
g++ -fopenmp ejercicio3_suma_vectores.cpp -o ejercicio3.exe
g++ -fopenmp ejercicio4_busqueda_vectores.cpp -o ejercicio4.exe
g++ -fopenmp ejercicio5_caida_libre.cpp -o ejercicio5.exe
```

**Ejecutar:**
```powershell
.\ejercicio1.exe
.\ejercicio3.exe
.\ejercicio4.exe
.\ejercicio5.exe
```

### Linux/Mac
```bash
g++ -fopenmp ejercicio1_filtro_imagenes.cpp -o ejercicio1
g++ -fopenmp ejercicio3_suma_vectores.cpp -o ejercicio3
g++ -fopenmp ejercicio4_busqueda_vectores.cpp -o ejercicio4
g++ -fopenmp ejercicio5_caida_libre.cpp -o ejercicio5
```

**Ejecutar:**
```bash
./ejercicio1
./ejercicio3
./ejercicio4
./ejercicio5
```

## ⚙️ Configuración de Threads

Para controlar el número de threads que usa OpenMP:

### En Docker/Bash:
```bash
export OMP_NUM_THREADS=4
./ejercicio1
```

### En PowerShell (Windows):
```powershell
$env:OMP_NUM_THREADS=4
.\ejercicio1.exe
```

### En CMD (Windows):
```cmd
set OMP_NUM_THREADS=4
ejercicio1.exe
```

### Dentro del contenedor Docker:
```bash
# Iniciar contenedor con variable de entorno
docker run -it -e OMP_NUM_THREADS=8 -v "${PWD}:/home/japeto/app:rw" -w /home/japeto/app japeto/parallel-tools:v64 bash
```

**Recomendación:** Usar un número de threads igual al número de cores físicos de tu CPU para mejor rendimiento.

## 📖 Conceptos de OpenMP Utilizados

### Directivas de Paralelización

| Directiva | Descripción | Uso en el Proyecto |
|-----------|-------------|-------------------|
| `#pragma omp parallel for` | Paraleliza un bucle for distribuyendo las iteraciones entre threads | Todos los ejercicios - itera sobre tareas independientes |
| `#pragma omp critical` | Sección crítica para evitar condiciones de carrera | Protege la salida por consola |

### Funciones de OpenMP

| Función | Descripción | Ejemplo de Uso |
|---------|-------------|----------------|
| `omp_get_wtime()` | Obtiene el tiempo actual en segundos (alta precisión) | Medir tiempo de ejecución |
| `omp_get_thread_num()` | Obtiene el ID del thread actual (0 a N-1) | Identificar qué thread ejecuta cada tarea |
| `omp_get_max_threads()` | Obtiene el número máximo de threads disponibles | Reportar configuración al usuario |

### Modelo de Ejecución

```
SECUENCIAL:                    PARALELO (4 threads):
━━━━━━━━━━━━━━━━━━━━          Thread 0: ████
Tarea 1                        Thread 1: ████
Tarea 2                        Thread 2: ████
Tarea 3                        Thread 3: ████
Tarea 4                        
━━━━━━━━━━━━━━━━━━━━          ━━━━━━━━━━━━━━
Tiempo: 4T                     Tiempo: T (speedup 4x)
```

## 🚀 Ventajas de la Paralelización

Estos ejercicios demuestran cómo la paralelización puede acelerar significativamente el procesamiento cuando:

✅ **Las tareas son independientes** - No hay dependencias de datos entre iteraciones  
✅ **No hay necesidad de compartir datos** - Cada tarea trabaja en su propio espacio de memoria  
✅ **El costo computacional es significativo** - El tiempo de procesamiento justifica el overhead de threads  
✅ **Hardware multi-core disponible** - Aprovecha procesadores modernos con múltiples cores  

### Speedup Esperado

| Threads | Speedup Teórico | Speedup Real (aprox) |
|---------|----------------|---------------------|
| 1 | 1x | 1x |
| 2 | 2x | 1.8x - 1.9x |
| 4 | 4x | 3.5x - 3.8x |
| 8 | 8x | 6.5x - 7.5x |

**Nota:** El speedup real es menor debido a:
- Overhead de creación y sincronización de threads
- Limitaciones de memoria cache
- Contención de recursos compartidos (memoria, I/O)

## 📊 Resultados Esperados

### Ejemplo de Salida (Ejercicio 1):
```
=== EJERCICIO 1: Filtro a Múltiples Imágenes ===
Creando 8 imágenes...
Thread 2 procesando imagen: imagen_2.jpg
Thread 0 procesando imagen: imagen_0.jpg
Thread 3 procesando imagen: imagen_3.jpg
Thread 1 procesando imagen: imagen_1.jpg
...
Todas las imágenes procesadas en 0.245 segundos
Número de threads utilizados: 4
```

### Ejemplo de Salida (Ejercicio 5):
```
=== EJERCICIO 5: Simulación de Caída Libre ===
Thread 1 calculando: Martillo
Thread 0 calculando: Pelota de tenis
...
--- Pelota de tenis ---
  Altura inicial: 10.000 m
  Masa: 0.058 kg
  Tiempo de caída: 1.428 segundos
  Velocidad al impactar: 14.012 m/s
...
Tiempo de cómputo: 0.001 segundos
Número de threads utilizados: 4
```

## 📝 Notas Importantes

- 🎯 Las "imágenes" en el Ejercicio 1 son **simuladas** (estructuras en memoria), no archivos .jpg reales
- ⏱️ Los tiempos de ejecución variarán según el hardware
- 🔄 El speedup ideal es lineal con el número de cores, pero en práctica es menor
- 🐳 **Docker es la forma recomendada** para ejecutar (entorno consistente)
- 💾 Los binarios compilados (`ejercicio1`, `ejercicio3`, etc.) se crean en el directorio actual

## 🔧 Troubleshooting

### Error: "command not found: g++"
**Solución:** Usa el contenedor Docker que ya tiene GCC instalado.

### Error: "undefined reference to omp_*"
**Solución:** Asegúrate de compilar con `-fopenmp`

### Los threads no se distribuyen
**Solución:** Verifica `OMP_NUM_THREADS` o el número de cores disponibles

### Rendimiento bajo en Docker
**Solución:** Aumenta los recursos asignados a Docker (CPU/memoria)
