#include <iostream>

using namespace std;

template<typename T>
string Tipo(T a){
    return "No es puntero.";
}

// Sobrecarga para punteros
template<typename T>
string Tipo(T* a){
    return "Es puntero.";
}

// Especialización para puntero a int
template<>
string Tipo(int* a){
    return "Es puntero 'int'.";
}

int main() {
    double x = 7;
    int u = 5;
    double* ptr1 = &x;
    int* ptr2 = &u;

    cout << Tipo(x) << endl;     // No es puntero
    cout << Tipo(ptr1) << endl;  // Es puntero
    cout << Tipo(ptr2) << endl;  // Es puntero 'int'

    return 0;
}