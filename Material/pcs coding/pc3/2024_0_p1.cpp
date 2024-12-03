#include <iostream>
#include <vector>
#include <string>

using namespace std;  // Permite usar los elementos de la biblioteca estándar sin std::

class Version {
public:
    int id;
    string description;
    vector<string> files;

    // Constructor por defecto
    Version() : id(0), description(""), files() {}

    // Constructor con parámetros
    Version(int id, const string& description, const vector<string>& files)
        : id(id), description(description), files(files) {}

    // Método para mostrar la versión
    void show() const {
        cout << "ID: " << id << ", Descripción: " << description << endl;
        cout << "Archivos: ";
        for (const auto& file : files) {
            cout << file << " ";
        }
        cout << endl;
    }
};

class GitCode {
private:
    vector<Version> versions;  // Almacena todas las versiones

public:
    // Método para agregar un nuevo cambio
    void addChange(const vector<string>& changedFiles, const string& description) {
        int newId = versions.size() + 1;  // ID basado en el tamaño de versiones
        versions.push_back(Version(newId, description, changedFiles));
    }

    // Método para mostrar todos los estados guardados
    void showAllVersions() const {
        if (versions.empty()) {
            cout << "No hay versiones guardadas." << endl;
            return;
        }
        for (const auto& version : versions) {
            version.show();
        }
    }

    // Método para restaurar una versión específica
    void restoreVersion(int id) {
        // Comprobamos que la versión con el ID existe
        if (id <= 0 || id > versions.size()) {
            cout << "Versión no válida." << endl;
            return;
        }
        versions[id - 1].show();
    }
};

int main() {
    GitCode git;  // Crear el sistema de control de versiones

    // Agregar algunos cambios
    git.addChange({"file1.cpp", "file2.cpp"}, "Version inicial");
    git.addChange({"file3.cpp", "file4.cpp"}, "Anadir nueva funcionalidad");
    git.addChange({"file5.cpp"}, "Corregir errores");

    // Mostrar todas las versiones
    cout << "Versiones guardadas:" << endl;
    git.showAllVersions();

    // Restaurar una versión específica
    cout << "\nRestaurando version 2:" << endl;
    git.restoreVersion(2);

    return 0;
}
