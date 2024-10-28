#include <iostream>
#include <cmath> // Para fabs()
using namespace std;

class Obstaculo {
private:
    double posicionX;

public:
    // Constructor para inicializar la posición del obstáculo
    Obstaculo(double x) : posicionX(x) {}

    // Método para obtener la posición del obstáculo
    double getPosicionX() const {
        return posicionX;
    }
};

class VehiculoAutonomo {
private:
    double posicionX;
    double velocidadX;

public:
    // Constructor para inicializar la posición y la velocidad del vehículo
    VehiculoAutonomo(double pos, double vel) : posicionX(pos), velocidadX(vel) {}

    // Sobrecarga del operador >>
    VehiculoAutonomo& operator>>(const Obstaculo& obstaculo) {
        while (true) {
            // Mostrar la posición actual del vehículo antes de moverse
            cout << "Avanzando... Posicion: " << posicionX << endl;

            // Actualizar la posición del vehículo
            posicionX += velocidadX;

            // Verificar si se detecta un obstáculo
            if (fabs(obstaculo.getPosicionX() - posicionX) <= fabs(velocidadX)) {
                cout << "Obstaculo detectado!" << endl;
                cout << "Girando..." << endl;

                // Invertir la dirección del vehículo
                velocidadX = -velocidadX;

                // Avanzar una vez después de girar
                posicionX += velocidadX;
                cout << "Avanzando... Posicion: " << posicionX << endl;
                break;
            }
        }
        return *this;
    }
};

int main() {
    // Crear el vehículo y los obstáculos
    VehiculoAutonomo v(0, 1.3);
    Obstaculo o1(9.1); // El obstáculo está en la posición 9.1
    
    // Avanzar y detectar obstáculo
    v >> o1;

    Obstaculo o2(-20);
    v >> o2;

    return 0;
}
