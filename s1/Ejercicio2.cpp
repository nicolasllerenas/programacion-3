#include <iostream>
#include <cstdlib> // Para srand() y rand()
#include <ctime>   // Para time()
using namespace std;

class Matriz2D {
private:
    int** ptr;
    int filas;
    int columnas;

public:
    // Constructor que inicializa la matriz con valores aleatorios entre 0 y 9
    Matriz2D(int f, int c) : filas(f), columnas(c) {
        ptr = new int*[filas];
        for (int i = 0; i < filas; i++) {
            ptr[i] = new int[columnas];
            for (int j = 0; j < columnas; j++) {
                ptr[i][j] = rand() % 10; // Valores entre 0 y 9
            }
        }
    }

    // Destructor para liberar la memoria dinámica
    ~Matriz2D() {
        for (int i = 0; i < filas; i++) {
            delete[] ptr[i];
        }
        delete[] ptr;
    }

    // Función para imprimir la matriz
    void print() const {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                cout << ptr[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    srand(time(0)); // Inicializar la semilla para números aleatorios

    Matriz2D m1(4, 3);

    // Imprimir la matriz 
    m1.print();

    return 0;
}
