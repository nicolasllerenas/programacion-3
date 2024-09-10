#include <iostream>
#include <vector>
using namespace std;

/*
 * Pregunta 1 - Clase plantilla MiLista
 */

template<typename T>
class MiLista {
private:
    vector<T> elementos;  // Vector para almacenar los elementos

public:
    // Constructor que inicializa la lista con argumentos variables
    template<typename... Args>
    MiLista(Args... args) : elementos{args...} {}

    // Sobrecarga del operador '<<' para agregar elementos a la lista
    MiLista& operator<<(const T& nuevoElemento) {
        elementos.push_back(nuevoElemento);
        return *this;
    }

    // Sobrecarga del operador '<<' para visualizar el objeto MiLista
    friend ostream& operator<<(ostream& os, const MiLista& lista) {
        os << "[ ";
        for (const auto& elem : lista.elementos) {
            os << elem << " ";
        }
        os << "]";
        return os;
    }

    // Sobrecarga del operador '+' para sumar dos listas
    MiLista operator+(const MiLista& otraLista) const {
        MiLista resultado = *this; // Copia de la lista actual
        resultado.elementos.insert(resultado.elementos.end(), otraLista.elementos.begin(), otraLista.elementos.end());
        return resultado;
    }
};

// Código principal para probar la clase MiLista
int main() {
    MiLista<int> lista1;                   // Lista vacía
    MiLista<int> lista2(1);                // Lista con un elemento
    MiLista<float> lista3(2.1, 3.2, 0.4);  // Lista con tres elementos

    cout << lista1 << endl; // Salida: [ ]
    cout << lista2 << endl; // Salida: [ 1 ]
    cout << lista3 << endl; // Salida: [ 2.1 3.2 0.4 ]

    lista1 << 2 << 5; // Agregar elementos 2 y 5 a lista1
    lista2 << 9;      // Agregar elemento 9 a lista2
    cout << lista1 << endl; // Salida: [ 2 5 ]
    cout << lista2 << endl; // Salida: [ 1 9 ]

    MiLista<int> lista4 = lista1 + lista2; // Sumar lista1 y lista2
    cout << lista4 << endl; // Salida: [ 2 5 1 9 ]

    return 0;
}
