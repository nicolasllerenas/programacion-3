#include <iostream>
using namespace std;

class Item{
    friend class Pj;
private:
    string nombre;
    int curacion;
public:
    Item(string n, int c):nombre(n),curacion(c){}
};

class Carne: public Item{
public:
   Carne():Item("Carne",10){}
};

class Agua: public Item{
public:
    Agua():Item("Agua",8){}
};

class Magia: public Item{
public:
    Magia():Item("Magia",12){}
};
class Pj{
    friend ostream& operator<<(ostream& os, const Pj& pj);
private:
    string nombre;
    string raza;
    int vida;
    int ataque;
public:
    Pj(string n, string r, int v, int a): nombre(n),raza(r),vida(v),ataque(a){}
    void curar(const Item& item){
        vida += item.curacion;
    }
};

ostream& operator<<(ostream& os, const Pj& pj){
    os << "Nombre: " << pj.nombre << '\n';
    os << "Raza  : " << pj.raza << '\n';
    os << "Vida  : " << pj.vida << '\n';
    os << "Ataque: " << pj.ataque << '\n';
    return os;
}

int main() {
    Pj pj1("Orgrim","Orco",100,20); // Se cura con Carne
    Pj pj2("Legolas","Elfo",60,35); // Se cura con Magia
    Pj pj3("Aragorn","Humano",80,25); // Se cura con Agua

    Item carne1("Carne",10);
    Carne carne;

    Agua agua;
    Magia magia;

    pj1.curar(carne);
    pj2.curar(agua);
    pj3.curar(magia);

    cout << pj1 << pj2 << pj3;

}
