#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <mutex>

using namespace std;

template<typename T>
void print(T begin, T end) {
    for_each(begin, end, [](double num) {
        cout << num << " ";
    });
    cout << endl;
}

template<typename T>
void print_mat(T begin, T end) {
    for_each(begin, end, [](vector<double> vec) {
        for_each(vec.begin(), vec.end(), [](double num) {
            cout << num << " ";
        });
        cout << endl;
    });
}

void g(vector<double>& y, const vector<vector<double>>& W, const vector<double>& x, const vector<double>& b, int total, int num) {
    int inicio = (num) * b.size() / total;
    int final = (num + 1) * b.size() / total;
    
    for (int i = inicio; i < final; i++) {
        double suma = 0; // Resetear suma en cada iteración de i
        for (auto j = 0u; j < W[i].size(); j++) {  // Usamos auto para deducir el tipo adecuado
            suma += W[i][j] * x[j];
        }
        y[i] = 1.0 / (1 + exp(-(suma + b[i]))); // Corregir la función de activación

        // Depuración: Mostrar valores intermedios para verificar el cálculo
        cout << "Iteración i = " << i << endl;
        cout << "  suma = " << suma << endl;
        cout << "  b[" << i << "] = " << b[i] << endl;
        cout << "  y[" << i << "] = " << y[i] << endl;
    }
}

int main() {
    srand(time(nullptr));

    int n = 10000;
    int m = 100;
    vector<double> x(n);
    vector<double> b(m);
    vector<vector<double>> W(m, vector<double>(n));  // Inicializamos correctamente W como m x n

    // Generar los valores para x (entre 0 y 1)
    generate(x.begin(), x.end(), []() {
        return ((double)rand()) / RAND_MAX;
    });

    print(x.begin(), x.end());
    cout << endl;

    // Generar los valores para W (entre 0 y 1)
    generate(W.begin(), W.end(), [n]() {
        vector<double> vec(n);
        generate(vec.begin(), vec.end(), []() {
            return ((double)rand()) / RAND_MAX;
        });
        return vec;
    });

    print_mat(W.begin(), W.end());
    cout << endl;

    // Generar los valores para b (entre -0.1 y 0.1)
    generate(b.begin(), b.end(), []() {
        return (((double)rand() / RAND_MAX) / 5) - 0.1;
    });

    print(b.begin(), b.end());
    cout << endl;

    // Crear vector para almacenar los resultados de y
    vector<double> y(m);

    // Crear varios hilos para paralelizar el cálculo de la función g
    int num_hilos = 4;
    vector<thread> hilos;
    
    for (int i = 0; i < num_hilos; ++i) {
        hilos.push_back(thread(g, ref(y), ref(W), ref(x), ref(b), num_hilos, i));
    }
    
    // Esperar a que todos los hilos terminen
    for (auto& hilo : hilos) {
        hilo.join();
    }

    // Imprimir el resultado final
    print(y.begin(), y.end());
    cout << endl;

    return 0;
}
