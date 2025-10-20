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
        vec[i] = rand() % 1000;
    }
    return vec;
}

// Función para buscar un valor en un vector
bool buscarValor(const vector<int>& vec, int valor, int indiceVector, int& posicion) {
    int thread_id = omp_get_thread_num();
    cout << "Thread " << thread_id << " buscando " << valor 
         << " en vector " << indiceVector << endl;
    
    for(int i = 0; i < vec.size(); i++) {
        if(vec[i] == valor) {
            posicion = i;
            return true;
        }
    }
    posicion = -1;
    return false;
}

int main() {
    srand(time(NULL));
    
    int numVectores = 8;
    int tamanoVector = 500000;
    int valorBuscado = 42;
    
    cout << "=== EJERCICIO 4: Búsqueda en Múltiples Vectores ===" << endl;
    cout << "Creando " << numVectores << " vectores de tamaño " << tamanoVector << endl;
    cout << "Buscando el valor: " << valorBuscado << endl << endl;
    
    // Crear múltiples vectores
    vector<vector<int>> vectores;
    for(int i = 0; i < numVectores; i++) {
        vectores.push_back(generarVector(tamanoVector));
        // Insertar el valor en algunos vectores aleatoriamente
        if(rand() % 2 == 0) {
            int posAleatoria = rand() % tamanoVector;
            vectores[i][posAleatoria] = valorBuscado;
        }
    }
    
    // Vectores para almacenar resultados
    vector<bool> encontrado(numVectores);
    vector<int> posiciones(numVectores);
    
    double inicio = omp_get_wtime();
    
    // Búsqueda paralela: cada vector se busca independientemente
    #pragma omp parallel for
    for(int i = 0; i < numVectores; i++) {
        encontrado[i] = buscarValor(vectores[i], valorBuscado, i, posiciones[i]);
    }
    
    double fin = omp_get_wtime();
    
    // Mostrar resultados
    cout << "\n=== Resultados de Búsqueda ===" << endl;
    int totalEncontrados = 0;
    for(int i = 0; i < numVectores; i++) {
        cout << "Vector " << i << ": ";
        if(encontrado[i]) {
            cout << "ENCONTRADO en posición " << posiciones[i] << endl;
            totalEncontrados++;
        } else {
            cout << "NO ENCONTRADO" << endl;
        }
    }
    
    cout << "\nValor encontrado en " << totalEncontrados << " de " << numVectores << " vectores" << endl;
    cout << "Tiempo total: " << (fin - inicio) << " segundos" << endl;
    cout << "Número de threads utilizados: " << omp_get_max_threads() << endl;
    
    return 0;
}
