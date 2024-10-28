#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class SubarrayMinimo {
private:
    // Almacena el inicio del subarreglo mínimo
    int inicio;
    // Almacena el final del subarreglo mínimo
    int fin;
    // Almacena la suma mínima encontrada
    int sumaMinima;

public:
    SubarrayMinimo() : inicio(0), fin(0), sumaMinima(INT_MAX) {}

    void encontrarSubarrayMinimo(const vector<int>& arr) {
        // Variables iniciales
        int sumaActual = 0;
        int minSumaHastaAhora = INT_MAX;
        int inicioTemp = 0;
        inicio = 0;
        fin = 0;

        // Recorremos el arreglo una sola vez - O(n)
        for (int i = 0; i < arr.size(); i++) {
            sumaActual += arr[i];

            // Si encontramos una suma menor -> actualizamos los índices
            if (sumaActual < minSumaHastaAhora) {
                minSumaHastaAhora = sumaActual;
                inicio = inicioTemp;
                fin = i;
            }

            // Si la suma actual se vuelve positiva, reiniciamos
            if (sumaActual > 0) {
                sumaActual = 0;
                inicioTemp = i + 1;
            }
        }

        sumaMinima = minSumaHastaAhora;
    }

    void mostrarResultado(const vector<int>& arr) {
        cout << "Suma minima: " << sumaMinima << " -> {";
        for (int i = inicio; i <= fin; i++) {
            cout << arr[i];
            if (i < fin) cout << ", ";
        }
        cout << "}" << endl;
    }
};

int main() {
    // Caso de prueba del ejemplo
    vector<int> arreglo = {-2, 1, -3, 4, -2, 2, -1, -2, 4};
    
    SubarrayMinimo solver;
    solver.encontrarSubarrayMinimo(arreglo);
    solver.mostrarResultado(arreglo);

    // Casos de prueba adicionales
    vector<int> caso1 = {1, -3, 2, -5, 7, -1, -4, 2};
    solver.encontrarSubarrayMinimo(caso1);
    solver.mostrarResultado(caso1);

    vector<int> caso2 = {-1, -2, -3, -4};
    solver.encontrarSubarrayMinimo(caso2);
    solver.mostrarResultado(caso2);

    return 0;
}