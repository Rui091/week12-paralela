#include <iostream>
#include <vector>
#include <omp.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Función para generar un vector aleatorio
vector<int> generarVector(int tamano) {
    vector<int> vec(tamano);
    for(int i = 0; i < tamano; i++) {
        vec[i] = rand() % 100;
    }
    return vec;
}

// Función para sumar elementos de un vector
long long sumarVector(const vector<int>& vec, int indice) {
    int thread_id = omp_get_thread_num();
    cout << "Thread " << thread_id << " sumando vector " << indice << endl;
    
    long long suma = 0;
    for(int i = 0; i < vec.size(); i++) {
        suma += vec[i];
    }
    return suma;
}

int main() {
    srand(time(NULL));
    
    int numVectores = 10;
    int tamanoVector = 1000000;
    
    cout << "=== EJERCICIO 3: Suma de Elementos en Múltiples Vectores ===" << endl;
    cout << "Creando " << numVectores << " vectores de tamaño " << tamanoVector << endl;
    
    // Crear múltiples vectores
    vector<vector<int>> vectores;
    for(int i = 0; i < numVectores; i++) {
        vectores.push_back(generarVector(tamanoVector));
    }
    
    // Vector para almacenar resultados
    vector<long long> resultados(numVectores);
    
    double inicio = omp_get_wtime();
    
    // Procesamiento paralelo: cada vector se suma independientemente
    #pragma omp parallel for
    for(int i = 0; i < numVectores; i++) {
        resultados[i] = sumarVector(vectores[i], i);
    }
    
    double fin = omp_get_wtime();
    
    // Mostrar resultados
    cout << "\n=== Resultados ===" << endl;
    for(int i = 0; i < numVectores; i++) {
        cout << "Vector " << i << ": Suma = " << resultados[i] << endl;
    }
    
    cout << "\nTiempo total: " << (fin - inicio) << " segundos" << endl;
    cout << "Número de threads utilizados: " << omp_get_max_threads() << endl;
    
    return 0;
}
