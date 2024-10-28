#include <iostream>
using namespace std;

// Definición de la función template utilizando variadic templates y fold expression
template<typename... Args>
void print(Args... args) {
    // Usamos una expresión de plegado para imprimir todos los argumentos separados por un espacio
    ((cout << args << " "), ...);
    cout << endl;
}

int main() {
    print(1); // Salida: 1
    print(); // Salida: (nada)
    print(1, 'a', 4.5, "Hola Mundo", false); // Salida: 1 a 4.5 Hola Mundo 0

    return 0;
}
