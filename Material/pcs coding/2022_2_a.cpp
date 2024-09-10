#include <iostream>
#include <vector>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
using namespace std;

class Polinomio {
private:
    vector<int> coef; // Vector para almacenar los coeficientes del polinomio

public:
    // Constructor que solicita el grado del polinomio y genera coeficientes aleatorios
    Polinomio(int grado) {
        coef.resize(grado + 1); // Redimensiona el vector para almacenar los coeficientes
        for (int i = 0; i <= grado; ++i) {
            coef[i] = rand() % 21 - 10; // Genera coeficientes aleatorios entre -10 y 10
        }
    }

    // Sobrecarga del operador <<
    friend ostream& operator<<(ostream& os, const Polinomio& p) {
        bool primero = true; // Para evitar el primer signo '+'
        for (int i = p.coef.size() - 1; i >= 0; --i) {
            if (p.coef[i] != 0) { // No mostrar términos con coeficiente cero
                if (!primero && p.coef[i] > 0) {
                    os << " + ";
                } else if (p.coef[i] < 0) {
                    os << " - ";
                } else if (!primero) {
                    os << " ";
                }

                if (abs(p.coef[i]) != 1 || i == 0) { // No mostrar '1' o '-1' excepto en el término constante
                    os << abs(p.coef[i]);
                }

                if (i > 0) {
                    os << "x";
                    if (i > 1) os << i; // Mostrar el exponente si es mayor que 1
                }
                primero = false;
            }
        }
        if (primero) {
            os << "0"; // Si todos los coeficientes son cero, mostrar 0
        }
        return os;
    }

    // Sobrecarga del operador +
    Polinomio operator+(const Polinomio& other) const {
        int maxGrado = max(coef.size(), other.coef.size());
        Polinomio resultado(maxGrado - 1); // Crear un polinomio de grado adecuado
        resultado.coef.resize(maxGrado);   // Ajustar el tamaño del vector de coeficientes

        for (int i = 0; i < maxGrado; ++i) {
            int coef1 = (i < coef.size()) ? coef[i] : 0; 
            int coef2 = (i < other.coef.size()) ? other.coef[i] : 0; 
            resultado.coef[i] = coef1 + coef2;
        }
        return resultado;
    }
};

int main() {
    srand(time(0)); // Semilla para la generación de números aleatorios

    // Crear dos polinomios de ejemplo
    Polinomio poli1(2); // Polinomio de grado 2
    Polinomio poli2(2); // Polinomio de grado 2

    // Sumar los dos polinomios
    Polinomio suma = poli1 + poli2;

    // Mostrar los polinomios y su suma
    cout << poli1 << ": poli1" << endl;
    cout << poli2 << ": poli2" << endl;
    cout << suma << ": poli1 + poli2" << endl;

    return 0;
}
