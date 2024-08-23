#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <cstring> // Para memcpy()
using namespace std;

class Dados {
private:
    int* ptr;
    int cantidad;

public: 
    // Constructor que recibe la cantidad de dados
    Dados(int cant) : cantidad(cant) {
        ptr = new int[cantidad];
    }

    // Constructor de copia
    Dados(const Dados& other) : cantidad(other.cantidad) {
        ptr = new int[cantidad];
        memcpy(ptr, other.ptr, cantidad * sizeof(int));
    }

    // Constructor de movimiento
    Dados(Dados&& other) noexcept : ptr(other.ptr), cantidad(other.cantidad) {
        other.ptr = nullptr; // Desvincular el puntero del objeto original
        other.cantidad = 0;
    }

    // Destructor
    ~Dados() {
        delete[] ptr;
    }

    // Método para lanzar los dados
    void lanzar() {
        for (int i = 0; i < cantidad; ++i) {
            ptr[i] = rand() % 6 + 1; // Valores entre 1 y 6
        }
    }

    // Método para calcular el promedio de los resultados
    double promedio() const {
        int suma = 0;
        for (int i = 0; i < cantidad; ++i) {
            suma += ptr[i];
        }
        return static_cast<double>(suma) / cantidad;
    }

    // Método para imprimir los resultados y determinar si el jugador gana
    void imprimirResultados() const {
        cout << "Resultados: ";
        for (int i = 0; i < cantidad; ++i) {
            cout << ptr[i] << " ";
        }
        cout << endl;
        
        double prom = promedio();
        cout << "Promedio: " << prom << endl;

        if (prom > 3) {
            cout << "El jugador gana." << endl;
        } else {
            cout << "El jugador pierde." << endl;
        }
    }
};

int main() {
    srand(time(0)); // Inicializar la semilla para rand()

    // Jugador 1
    Dados jugador1(5);
    jugador1.lanzar();
    cout << "Jugador 1:" << endl;
    jugador1.imprimirResultados();

    // Jugador 2 utilizando constructor de copia
    Dados jugador2(jugador1);
    cout << "\nJugador 2 (Constructor de Copia):" << endl;
    jugador2.imprimirResultados();

    // Jugador 3 utilizando constructor de movimiento
    Dados jugador3(move(jugador1));
    cout << "\nJugador 3 (Constructor de Movimiento):" << endl;
    jugador3.imprimirResultados();

    // Comprobando que jugador1 ya no tiene datos
    cout << "\nIntentando imprimir Jugador 1 despues del movimiento:" << endl;
    jugador1.imprimirResultados();

    return 0;
}
