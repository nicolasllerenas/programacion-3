#include <iostream>
#include <string>

using namespace std;

class Pj {
private:
    string nombre;
    string raza;
    int vida;
    int ataque;

public:
    Pj(string n, string r, int v, int a) : nombre(n), raza(r), vida(v), ataque(a) {}

    // Operador >> para atacar a otro personaje
    void operator>>(Pj& otro) {
        otro.vida -= this->ataque;
        if (otro.vida < 0) otro.vida = 0;
        cout << this->nombre << " ataca a " << otro.nombre << " causando " << this->ataque << " de daño." << endl;
    }

    // Operador + para recuperar vida
    void operator+(int cantidad) {
        this->vida += cantidad;
        cout << this->nombre << " recupera " << cantidad << " puntos de vida." << endl;
    }

    // Operador << para visualizar atributos
    friend ostream& operator<<(ostream& os, const Pj& pj) {
        os << "Nombre: " << pj.nombre << ", Raza: " << pj.raza 
           << ", Vida: " << pj.vida << ", Ataque: " << pj.ataque;
        return os;
    }
};

int main() {
    Pj orco("Gromash", "Orco", 100, 15);
    Pj humano("Arthas", "Humano", 80, 12);
    Pj elfo("Legolas", "Elfo", 70, 10);

    cout << "Estado inicial:" << endl;
    cout << orco << endl;
    cout << humano << endl;
    cout << elfo << endl;

    cout << "\nAcciones:" << endl;
    orco >> humano;
    humano + 5;
    elfo >> orco;

    cout << "\nEstado final:" << endl;
    cout << orco << endl;
    cout << humano << endl;
    cout << elfo << endl;

    return 0;
}