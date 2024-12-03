#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set> // Para evitar nodos repetidos

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

    // Método BFS para explorar hasta una profundidad específica
    void BFS(T origen, int profundidad_max) {
        queue<pair<T, int>> q; // Cola para BFS (nodo, profundidad actual)
        set<T> visitado; // Para evitar visitar el mismo nodo más de una vez

        q.push({origen, 0}); // Iniciar desde el nodo origen con profundidad 0
        visitado.insert(origen);

        cout << "Explorando -> " << origen << endl;

        while (!q.empty()) {
            T nodo = q.front().first;
            int profundidad = q.front().second;
            q.pop();

            // Si alcanzamos la profundidad máxima, no exploramos más
            if (profundidad >= profundidad_max) {
                continue;
            }

            // Explorar vecinos
            for (auto vecino : adjList[nodo]) {
                if (visitado.find(vecino) == visitado.end()) { // Si no ha sido visitado
                    q.push({vecino, profundidad + 1});
                    visitado.insert(vecino);
                    cout << "Explorando -> " << vecino << endl;
                }
            }
        }
    }
};

int main() {
    Grafo<string> g;
    g.nueva_arista("http://www.google.com", "http://www.google.com/finance");
    g.nueva_arista("http://www.google.com", "http://www.google.com/maps");
    g.nueva_arista("http://www.google.com", "http://www.google.com/translate");
    g.nueva_arista("http://www.google.com", "http://www.facebook.com");
    g.nueva_arista("http://www.facebook.com", "http://www.facebook.com/MarkZuckerberg");
    g.nueva_arista("http://www.facebook.com/MarkZuckerberg", "http://www.facebook.com/MarkZuckerberg/photos");
    g.nueva_arista("http://www.google.com", "http://www.twitter.com");
    g.nueva_arista("http://www.twitter.com", "http://www.twitter.com/ElonMusk");
    g.nueva_arista("http://www.twitter.com/ElonMusk", "http://www.twitter.com/ElonMusk/last_tweet");
    g.nueva_arista("http://www.google.com", "http://www.youtube.com");
    g.nueva_arista("http://www.google.com", "http://utec.edu.pe");

    g.BFS("http://www.google.com", 1); // Profundidad máxima 1

    return 0;
}
