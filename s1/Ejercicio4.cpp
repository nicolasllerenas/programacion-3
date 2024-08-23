#include <iostream>
#include <string> // Para std::string

using namespace std;

class Personaje {
private:
    string nombre; // Nombre del personaje
    int vida;      // Vida del personaje
    int ataque;    // Ataque del personaje
    int defensa;   // Defensa del personaje

public:
    // Constructor para inicializar todos los atributos
    Personaje(const string& n, int v, int a, int d) 
        : nombre(n), vida(v), ataque(a), defensa(d) {}

    // Constructor de copia
    Personaje(const Personaje& other) 
        : nombre(other.nombre), vida(other.vida), ataque(other.ataque), defensa(other.defensa) {}

    // Método para cambiar el nombre del personaje
    void set_nombre(const string& n) {
        nombre = n;
    }

    // Método para imprimir la información del personaje
    void print() const {
        cout << "Nombre: " << nombre << endl;
        cout << "Vida: " << vida << endl;
        cout << "Ataque: " << ataque << endl;
        cout << "Defensa: " << defensa << endl;
    }
};

int main() {
    // Crear un personaje
    Personaje p1("Pedro", 12, 8, 10);
    cout << "Personaje 1:" << endl;
    p1.print();

    // Crear un nuevo personaje usando el constructor de copia
    Personaje p2 = p1; // Copia el personaje
    p2.set_nombre("Mago"); // Cambia el nombre

    cout << "\nPersonaje 2 (despues de cambiar el nombre):" << endl;
    p2.print();

    return 0;
}
