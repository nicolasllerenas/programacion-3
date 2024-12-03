#include <iostream>
#include <memory>
#include <queue>
#include <string>

using namespace std;

// Definimos las clases de armas y armaduras
class Arma {
public:
    virtual void usar() = 0;
    virtual ~Arma() = default;
};

class Armadura {
public:
    virtual void usar() = 0;
    virtual ~Armadura() = default;
};

class Hacha : public Arma {
public:
    void usar() override {
        cout << "Usando Hacha." << endl;
    }
};

class Malla : public Armadura {
public:
    void usar() override {
        cout << "Usando Malla." << endl;
    }
};

class Flecha : public Arma {
public:
    void usar() override {
        cout << "Usando Flecha." << endl;
    }
};

class Cuero : public Armadura {
public:
    void usar() override {
        cout << "Usando Cuero." << endl;
    }
};

// Clase Jugador
class Jugador {
public:
    string nombre;
    Jugador(const string& nombre) : nombre(nombre) {}
    virtual void elegirEquipo() = 0;
    virtual ~Jugador() = default;
};

// Clase CuerpoACuerpo
class CuerpoACuerpo : public Jugador {
private:
    unique_ptr<Arma> arma;
    unique_ptr<Armadura> armadura;

public:
    CuerpoACuerpo(const string& nombre) : Jugador(nombre) {}

    void elegirEquipo() override {
        arma = make_unique<Hacha>();   // Se crea un Hacha
        armadura = make_unique<Malla>(); // Se crea una Malla
        cout << "Jugador " << nombre << " eligio un Hacha y una Malla." << endl;
    }
};

// Clase ADistancia
class ADistancia : public Jugador {
private:
    unique_ptr<Arma> arma;
    unique_ptr<Armadura> armadura;

public:
    ADistancia(const string& nombre) : Jugador(nombre) {}

    void elegirEquipo() override {
        arma = make_unique<Flecha>();  // Se crea una Flecha
        armadura = make_unique<Cuero>();  // Se crea una armadura de Cuero
        cout << "Jugador " << nombre << " eligio una Flecha y una armadura de Cuero." << endl;
    }
};

// Clase Equipo
class Equipo {
private:
    queue<shared_ptr<Jugador>> colaJugadores;

public:
    void agregarJugador(shared_ptr<Jugador> jugador) {
        colaJugadores.push(jugador);
    }

    void mostrarJugadores() {
        while (!colaJugadores.empty()) {
            shared_ptr<Jugador> jugador = colaJugadores.front();
            colaJugadores.pop();
            jugador->elegirEquipo();
        }
    }
};

int main() {
    // Creamos un equipo
    Equipo equipo;

    // Agregamos jugadores al equipo
    equipo.agregarJugador(make_shared<CuerpoACuerpo>("Jugador1"));
    equipo.agregarJugador(make_shared<ADistancia>("Jugador2"));

    // Mostramos los jugadores y sus elecciones de equipo
    equipo.mostrarJugadores();

    return 0;
}
