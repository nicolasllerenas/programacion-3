#include <iostream>
#include <string>
#include <vector>
#include <memory> // Para memoria dinámica
using namespace std;

// Clase base Personaje
class Personaje {
protected:
    string nombre;
    int puntos_vida;
    int puntos_mana;
    int puntos_ataque;
    int puntos_defensa;
    
public:
    // Constructor base
    Personaje(string nombre, int vida, int mana, int ataque, int defensa)
        : nombre(nombre), puntos_vida(vida), puntos_mana(mana), puntos_ataque(ataque), puntos_defensa(defensa) {}

    // Destructor virtual para soporte polimórfico
    virtual ~Personaje() {}

    // Función virtual pura para sobreescribir en las clases derivadas
    virtual void mostrarInfo() const = 0;

    // Función para atacar
    virtual void atacar(Personaje& objetivo) {
        cout << nombre << " ataca a " << objetivo.nombre << " causando " << puntos_ataque << " de daño." << endl;
        objetivo.recibirDanio(puntos_ataque);
    }
    
    // Función para recibir daño
    void recibirDanio(int danio) {
        puntos_vida -= danio;
        if (puntos_vida < 0) puntos_vida = 0;
    }

    // Función para mostrar el estado de vida
    bool estaVivo() const {
        return puntos_vida > 0;
    }

    string getNombre() const {
        return nombre;
    }

    // Operador de sobrecarga para comparar personajes
    bool operator==(const Personaje& otro) const {
        return nombre == otro.nombre;
    }

    // Función para obtener puntos de vida
    int getPuntosVida() const {
        return puntos_vida;
    }
};

// Clase Guerrero derivada de Personaje
class Guerrero : public Personaje {
public:
    Guerrero(string nombre) : Personaje(nombre, 200, 0, 30, 50) {}

    void mostrarInfo() const override {
        cout << "Guerrero: " << nombre << " | Vida: " << puntos_vida << " | Ataque: " << puntos_ataque << " | Defensa: " << puntos_defensa << endl;
    }
};

// Clase Mago derivada de Personaje
class Mago : public Personaje {
public:
    Mago(string nombre) : Personaje(nombre, 100, 200, 10, 20) {}

    void mostrarInfo() const override {
        cout << "Mago: " << nombre << " | Vida: " << puntos_vida << " | Maná: " << puntos_mana << " | Ataque: " << puntos_ataque << " | Defensa: " << puntos_defensa << endl;
    }

    // Sobrecarga de atacar para incluir el uso de magia
    void atacar(Personaje& objetivo) override {
        if (puntos_mana > 0) {
            cout << nombre << " lanza un hechizo a " << objetivo.getNombre() << " causando " << puntos_ataque << " de daño mágico." << endl;
            objetivo.recibirDanio(puntos_ataque);
            puntos_mana -= 20; // Cada hechizo consume 20 de maná
        } else {
            cout << nombre << " no tiene suficiente maná para atacar." << endl;
        }
    }
};

// Clase Jugador que puede tener múltiples personajes
class Jugador {
private:
    string nombre;
    vector<shared_ptr<Personaje>> personajes;

public:
    Jugador(string nombre) : nombre(nombre) {}

    // Función para agregar personajes
    void agregarPersonaje(shared_ptr<Personaje> personaje) {
        personajes.push_back(personaje);
    }

    // Mostrar información de los personajes del jugador
    void mostrarPersonajes() const {
        cout << "Jugador: " << nombre << endl;
        for (const auto& p : personajes) {
            p->mostrarInfo();
        }
    }

    // Seleccionar un personaje por nombre
    shared_ptr<Personaje> seleccionarPersonaje(string nombre_personaje) {
        for (const auto& p : personajes) {
            if (p->getNombre() == nombre_personaje) {
                return p;
            }
        }
        return nullptr; // No encontrado
    }
};

// Clase Grupo que contiene varios jugadores
class Grupo {
private:
    vector<shared_ptr<Jugador>> jugadores;

public:
    void agregarJugador(shared_ptr<Jugador> jugador) {
        jugadores.push_back(jugador);
    }

    void mostrarGrupo() const {
        for (const auto& j : jugadores) {
            j->mostrarPersonajes();
        }
    }
};

// Clase WoWWorld que maneja el mundo del juego
class WoWWorld {
private:
    Grupo grupo;

public:
    void agregarJugador(shared_ptr<Jugador> jugador) {
        grupo.agregarJugador(jugador);
    }

    void mostrarEstadoDelMundo() const {
        cout << "Estado del mundo WoW:" << endl;
        grupo.mostrarGrupo();
    }
};

int main() {
    // Crear personajes
    auto guerrero1 = make_shared<Guerrero>("Thorin");
    auto mago1 = make_shared<Mago>("Gandalf");

    // Crear jugador
    shared_ptr<Jugador> jugador1 = make_shared<Jugador>("Jugador1");
    jugador1->agregarPersonaje(guerrero1);
    jugador1->agregarPersonaje(mago1);

    // Crear mundo WoW
    WoWWorld mundo;
    mundo.agregarJugador(jugador1);

    // Mostrar estado del mundo
    mundo.mostrarEstadoDelMundo();

    // Combate entre personajes
    guerrero1->atacar(*mago1);
    mago1->atacar(*guerrero1);

    // Mostrar estado del mundo después del combate
    mundo.mostrarEstadoDelMundo();

    return 0;
}