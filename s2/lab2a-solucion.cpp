#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Pj{
    friend ostream& operator<<(ostream& os, const Pj& pj);
private:
    string nombre;
    string raza;
    int vida;
    int ataque;
public:
    Pj(string n, string r, int v, int a): nombre(n),raza(r),vida(v),ataque(a){}
    void operator>>(Pj& pj_derecha){
        cout << nombre << " atacando a " << pj_derecha.nombre << "...\n";
        pj_derecha.vida -= this->ataque;
    }
    void operator+(int puntos){
        cout << nombre << " recuperando " << puntos << " puntos de vida...\n";
        vida += puntos;
    }
};
/*
void operator+(Pj& pj, int puntos){
    cout << pj.nombre << " recuperando " << puntos << " puntos de vida...\n";
    pj.vida += puntos;
}
*/
ostream& operator<<(ostream& os, const Pj& pj){
    os << "-----------------------------\n";
    os << "Nombre: " << pj.nombre << '\n';
    os << "Raza  : " << pj.raza << '\n';
    os << "Vida  : " << pj.vida << '\n';
    os << "Ataque: " << pj.ataque;
    return os;
}

class Cartas{
    friend void operator<<(ostream& os, const Cartas& C);
private:
    vector<int> cartas;
    void barajar(){
        for(int i=0; i < 52; i++) {
            int r = rand() % 52;
            swap(cartas[i], cartas[r]);
        }

    }
public:
    Cartas(){
        /*
         * 0 -12: Trebol
         * 13-25: Espada
         * 26-38: Diamante
         * 39-51: Corazones
         */
        for(int i=0; i < 52; i++)
            cartas.push_back(i); // 0,1,2,3,...,51
    }
    void operator>>(int n){
        // Ejecutamos el "random_shuffle" una cantidad de 'n' veces
        for(int i=0; i < n; ++i)
            random_shuffle(cartas.begin(), cartas.end());
    }
};

void operator<<(ostream& os, const Cartas& C){
    int x = C.cartas[0];
    int y = C.cartas[1];
    int z = C.cartas[2];

    int x_num = x % 13; //  1 (1T) == 14 (1E)
    int y_num = y % 13;
    int z_num = z % 13;
    int puntos = 0;
    if (x_num == y_num or y_num == z_num or x_num == z_num)
        puntos += 1;
    if (x / 13 == y / 13 and x/13 == z/13)  // 3 5 12
        puntos += 1;


}

// Ej. 2
class Comp{
    friend Comp operator+(const Comp& c1, const Comp& c2);
    friend istream& operator>>(istream& is, Comp& C);
private:
    double real;
    double imag;
public:
    Comp(){}
    Comp(double r, double i): real(r), imag(i){}
};

istream& operator>>(istream& is, Comp& C){
    cout << "Parte Real: ";
    is >> C.real;
    cout << "Parte Imag: ";
    is >> C.imag;
    return is;
}

Comp operator+(const Comp& c1, const Comp& c2){
    return Comp(c1.real+c2.real, c1.imag + c2.imag);
}
int main() {
    /*
    // Ej. 1
    Pj orco("Orgrim", "Orco", 100, 20);
    Pj humano("Humano", "Humano", 80, 30);

    orco >> humano;

    cout << orco << endl;
    cout << humano << endl;

    humano+10;
    cout << humano << endl;
     */
    /*
     * // Ej 2
    // +1pt : Dos cartas de igual valor
    // +1pt : Las tres cartas del mismo simbolo
    // +2pt : Las tres cartas del mismo valor o escalera
    Cartas cartas;
    int N;
    cout << "Ingrese N: ";
    cin >> N;
    if (N > 1){
        cartas >> N;
    }
    return 0;
    */
    Comp c1(1,2);
    Comp c2(3,4);
    Comp c3;
    cin >> c3;
    Comp c4 = c1 + c2;
}
