#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int elementos_no_repetidos(const vector<int>& vec) {
    unordered_map<int, int> frecuencias;

    // Primer recorrido: contar frecuencias de cada elemento
    for (int num : vec) {
        frecuencias[num]++;
    }

    // Segundo recorrido: contar elementos que aparecen solo una vez
    int no_repetidos = 0;
    for (const auto& par : frecuencias) {
        if (par.second == 1) {
            no_repetidos++;
        }
    }

    return no_repetidos;
}



int main() {
    vector<int> vec = {1, 5, 3, 2, 4, 1, 2, 3, 4, 8, 11};
    int resultado = elementos_no_repetidos(vec);
    cout << "El resultado es: " << resultado << endl;
    return 0;
}