#include <iostream>
#include <cmath> // Para la función abs (valor absoluto)

using namespace std;

// Clase VehiculoAutonomo
class VehiculoAutonomo {
private:
    double posicion_x; // Posición en el eje X
    double velocidad_x; // Velocidad en el eje X

public:
    // Constructor para inicializar los atributos
    VehiculoAutonomo(double pos, double vel) : posicion_x(pos), velocidad_x(vel) {}

    // Sobrecarga del operador '>>' para simular el movimiento
    void operator>>(Obstaculo& obs) {
        // Distancia al obstáculo
        double distancia = abs(obs.getPosicion() - posicion_x);
        
        // Mover el vehículo
        posicion_x += velocidad_x;

        // Si la distancia es menor o igual a la velocidad (distancia recorrida en una iteración)
        if (distancia <= abs(velocidad_x)) {
            // Cambiar la dirección de la velocidad (girando)
            velocidad_x = -velocidad_x;
            cout << "Vehiculo giro, nueva velocidad: " << velocidad_x << endl;
        }

        cout << "Posicion del vehiculo: " << posicion_x << endl;
    }
};

// Clase Obstaculo
class Obstaculo {
private:
    double posicion_x; // Posición en el eje X

public:
    // Constructor para inicializar la posición del obstáculo
    Obstaculo(double pos) : posicion_x(pos) {}

    // Método para obtener la posición del obstáculo
    double getPosicion() const {
        return posicion_x;
    }
};

// Programa principal para validar la implementación
int main() {
    // Crear un vehículo autónomo con posición inicial 0 y velocidad 1.3
    VehiculoAutonomo v(0, 1.3);
    
    // Crear obstáculos en posiciones 10 y -20
    Obstaculo o1(10);
    Obstaculo o2(-20);

    // Avanzar el vehículo hacia o1 y o2
    v >> o1;
    v >> o2;

    return 0;
}
