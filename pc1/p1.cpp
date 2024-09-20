#include <iostream>
#include <string>
using namespace std;

// Clase base abstracta Personaje
template <typename T>
class Personaje {
protected:
    T salud;
    T ataque;
    T defensa;

public:
    // Constructor
    Personaje(T salud, T ataque, T defensa) : salud(salud), ataque(ataque), defensa(defensa) {}

    // Métodos virtuales 
    virtual void atacar(Personaje& otro) = 0;
    virtual void defenderse() = 0;
    virtual void usarHabilidad(Personaje& otro) = 0;

    // Función getter para salud
    T getSalud() const {
        return salud;
    }

    // Función setter para salud
    void setSalud(T nuevaSalud) {
        salud = nuevaSalud;
    }

    // Función getter para defensa
    T getDefensa() const {
        return defensa;
    }

    // Destructor 
    virtual ~Personaje() {}
};

// Clase Guerrero derivada de Personaje
template <typename T>
class Guerrero : public Personaje<T> {
public:
    Guerrero(T salud, T ataque, T defensa) : Personaje<T>(salud, ataque, defensa) {}

    void atacar(Personaje<T>& otro) override {
        cout << "El guerrero ataca con fuerza fisica!" << endl;
        T danio = this->ataque - otro.getDefensa();
        if (danio > 0) {
            otro.setSalud(otro.getSalud() - danio);
            cout << "El otro personaje pierde " << danio << " puntos de salud." << endl;
        } else {
            cout << "El ataque no causa danio." << endl;
        }
    }

    void defenderse() override {
        cout << "El guerrero se defiende, reduciendo el danio entrante." << endl;
        this->defensa += 10; // Mejora temporal de la defensa
    }

    void usarHabilidad(Personaje<T>& otro) override {  
        cout << "El guerrero usa una habilidad especial de aumento de ataque!" << endl;
        this->ataque += 20; // Mejora temporal del ataque
    }
};

// Clase Mago derivada de Personaje
template <typename T>
class Mago : public Personaje<T> {
private:
    T mana;

public:
    Mago(T salud, T ataque, T defensa, T mana) : Personaje<T>(salud, ataque, defensa), mana(mana) {}

    void atacar(Personaje<T>& otro) override {
        if (mana > 10) {
            cout << "El mago lanza un hechizo ofensivo!" << endl;
            mana -= 10;
            T danio = this->ataque - otro.getDefensa();
            if (danio > 0) {
                otro.setSalud(otro.getSalud() - danio);
                cout << "El otro personaje pierde " << danio << " puntos de salud." << endl;
            } else {
                cout << "El hechizo no causa danio." << endl;
            }
        } else {
            cout << "El mago no tiene suficiente mana!" << endl;
        }
    }

    void defenderse() override {
        cout << "El mago se defiende con un escudo magico." << endl;
        this->defensa += 15; // Mejora temporal de la defensa
    }

    void usarHabilidad(Personaje<T>& otro) override {
        if (mana >= 20) {
            cout << "El mago lanza un hechizo que ignora la defensa del enemigo!" << endl;
            mana -= 20;
            otro.setSalud(otro.getSalud() - this->ataque);
            cout << "El otro personaje pierde " << this->ataque << " puntos de salud sin considerar la defensa." << endl;
        } else {
            cout << "No hay suficiente mana para usar esta habilidad." << endl;
        }
    }
};

// Clase Arquero derivada de Personaje
template <typename T>
class Arquero : public Personaje<T> {
private:
    T precision;
    T velocidad;

public:
    Arquero(T salud, T ataque, T defensa, T precision, T velocidad)
        : Personaje<T>(salud, ataque, defensa), precision(precision), velocidad(velocidad) {}

    void atacar(Personaje<T>& otro) override {
        cout << "El arquero dispara flechas rapidas!" << endl;
        if (velocidad > 50) {
            T danio = (this->ataque * precision / 100) - otro.getDefensa();
            if (danio > 0) {
                otro.setSalud(otro.getSalud() - danio);
                cout << "El otro personaje pierde " << danio << " puntos de salud." << endl;
            } else {
                cout << "El ataque del arquero no causa danio." << endl;
            }
        } else {
            cout << "El arquero no tiene suficiente velocidad para atacar dos veces." << endl;
        }
    }

    void defenderse() override {
        cout << "El arquero esquiva rapidamente el ataque." << endl;
        this->defensa += 5; // Mejora temporal de la defensa
    }

    void usarHabilidad(Personaje<T>& otro) override {
        cout << "El arquero usa 'Disparo Critico'!" << endl;
        T danio = (this->ataque * precision / 100) * 1.5;
        otro.setSalud(otro.getSalud() - danio);
        cout << "El otro personaje pierde " << danio << " puntos de salud." << endl;
    }
};

// Sobrecarga del operador +
template <typename T>
T operator+(const T& atributo, const T& objeto) {
    return atributo + objeto; // Suma el atributo con el poder de un objeto
}

// Variadic Template para ejecutar múltiples acciones
template <typename T, typename CharT, typename... Actions>
void ejecutarAcciones(CharT& personaje, Personaje<T>& objetivo, Actions... acciones) {
    (void)std::initializer_list<int>{((personaje.*acciones)(objetivo), 0)...};
}

template <typename T>
void ejecutarDefensa(Personaje<T>& personaje) {
    personaje.defenderse();
}

int main() {
    // Creamos los personajes
    Guerrero<int> guerrero(100, 30, 20);
    Mago<int> mago(80, 25, 10, 50);
    Arquero<int> arquero(90, 20, 15, 80, 60);

    // Combate
    guerrero.atacar(mago);
    mago.usarHabilidad(guerrero);
    arquero.atacar(mago);

    // Variadic template: ejecutar múltiples acciones (ataque y habilidad)
    cout << "\nEl arquero realiza varias acciones en un solo turno:\n";
    ejecutarAcciones<int>(arquero, mago, &Arquero<int>::atacar, &Arquero<int>::usarHabilidad); //Varias acciones en un solo turno
    ejecutarDefensa(arquero); //El arquero esquiva rapidamente el ataque

    return 0;
}