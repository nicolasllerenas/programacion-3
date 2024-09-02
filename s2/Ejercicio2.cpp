#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

class Carta {
public:
    string simbolo;
    int numero;

    Carta(string s, int n) : simbolo(s), numero(n) {}
};

class Cartas {
private:
    vector<Carta> mazo;

public:
    // Constructor que genera un mazo de 52 cartas
    Cartas() {
        string simbolos[] = {"Corazones", "Diamantes", "Treboles", "Picas"};
        for (int i = 0; i < 4; ++i) {
            for (int j = 1; j <= 13; ++j) {
                mazo.push_back(Carta(simbolos[i], j));
            }
        }
    }

    // Sobrecarga del operador >> para barajar el mazo
    void operator>>(int veces) {
        for (int i = 0; i < veces; ++i) {
            shuffle(mazo.begin(), mazo.end(), default_random_engine(time(0)));
        }
    }

    // Sobrecarga del operador << para verificar tres cartas
    int operator<<(vector<Carta>& seleccionadas) {
        int puntos = 0;

        // Verificar si existe un par de cartas con el mismo número
        if (seleccionadas[0].numero == seleccionadas[1].numero ||
            seleccionadas[0].numero == seleccionadas[2].numero ||
            seleccionadas[1].numero == seleccionadas[2].numero) {
            puntos += 1;
        }

        // Verificar si las tres cartas tienen el mismo símbolo
        if (seleccionadas[0].simbolo == seleccionadas[1].simbolo &&
            seleccionadas[0].simbolo == seleccionadas[2].simbolo) {
            puntos += 1;
        }

        // Verificar si las tres cartas forman una escalera
        vector<int> numeros;
        for (auto &carta : seleccionadas) {
            numeros.push_back(carta.numero);
        }
        sort(numeros.begin(), numeros.end());
        if (numeros[2] == numeros[1] + 1 && numeros[1] == numeros[0] + 1) {
            puntos += 2;
        }

        return puntos;
    }

    // Mostrar el mazo
    void mostrarMazo() {
        for (auto &carta : mazo) {
            cout << carta.simbolo << " " << carta.numero << endl;
        }
    }

    // Seleccionar tres cartas
    vector<Carta> seleccionarTresCartas() {
        vector<Carta> seleccionadas;
        seleccionadas.push_back(mazo.back());
        mazo.pop_back();
        seleccionadas.push_back(mazo.back());
        mazo.pop_back();
        seleccionadas.push_back(mazo.back());
        mazo.pop_back();
        return seleccionadas;
    }
};

int main() {
    Cartas cartas;

    int barajar;
    cout << "Barajar? (> 1): ";
    cin >> barajar;

    if (barajar > 1) {
        cartas >> barajar;
        cartas.mostrarMazo();
    }

    vector<Carta> seleccionadas = cartas.seleccionarTresCartas();
    int puntos = cartas << seleccionadas;

    cout << "Puntos obtenidos: " << puntos << endl;

    return 0;
}
