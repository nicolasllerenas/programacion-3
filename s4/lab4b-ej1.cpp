#include <iostream>
#include <cmath>  // Para usar pow()

using namespace std;

// Función base
int foo() {
    return 0;  // Caso base para la recursión de la variadic function
}

// Variadic function con fold expression
template<typename T, typename... Args>
int foo(T first, Args... args) {
    int index = sizeof...(args); // Obtener el índice (la posición del parámetro)
    
    // Si la posición es impar (index % 2 == 0), se suma, de lo contrario se resta
    if (index % 2 == 0) {
        return pow(first, 2) + foo(args...); // Sumamos el cuadrado de los números en posiciones pares
    } else {
        return -pow(first, 2) + foo(args...); // Restamos el cuadrado de los números en posiciones impares
    }
}

int main() {
    cout << foo(4, 4, 5, 6) << endl; // Resultado esperado: -11
    return 0;
}
