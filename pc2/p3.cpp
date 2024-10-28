#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

class BaseDatos {
    int data;  // La base de datos compartida (en este caso un entero)
    int num_lectores;  // Número de lectores leyendo
    bool escritor_activo;  // Indica si hay un escritor activo
    mutex mtx;  // Mutex para exclusión mutua
    condition_variable cv_leer, cv_escribir;  // Variables de condición para sincronización

public:
    BaseDatos() : data(0), num_lectores(0), escritor_activo(false) {}

    // Función para que los lectores lean la base de datos
    void leer(int id) {
        unique_lock<mutex> lock(mtx);
        // Esperar si hay un escritor activo
        cv_leer.wait(lock, [this]() { return !escritor_activo; });

        // Incrementar el número de lectores
        num_lectores++;
        lock.unlock();

        // Leer el dato
        cout << "Lector " << id << " lee el valor: " << data << endl;
        this_thread::sleep_for(chrono::milliseconds(100));  // Simular tiempo de lectura

        // Cuando el lector termina de leer
        lock.lock();
        num_lectores--;
        if (num_lectores == 0) {
            cv_escribir.notify_one();  // Si no hay más lectores, notificar a los escritores
        }
    }

    // Función para que los escritores escriban en la base de datos
    void escribir(int id, int nuevo_valor) {
        unique_lock<mutex> lock(mtx);
        // Esperar hasta que no haya lectores ni escritores activos
        cv_escribir.wait(lock, [this]() { return !escritor_activo && num_lectores == 0; });

        // Marcar que un escritor está activo
        escritor_activo = true;

        // Escribir el nuevo valor
        cout << "Escritor " << id << " escribe el valor: " << nuevo_valor << endl;
        data = nuevo_valor;
        this_thread::sleep_for(chrono::milliseconds(100));  // Simular tiempo de escritura

        // Marcar que el escritor ha terminado
        escritor_activo = false;

        // Notificar a los lectores y escritores
        cv_leer.notify_all();
        cv_escribir.notify_one();
    }
};

// Función que simula la lectura repetida
void lector(BaseDatos& bd, int id) {
    for (int i = 0; i < 5; ++i) {
        bd.leer(id);
        this_thread::sleep_for(chrono::milliseconds(150));  // Tiempo de espera antes de la próxima lectura
    }
}

// Función que simula la escritura repetida
void escritor(BaseDatos& bd, int id) {
    for (int i = 0; i < 5; ++i) {
        bd.escribir(id, id * 10 + i);  // Escribir un valor basado en el id y el número de iteración
        this_thread::sleep_for(chrono::milliseconds(200));  // Tiempo de espera antes de la próxima escritura
    }
}

int main() {
    BaseDatos bd;

    // Crear hilos para múltiples lectores y escritores
    vector<thread> lectores, escritores;

    // Iniciar 3 lectores y 2 escritores
    for (int i = 0; i < 3; ++i) {
        lectores.push_back(thread(lector, ref(bd), i + 1));
    }
    for (int i = 0; i < 2; ++i) {
        escritores.push_back(thread(escritor, ref(bd), i + 1));
    }

    // Esperar a que todos los hilos terminen
    for (auto& t : lectores) {
        t.join();
    }
    for (auto& t : escritores) {
        t.join();
    }

    return 0;
}
