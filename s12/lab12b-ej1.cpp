#include <iostream>
#include <queue>
#include <string>

using namespace std;

class Banco {
private:
    queue<string> clientes;

public:
    // Método para agregar un cliente a la cola
    void agregarCliente(const string& nombre) {
        clientes.push(nombre);
        cout << "Cliente agregado: " << nombre << endl;
    }

    // Método para atender al próximo cliente
    void atenderCliente() {
        if (!clientes.empty()) {
            cout << "Atendiendo a " << clientes.front() << endl;
            clientes.pop();
        } else {
            cout << "No hay clientes en espera." << endl;
        }
    }

    // Método para mostrar los clientes en espera
    void mostrarClientesEnEspera() const {
        if (clientes.empty()) {
            cout << "No hay clientes en espera." << endl;
        } else {
            cout << "Clientes en espera:" << endl;
            int num = 1;
            queue<string> temp = clientes;  // Copia temporal para mostrar los clientes sin modificar la cola
            while (!temp.empty()) {
                cout << num << ". " << temp.front() << endl;
                temp.pop();
                num++;
            }
        }
    }
};

int main() {
    Banco banco;

    banco.agregarCliente("Juan");
    banco.agregarCliente("Maria");
    banco.agregarCliente("Pedro");
    banco.mostrarClientesEnEspera(); // 1. Juan 2. Maria 3. Pedro
    banco.atenderCliente();
    banco.mostrarClientesEnEspera(); // 1. Maria 2. Pedro
    banco.atenderCliente();
    banco.atenderCliente();
    banco.mostrarClientesEnEspera(); // No hay clientes en espera.

    return 0;
}
