#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;

class Comentario {
private:
    string autor;
    string fecha;
    string contenido;

public:
    // Constructor por defecto
    Comentario() : autor(""), fecha(""), contenido("") {}
    
    Comentario(string _autor, string _fecha, string _contenido) 
        : autor(_autor), fecha(_fecha), contenido(_contenido) {}

    string getAutor() const { return autor; }
    string getFecha() const { return fecha; }
    string getContenido() const { return contenido; }
};

class Publicacion {
private:
    string autor;
    string fecha;
    string contenido;
    vector<Comentario> comentarios;

public:
    // Constructor por defecto
    Publicacion() : autor(""), fecha(""), contenido("") {}
    
    Publicacion(string _autor, string _fecha, string _contenido)
        : autor(_autor), fecha(_fecha), contenido(_contenido) {}

    void agregarComentario(const Comentario& comentario) {
        comentarios.push_back(comentario);
    }

    string getAutor() const { return autor; }
    string getFecha() const { return fecha; }
    const vector<Comentario>& getComentarios() const { return comentarios; }
};

class Usuario {
private:
    string nombre;
    string correo;
    string contrasena;
    vector<string> amigos;
    vector<Publicacion> publicaciones;

public:
    // Constructor por defecto
    Usuario() : nombre(""), correo(""), contrasena("") {}
    
    Usuario(string _nombre, string _correo, string _contrasena)
        : nombre(_nombre), correo(_correo), contrasena(_contrasena) {}

    void agregarAmigo(const string& correoAmigo) {
        amigos.push_back(correoAmigo);
    }

    void agregarPublicacion(const Publicacion& pub) {
        publicaciones.push_back(pub);
    }

    string getCorreo() const { return correo; }
    const vector<Publicacion>& getPublicaciones() const { return publicaciones; }
};

class RedSocial {
private:
    map<string, Usuario> usuarios;
    map<pair<string, string>, Publicacion> publicaciones;
    mutex mtx;
    condition_variable cv;
    bool hayPublicacion = false;

public:
    void registrarUsuario(const string& nombre, const string& correo, const string& contrasena) {
        lock_guard<mutex> lock(mtx);
        usuarios.emplace(correo, Usuario(nombre, correo, contrasena));
    }

    void crearPublicacion(const string& correoAutor, const string& fecha, const string& contenido) {
        lock_guard<mutex> lock(mtx);
        Publicacion pub(correoAutor, fecha, contenido);
        publicaciones[make_pair(correoAutor, fecha)] = pub;
        
        auto it = usuarios.find(correoAutor);
        if (it != usuarios.end()) {
            it->second.agregarPublicacion(pub);
        }
        
        hayPublicacion = true;
        cv.notify_all();
    }

    void comentarPublicacion(const string& correoAutor, const string& fechaPublicacion,
                           const string& correoComentador, const string& fechaComentario,
                           const string& contenidoComentario) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]() { return hayPublicacion; });

        auto it = publicaciones.find(make_pair(correoAutor, fechaPublicacion));
        if (it != publicaciones.end()) {
            Comentario comentario(correoComentador, fechaComentario, contenidoComentario);
            it->second.agregarComentario(comentario);
        }
    }

    void simularComentario(const string& correoComentador, const string& correoAutor,
                          const string& fechaPublicacion) {
        this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
        string fechaComentario = "2024-03-" + to_string(rand() % 30 + 1);
        string contenido = "Comentario de " + correoComentador;
        comentarPublicacion(correoAutor, fechaPublicacion, correoComentador,
                          fechaComentario, contenido);
    }

    // Método para mostrar el estado de la red social
    void mostrarEstado() {
        lock_guard<mutex> lock(mtx);
        cout << "\n=== Estado de la Red Social ===\n";
        for (const auto& [correo, usuario] : usuarios) {
            cout << "\nUsuario: " << correo << endl;
            for (const auto& pub : usuario.getPublicaciones()) {
                cout << "  Publicacion de " << pub.getAutor() << endl;
                cout << "  Comentarios:" << endl;
                for (const auto& com : pub.getComentarios()) {
                    cout << "    - " << com.getAutor() << ": " << com.getContenido() << endl;
                }
            }
        }
    }
};

int main() {
    RedSocial redSocial;
    
    // Registrar usuarios
    redSocial.registrarUsuario("Juan", "juan@mail.com", "pass123");
    redSocial.registrarUsuario("Ana", "ana@mail.com", "pass456");
    
    // Crear una publicación
    thread t1([&redSocial]() {
        redSocial.crearPublicacion("juan@mail.com", "2024-03-20", "Mi primera publicación!");
    });

    // Simular comentarios concurrentes
    vector<thread> hilosComentarios;
    vector<string> comentadores = {"ana@mail.com", "pedro@mail.com", "maria@mail.com"};
    
    for (const auto& comentador : comentadores) {
        hilosComentarios.push_back(thread(&RedSocial::simularComentario, &redSocial,
            comentador, "juan@mail.com", "2024-03-20"));
    }

    t1.join();
    for (auto& t : hilosComentarios) {
        t.join();
    }

    // Mostrar el estado final
    redSocial.mostrarEstado();

    return 0;
}