#include <iostream>
using namespace std;

// Función base (caso de finalización para 1 argumento)
template <typename T>
bool check_sum(T num) {
    // Si solo hay un número, no hay posibilidad de formar un par
    return false;
}

// Función recursiva para verificar si existe un par que sume 10
template <typename T, typename... Args>
bool check_sum(T first, Args... rest) {
    // Comparamos el primer número con cada uno de los demás números
    bool found = ((first + rest == 10) || ...);

    // Si encontramos un par, devolvemos true
    if (found) {
        return true;
    }

    // Si no encontramos un par, llamamos recursivamente para los siguientes números
    return check_sum(rest...);
}

int main() {
    cout << check_sum(2, 5, 6, 7, 2, 1, 3) << endl;   // Resultado: 1
    cout << check_sum(1, 2, 5, 6, 7, 2, 1, 1) << endl; // Resultado: 0
    cout << check_sum(1, 1, 2, 3, 6, 6, 2, 5, 5) << endl; // Resultado: 1
    return 0;
}
