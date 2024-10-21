#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

// Función para calcular la derivada numérica
double derivada(function<double(double)> func, double x, double h = 1e-5) {
    return (func(x + h) - func(x - h)) / (2 * h);
}

// Método de Newton-Raphson
double newton_raphson(function<double(double)> func, double x0, int max_iter = 1000, double tol = 1e-5) {
    double x = x0;
    for (int i = 0; i < max_iter; ++i) {
        double f_x = func(x);
        double f_prime_x = derivada(func, x);
        
        if (fabs(f_prime_x) < tol) break;  // Evitar división por cero
        
        double x_new = x - f_x / f_prime_x;
        
        if (fabs(x_new - x) < tol) return x_new;
        
        x = x_new;
    }
    return x;
}

// Función para calcular la integral numérica usando la regla del trapecio
double integrar(function<double(double)> func, double a, double b, int n = 1000) {
    double h = (b - a) / n;
    double suma = 0.5 * (func(a) + func(b));

    for (int i = 1; i < n; ++i) {
        suma += func(a + i * h);
    }

    return suma * h;
}

// Función para calcular la segunda derivada numérica
double segunda_derivada(function<double(double)> func, double x, double h = 1e-5) {
    return (func(x + h) - 2 * func(x) + func(x - h)) / (h * h);
}

int main() {
    // 1. Método de Newton-Raphson para la ecuación: -4x + cos(x) + 2 = 0
    auto funcion1 = [](double x) {
        return -4 * x + cos(x) + 2;
    };

    double raiz = newton_raphson(funcion1, 0.5);  // Punto inicial
    cout << "Raiz aproximada de -4x + cos(x) + 2 = 0: " << raiz << endl;

    // 2. Integral de cos(x) * sin(x) entre 0 y 2PI
    auto funcion2 = [](double x) {
        return cos(x) * sin(x);
    };

    double resultado_integral = integrar(funcion2, 0, 2 * M_PI);
    cout << "Integral de cos(x) * sin(x) entre 0 y 2PI: " << resultado_integral << endl;

    // 3. Verificar convexidad de f(x) = 2x^3 - 6x^2 + 13x - 7 en x0 = 2
    auto funcion3 = [](double x) {
        return 2 * pow(x, 3) - 6 * pow(x, 2) + 13 * x - 7;
    };

    double x0 = 2.0;
    double segunda_der = segunda_derivada(funcion3, x0);

    cout << "Segunda derivada de f(x) en x0 = " << x0 << " es: " << segunda_der << endl;

    if (segunda_der > 0) {
        cout << "La funcion es convexa en x0 = " << x0 << endl;
    } else {
        cout << "La funcion es cóncava en x0 = " << x0 << endl;
    }

    return 0;
}
