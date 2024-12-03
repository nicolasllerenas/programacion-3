#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct Solicitud {
    int _id;
    string _info;

    // Constructor de la clase Solicitud
    Solicitud(int id, string info) : _id(id), _info(info) {}
};

class Servidor {
private:
    queue<Solicitud> solicitudes;

public:
    // Método para agregar una solicitud y confirmar que fue agregada
    void agregarSolicitud(Solicitud sol) {
        solicitudes.push(sol);
        cout << "Solicitud agregada - ID: " << sol._id << endl;
    }

    // Método para procesar las solicitudes en el orden de recepción
    void procesarSolicitudes() {
        cout << "Procesando solicitudes..." << endl;
        while (!solicitudes.empty()) {
            Solicitud actual = solicitudes.front();
            cout << "Solicitud procesada - ID: " << actual._id
                 << ", Descripcion: " << actual._info << endl;
            solicitudes.pop();
        }
    }
};

int main() {
    Servidor servidor;

    Solicitud solicitud1(212, "Solicitud de acceso al sistema");
    Solicitud solicitud2(103, "Solicitud de actualizacion de datos");
    Solicitud solicitud3(111, "Solicitud de generacion de reporte");

    servidor.agregarSolicitud(solicitud1); // Salida: Solicitud agregada - ID: 212
    servidor.agregarSolicitud(solicitud2); // Salida: Solicitud agregada - ID: 103
    servidor.agregarSolicitud(solicitud3); // Salida: Solicitud agregada - ID: 111

    servidor.procesarSolicitudes();
    // Salida:
    // Procesando solicitudes...
    // Solicitud procesada - ID: 212, Descripcion: Solicitud de acceso al sistema
    // Solicitud procesada - ID: 103, Descripcion: Solicitud de actualizacion de datos
    // Solicitud procesada - ID: 111, Descripcion: Solicitud de generacion de reporte

    return 0;
}
