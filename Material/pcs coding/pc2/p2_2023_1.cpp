#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int contarPares(const vector<int>& vec, int k) {
    unordered_set<int> elementos;
    int contador = 0;

    for (int x : vec) {
        // Verificamos si hay algún número en el set que cumpla con la diferencia k
        if (elementos.count(x - k)) {
            contador++;
        }
        if (elementos.count(x + k)) {
            contador++;
        }
        // Añadimos el elemento actual al set
        elementos.insert(x);
    }

    return contador;
}

int main() {
    vector<int> vec = {1, 5, 3, 2, 4};
    int k = 2;
    int resultado = contarPares(vec, k);
    cout << "El resultado es: " << resultado << endl;
    return 0;
}
