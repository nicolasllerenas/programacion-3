#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <limits> // Para usar std::numeric_limits

using namespace std;

template <typename T>
class Grafo {
private:
    map<T, vector<T>> adjList; // Lista de adyacencia

public:
    // Método para agregar una nueva arista
    void nueva_arista(T u, T v) {
        adjList[u].push_back(v); // Añadir v a la lista de u
        adjList[v].push_back(u); // Añadir u a la lista de v (grafo no dirigido)
    }

    // Método para calcular el número mínimo de aristas entre dos nodos utilizando BFS
    int aristas(T inicio, T fin) {
        if (inicio == fin) return 0;

        map<T, bool> visitado; // Mapa para marcar nodos visitados
        map<T, int> distancia; // Mapa para almacenar distancias desde el nodo inicial

        // Inicializar nodos como no visitados y con distancia infinita
        for (auto& nodo : adjList) {
            visitado[nodo.first] = false;
            distancia[nodo.first] = numeric_limits<int>::max();
        }

        // Cola para BFS
        queue<T> q;
        q.push(inicio);
        visitado[inicio] = true;
        distancia[inicio] = 0;

        // BFS
        while (!q.empty()) {
            T nodo = q.front();
            q.pop();

            for (auto vecino : adjList[nodo]) {
                if (!visitado[vecino]) {
                    q.push(vecino);
                    visitado[vecino] = true;
                    distancia[vecino] = distancia[nodo] + 1;

                    // Si llegamos al nodo final, devolvemos la distancia
                    if (vecino == fin) {
                        return distancia[vecino];
                    }
                }
            }
        }

        // Si no se encuentra un camino, devolvemos -1
        return -1;
    }
};

int main() {
    Grafo<char> g;
    g.nueva_arista('A', 'B'); // Grafo no dirigido
    g.nueva_arista('A', 'C');
    g.nueva_arista('A', 'F');
    g.nueva_arista('B', 'E');
    g.nueva_arista('B', 'D');
    g.nueva_arista('C', 'E');
    g.nueva_arista('F', 'G');
    g.nueva_arista('G', 'D');

    cout << "Aristas: " << g.aristas('A', 'D') << endl; 
    // Salida esperada: 2

    return 0;
}
