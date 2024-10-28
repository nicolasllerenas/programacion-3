#include <iostream>
#include <string>
using namespace std;

class Transformer {
    string operacion;  // Modo de transformación (SUMAR, RESTAR, MULTIPLICAR, DIVIDIR)
    int constante;     // Valor constante que se aplicará a la transformación

public:
    // Constructor que recibe el modo de transformación y la constante
    Transformer(string operacion, int constante) : operacion(operacion), constante(constante) {}

    // Sobrecargar el operador () para aplicar la transformación
    int operator()(int valor) const {
        if (operacion == "SUMAR") {
            return valor + constante;
        } else if (operacion == "RESTAR") {
            return valor - constante;
        } else if (operacion == "MULTIPLICAR") {
            return valor * constante;
        } else if (operacion == "DIVIDIR") {
            return valor / constante;
        } else {
            throw invalid_argument("Operación no válida");
        }
    }
};
void modificar_matriz(int** matriz, Transformer transformer) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            matriz[i][j] = transformer(matriz[i][j]);  // Aplica la transformación a cada elemento
        }
    }
}
void print(int** matriz) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}
int main() {
    // Crear matriz dinámica 3x3
    int** M = new int*[3];
    for (int i = 0; i < 3; ++i) {
        M[i] = new int[3];
    }

    // Inicializar la matriz
    M[0][0] = 1; M[0][1] = 2; M[0][2] = 3;
    M[1][0] = 4; M[1][1] = 5; M[1][2] = 6;
    M[2][0] = 7; M[2][1] = 8; M[2][2] = 9;

    // Paso 1: Aplicar transformaciones
    Transformer transformer1("SUMAR", 3);
    modificar_matriz(M, transformer1);  // Paso 2
    print(M);  // Paso 3

    // Resetear la matriz y aplicar más transformaciones
    M[0][0] = 1; M[0][1] = 2; M[0][2] = 3;
    M[1][0] = 4; M[1][1] = 5; M[1][2] = 6;
    M[2][0] = 7; M[2][1] = 8; M[2][2] = 9;

    Transformer transformer2("RESTAR", 1);
    modificar_matriz(M, transformer2);
    print(M);

    Transformer transformer3("MULTIPLICAR", 2);
    modificar_matriz(M, transformer3);
    print(M);

    Transformer transformer4("DIVIDIR", 3);
    modificar_matriz(M, transformer4);
    print(M);

    // Liberar memoria
    for (int i = 0; i < 3; ++i) {
        delete[] M[i];
    }
    delete[] M;

    return 0;
}
