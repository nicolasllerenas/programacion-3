#include <iostream>
#include <cstdlib> // Para srand() y rand()
#include <ctime>   // Para time()
#include <iomanip> // Para setprecision()
using namespace std;

/*
 * Pregunta 2 - Clase plantilla MatVector
 */

template<typename T>
class MatVector {
private:
    T* data;  // Puntero dinámico para almacenar los elementos del vector
    int size; // Tamaño del vector

public:
    // Constructor: Inicializa el vector con elementos aleatorios
    MatVector(int n) : size(n) {
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = static_cast<T>(rand() % 10); // Valores aleatorios entre 0 y 9
        }
    }

    // Destructor para liberar la memoria asignada dinámicamente
    ~MatVector() {
        delete[] data;
    }

    // Sobrecarga del operador '[]' para acceder y modificar elementos
    T& operator[](int index) {
        return data[index];
    }

    // Sobrecarga del operador '<<' para visualizar el objeto MatVector
    friend ostream& operator<<(ostream& os, const MatVector& v) {
        os << "[ ";
        for (int i = 0; i < v.size; i++) {
            os << v.data[i] << " ";
        }
        os << "]";
        return os;
    }

    // Sobrecarga del operador '*' para el producto escalar de dos vectores
    T operator*(const MatVector& other) const {
        T product = 0; // Inicializa el producto escalar en 0
        int min_size = min(size, other.size); // El tamaño mínimo entre los dos vectores
        for (int i = 0; i < min_size; i++) {
            product += data[i] * other.data[i];
        }
        return product;
    }
};

// Código principal para probar la clase MatVector
int main() {
    srand(static_cast<unsigned>(time(0))); // Inicializar la semilla de números aleatorios

    MatVector<int> v1(4);               // Vector de enteros de tamaño 4
    MatVector<float> v2(4);             // Vector de flotantes de tamaño 4

    cout << v1[2] << endl;              // Imprime el tercer elemento de v1
    cout << v1 << endl;                 // Imprime todo el vector v1

    cout << v2 << endl;                 // Imprime todo el vector v2
    v2[3] = 7.1;                        // Asigna 7.1 al cuarto elemento de v2
    cout << v2 << endl;                 // Imprime el vector v2 modificado

    cout << fixed << setprecision(1);   // Configura la precisión a un decimal
    cout << (v1 * v2) << endl;          // Imprime el producto escalar de v1 y v2

    return 0;
}