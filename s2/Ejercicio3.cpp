#include <iostream>
using namespace std;

class Complejo {
private:
    double real;
    double imaginaria;

public:
    // Constructor por defecto
    Complejo(double r = 0.0, double i = 0.0) : real(r), imaginaria(i) {}

    // Sobrecarga del operador >>
    friend istream& operator>>(istream& in, Complejo& c) {
        cout << "Ingrese la parte real: ";
        in >> c.real;
        cout << "Ingrese la parte imaginaria: ";
        in >> c.imaginaria;
        return in;
    }

    // Sobrecarga del operador <<
    friend ostream& operator<<(ostream& out, const Complejo& c) {
        out << c.real << " + " << c.imaginaria << "i";
        return out;
    }

    // Sobrecarga del operador +
    Complejo operator+(const Complejo& c) const {
        return Complejo(real + c.real, imaginaria + c.imaginaria);
    }

    // Sobrecarga del operador -
    Complejo operator-(const Complejo& c) const {
        return Complejo(real - c.real, imaginaria - c.imaginaria);
    }

    // Sobrecarga del operador *
    Complejo operator*(const Complejo& c) const {
        double r = real * c.real - imaginaria * c.imaginaria;
        double i = real * c.imaginaria + imaginaria * c.real;
        return Complejo(r, i);
    }

    // Sobrecarga del operador ==
    bool operator==(const Complejo& c) const {
        return (real == c.real && imaginaria == c.imaginaria);
    }

    // Sobrecarga del operador ++ (pre-incremento)
    Complejo& operator++() {
        ++real;
        ++imaginaria;
        return *this;
    }

    // Sobrecarga del operador ++ (post-incremento)
    Complejo operator++(int) {
        Complejo temp = *this;
        real++;
        imaginaria++;
        return temp;
    }
};

int main() {
    Complejo c1, c2, c3;

    // Leer dos números complejos
    cout << "Ingrese el primer numero complejo:" << endl;
    cin >> c1;
    cout << "Ingrese el segundo numero complejo:" << endl;
    cin >> c2;

    // Sumar
    c3 = c1 + c2;
    cout << "Suma: " << c3 << endl;

    // Restar
    c3 = c1 - c2;
    cout << "Resta: " << c3 << endl;

    // Multiplicar
    c3 = c1 * c2;
    cout << "Multiplicacion: " << c3 << endl;

    // Comparar
    if (c1 == c2)
        cout << "Los numeros complejos son iguales." << endl;
    else
        cout << "Los numeros complejos son diferentes." << endl;

    // Incrementar (pre-incremento)
    ++c1;
    cout << "Primer numero complejo después de pre-incremento: " << c1 << endl;

    // Incrementar (post-incremento)
    c2++;
    cout << "Segundo numero complejo despues de post-incremento: " << c2 << endl;

    return 0;
}
