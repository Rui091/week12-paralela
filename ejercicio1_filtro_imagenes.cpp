#include <iostream>
#include <vector>
#include <string>
#include <omp.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Estructura simple para representar una imagen
struct Imagen {
    string nombre;
    int ancho;
    int alto;
    vector<vector<int>> pixeles; // RGB simulado como un solo valor
    
    Imagen(string n, int w, int h) : nombre(n), ancho(w), alto(h) {
        pixeles.resize(h, vector<int>(w));
        // Generar píxeles aleatorios
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                pixeles[i][j] = rand() % 256;
            }
        }
    }
};

// Función para aplicar filtro blanco y negro (grayscale)
void aplicarFiltroBlancoYNegro(Imagen& img) {
    int thread_id = omp_get_thread_num();
    cout << "Thread " << thread_id << " procesando imagen: " << img.nombre << endl;
    
    // Simular procesamiento más complejo
    for(int i = 0; i < img.alto; i++) {
        for(int j = 0; j < img.ancho; j++) {
            // Aplicar threshold para blanco/negro
            img.pixeles[i][j] = (img.pixeles[i][j] > 128) ? 255 : 0;
        }
    }
}

// Función para "guardar" imagen (simulado)
void guardarImagen(const Imagen& img) {
    cout << "Imagen " << img.nombre << " guardada correctamente." << endl;
}

int main() {
    srand(time(NULL));
    
    // Crear múltiples imágenes
    vector<Imagen> imagenes;
    int numImagenes = 8;
    
    cout << "=== EJERCICIO 1: Filtro a Múltiples Imágenes ===" << endl;
    cout << "Creando " << numImagenes << " imágenes..." << endl;
    
    for(int i = 0; i < numImagenes; i++) {
        imagenes.push_back(Imagen("imagen_" + to_string(i) + ".jpg", 800, 600));
    }
    
    double inicio = omp_get_wtime();
    
    // Procesamiento paralelo de imágenes
    #pragma omp parallel for
    for(int i = 0; i < numImagenes; i++) {
        // Cada imagen se procesa independientemente
        aplicarFiltroBlancoYNegro(imagenes[i]);
        
        #pragma omp critical
        {
            guardarImagen(imagenes[i]);
        }
    }
    
    double fin = omp_get_wtime();
    
    cout << "\nTodas las imágenes procesadas en " << (fin - inicio) << " segundos" << endl;
    cout << "Número de threads utilizados: " << omp_get_max_threads() << endl;
    
    return 0;
}
