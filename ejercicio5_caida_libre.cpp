#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <iomanip>

using namespace std;

// Estructura para representar un objeto
struct Objeto {
    string nombre;
    double altura;      // metros
    double masa;        // kg (no afecta en caída libre sin resistencia del aire)
    double tiempo;      // resultado: tiempo de caída
    
    Objeto(string n, double h, double m) : nombre(n), altura(h), masa(m), tiempo(0.0) {}
};

// Función para calcular el tiempo de caída libre
void calcularTiempoCaida(Objeto& obj) {
    int thread_id = omp_get_thread_num();
    
    const double g = 9.81; // aceleración de la gravedad (m/s²)
    
    // Fórmula: t = sqrt(2h/g)
    // Derivada de: h = (1/2) * g * t²
    obj.tiempo = sqrt(2.0 * obj.altura / g);
    
    #pragma omp critical
    {
        cout << "Thread " << thread_id << " calculando: " << obj.nombre << endl;
    }
}

// Función para presentar resultados de un objeto
void presentarResultado(const Objeto& obj) {
    cout << fixed << setprecision(3);
    cout << "\n--- " << obj.nombre << " ---" << endl;
    cout << "  Altura inicial: " << obj.altura << " m" << endl;
    cout << "  Masa: " << obj.masa << " kg" << endl;
    cout << "  Tiempo de caída: " << obj.tiempo << " segundos" << endl;
    
    // Calcular velocidad final (v = g * t)
    double velocidadFinal = 9.81 * obj.tiempo;
    cout << "  Velocidad al impactar: " << velocidadFinal << " m/s" << endl;
}

int main() {
    cout << "=== EJERCICIO 5: Simulación de Caída Libre para Múltiples Objetos ===" << endl;
    cout << "(Sin considerar resistencia del aire)\n" << endl;
    
    // Crear múltiples objetos con diferentes alturas
    vector<Objeto> objetos;
    objetos.push_back(Objeto("Pelota de tenis", 10.0, 0.058));
    objetos.push_back(Objeto("Martillo", 50.0, 0.5));
    objetos.push_back(Objeto("Pluma (vacío)", 100.0, 0.005));
    objetos.push_back(Objeto("Ladrillo", 25.0, 2.5));
    objetos.push_back(Objeto("Balón de fútbol", 75.0, 0.43));
    objetos.push_back(Objeto("Moneda", 5.0, 0.01));
    objetos.push_back(Objeto("Libro", 150.0, 1.0));
    objetos.push_back(Objeto("Gota de agua", 200.0, 0.001));
    
    int numObjetos = objetos.size();
    
    cout << "Simulando caída libre para " << numObjetos << " objetos...\n" << endl;
    
    double inicio = omp_get_wtime();
    
    // Cálculo paralelo: cada objeto se calcula independientemente
    #pragma omp parallel for
    for(int i = 0; i < numObjetos; i++) {
        calcularTiempoCaida(objetos[i]);
    }
    
    double fin = omp_get_wtime();
    
    // Presentar todos los resultados
    cout << "\n=== RESULTADOS DE LA SIMULACIÓN ===" << endl;
    for(int i = 0; i < numObjetos; i++) {
        presentarResultado(objetos[i]);
    }
    
    // Encontrar el objeto que tarda más y menos tiempo
    int masLento = 0, masRapido = 0;
    for(int i = 1; i < numObjetos; i++) {
        if(objetos[i].tiempo > objetos[masLento].tiempo) masLento = i;
        if(objetos[i].tiempo < objetos[masRapido].tiempo) masRapido = i;
    }
    
    cout << "\n=== ESTADÍSTICAS ===" << endl;
    cout << "Objeto con mayor tiempo de caída: " << objetos[masLento].nombre 
         << " (" << objetos[masLento].tiempo << " s)" << endl;
    cout << "Objeto con menor tiempo de caída: " << objetos[masRapido].nombre 
         << " (" << objetos[masRapido].tiempo << " s)" << endl;
    
    cout << "\nTiempo de cómputo: " << (fin - inicio) << " segundos" << endl;
    cout << "Número de threads utilizados: " << omp_get_max_threads() << endl;
    
    return 0;
}
