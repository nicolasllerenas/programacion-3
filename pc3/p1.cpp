#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <memory>
#include <limits>
#include <algorithm>
#include <string>
#include <ctime>

using namespace std;


class Enemigo {
public:
    string nombre;
    int nivel;
    int vida;
    int ataque;
    int experiencia;

    Enemigo(string nom = "", int niv = 1, int vid = 100, int atq = 10) 
        : nombre(nom), nivel(niv), vida(vid), ataque(atq), experiencia(0) {}

    bool estaDerrotado() const {
        return vida <= 0;
    }

    void recibirDano(int dano) {
        vida -= dano;
        if (vida < 0) vida = 0;
    }
};

// Clase Grafo para representar mapa de enemigos
class GrafoEnemigos {
private:
    static const int TAMANO = 4;
    vector<vector<Enemigo>> matriz;
    vector<vector<int>> distancias;

public:
    GrafoEnemigos() {
        // Inicializar matriz con enemigos predefinidos
        matriz.resize(TAMANO, vector<Enemigo>(TAMANO));
        
        // Nombres de ejemplo para enemigos 
        vector<string> nombres = {
            "Creeper", "Enderman", "Skeleton", "Zombie", "Spider", 
            "Blaze", "Witch", "Slime", "Piglin", "Vindicator", 
            "Warden", "Wither", "Ghast", "Golem", "Ender Dragon", "Herobrine"
        };

        // Poblar matriz de enemigos
        for (int i = 0; i < TAMANO; ++i) {
            for (int j = 0; j < TAMANO; ++j) {
                int index = i * TAMANO + j;
                matriz[i][j] = Enemigo(
                    nombres[index], 
                    (index % 5) + 1,  // Nivel varía de 1 a 5
                    100 + (index * 10),  // Vida incrementa
                    10 + (index * 2)    // Ataque incrementa
                );
            }
        }

        // Inicializar distancias (todas iguales en este ejemplo)
        distancias.resize(TAMANO, vector<int>(TAMANO, 1));
    }

    // Método para navegar usando BFS
    vector<Enemigo*> navegarBFS(int filaInicio, int columnaInicio) {
        vector<vector<bool>> visitado(TAMANO, vector<bool>(TAMANO, false));
        queue<pair<int, int>> cola;
        vector<Enemigo*> rutaEnemigos;

        cola.push({filaInicio, columnaInicio});
        visitado[filaInicio][columnaInicio] = true;

        int direcciones[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        while (!cola.empty()) {
            auto [fila, columna] = cola.front();
            cola.pop();

            rutaEnemigos.push_back(&matriz[fila][columna]);

            for (auto& dir : direcciones) {
                int nuevaFila = fila + dir[0];
                int nuevaColumna = columna + dir[1];

                if (nuevaFila >= 0 && nuevaFila < TAMANO && 
                    nuevaColumna >= 0 && nuevaColumna < TAMANO &&
                    !visitado[nuevaFila][nuevaColumna]) {
                    
                    cola.push({nuevaFila, nuevaColumna});
                    visitado[nuevaFila][nuevaColumna] = true;
                }
            }
        }

        return rutaEnemigos;
    }

    Enemigo& obtenerEnemigo(int fila, int columna) {
        return matriz[fila][columna];
    }
};

// Patrón Singleton para gestionar jugadores
class GestorJugadores {
private:
    static GestorJugadores* instancia;
    map<string, pair<int, int>> jugadoresGuardados;

    GestorJugadores() {}

public:
    static GestorJugadores* obtenerInstancia() {
        if (!instancia) {
            instancia = new GestorJugadores();
        }
        return instancia;
    }

    void guardarProgreso(const string& nombreJugador, int fila, int columna) {
        jugadoresGuardados[nombreJugador] = {fila, columna};
    }

    bool existeJugador(const string& nombreJugador) {
        return jugadoresGuardados.find(nombreJugador) != jugadoresGuardados.end();
    }

    pair<int, int> obtenerUltimaPosicion(const string& nombreJugador) {
        return jugadoresGuardados[nombreJugador];
    }
};

// Inicializar el singleton
GestorJugadores* GestorJugadores::instancia = nullptr;

// Clase Principal del Juego
class JuegoEnemigos {
private:
    GrafoEnemigos grafo;
    stack<Enemigo*> historialDerrotas;
    string nombreJugador;
    int filaActual = 0, columnaActual = 0;
    GestorJugadores* gestorJugadores;

public:
    JuegoEnemigos() : gestorJugadores(GestorJugadores::obtenerInstancia()) {}

    void iniciarJuego() {
        mostrarMenuInicial();
    }

    void mostrarMenuInicial() {
        cout << "==== Sistema de gestion de enemigos ====\n";
        cout << "1. Continuar partida guardada\n";
        cout << "2. Nueva partida\n";
        cout << "Seleccione una opcion: ";

        int opcion;
        cin >> opcion;

        if (opcion == 1) {
            continuarPartidaGuardada();
        } else {
            nuevaPartida();
        }
    }

    void continuarPartidaGuardada() {
        cout << "Jugadores guardados:\n";
        // Mostrar jugadores guardados
        string nombreSeleccionado;
        cout << "Ingrese nombre de jugador: ";
        cin >> nombreSeleccionado;

        if (gestorJugadores->existeJugador(nombreSeleccionado)) {
            nombreJugador = nombreSeleccionado;
            auto [fila, columna] = gestorJugadores->obtenerUltimaPosicion(nombreJugador);
            filaActual = fila;
            columnaActual = columna;
            menuNavegacion();
        } else {
            cout << "Jugador no encontrado.\n";
            mostrarMenuInicial();
        }
    }

    void nuevaPartida() {
        cout << "Ingrese su nombre de jugador: ";
        cin >> nombreJugador;
        menuNavegacion();
    }

    void menuNavegacion() {
        while (true) {
            cout << "\n=== Navegacion ===\n";
            cout << "Posicion actual: [" << filaActual << "][" << columnaActual << "]\n";
            cout << "1. Avanzar\n";
            cout << "2. Retroceder\n";
            cout << "3. Pelear\n";
            cout << "4. Ver historial\n";
            cout << "5. Salir\n";
            cout << "Seleccione una opcion: ";

            int opcion;
            cin >> opcion;

            switch (opcion) {
                case 1: avanzar(); break;
                case 2: retroceder(); break;
                case 3: pelear(); break;
                case 4: verHistorial(); break;
                case 5: salir(); return;
            }
        }
    }

    void avanzar() {
        // Obtener los enemigos cercanos usando BFS
        auto rutaEnemigos = grafo.navegarBFS(filaActual, columnaActual);

        // Buscar el siguiente enemigo en la ruta (cualquier enemigo disponible)
        if (rutaEnemigos.size() > 1) {
            auto siguienteEnemigo = rutaEnemigos[1];  // Avanzamos al siguiente enemigo
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (&grafo.obtenerEnemigo(i, j) == siguienteEnemigo) {
                        filaActual = i;
                        columnaActual = j;
                        cout << "Avanzando a " << siguienteEnemigo->nombre << " en la posicion [" << filaActual << "][" << columnaActual << "]\n";
                        return;
                    }
                }
            }
        } else {
            cout << "No hay enemigos cerca para avanzar.\n";
        }
    }

    void retroceder() {
        // Obtener los enemigos cercanos usando BFS
        auto rutaEnemigos = grafo.navegarBFS(filaActual, columnaActual);

        // Buscar el enemigo anterior en la ruta
        if (rutaEnemigos.size() > 1) {
            auto anteriorEnemigo = rutaEnemigos[rutaEnemigos.size() - 2];
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (&grafo.obtenerEnemigo(i, j) == anteriorEnemigo) {
                        filaActual = i;
                        columnaActual = j;
                        cout << "Retrocediendo a " << anteriorEnemigo->nombre << " en la posicion [" << filaActual << "][" << columnaActual << "]\n";
                        return;
                    }
                }
            }
        } else {
            cout << "No se puede retroceder más.\n";
        }
    }

    void pelear() {
        Enemigo& enemigo = grafo.obtenerEnemigo(filaActual, columnaActual);
        cout << "Te has enfrentado a " << enemigo.nombre << "!\n";
        
        // Simulación de pelea
        enemigo.recibirDano(20);  // Hacer daño
        historialDerrotas.push(&enemigo);

        if (enemigo.estaDerrotado()) {
            cout << enemigo.nombre << " ha sido derrotado.\n";
            gestorJugadores->guardarProgreso(nombreJugador, filaActual, columnaActual);
        }
    }

    void verHistorial() {
        cout << "Historial de derrotas:\n";
        while (!historialDerrotas.empty()) {
            auto enemigo = historialDerrotas.top();
            cout << "Derrotado: " << enemigo->nombre << "\n";
            historialDerrotas.pop();
        }
    }

    void salir() {
        cout << "Hasta pronto!\n";
    }
};

int main() {
    std::srand(std::time(nullptr));
    JuegoEnemigos juego;
    juego.iniciarJuego();
    return 0;
}