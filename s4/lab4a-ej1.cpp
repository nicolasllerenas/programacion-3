#include <iostream>
#include <type_traits>

using namespace std;

template<typename T>
T sumar(T inp1, T inp2){
    return inp1 + inp2;
}

template<typename T1, typename T2>
char sumar(T1 inp1, T2 inp2){
    return inp1 + inp2;
}
int main() {
    cout << sumar(1, 3) << endl;           // Suma numérica
    cout << sumar('A', 1) << endl;         // Caracter + Número
    cout << sumar(2, 'A') << endl;         // Número + Caracter
    cout << sumar('<', '=') << endl;       // Caracter + Caracter
    
    return 0;
}