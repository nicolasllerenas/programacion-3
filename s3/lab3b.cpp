#include <iostream>
#include <vector>
#include <cmath>
#include <list>
using namespace std;

template<typename T>
string a_string(T x){
    string s = "";
    if (x > 0){
        s+= "+";
        s+= to_string(x);
    }
    else if (x < 0){
        s += to_string(x);
    }
    return s;
}

double r(){
    return (double)rand()/RAND_MAX; // numeros aleatorios entre 0 y 1 (decimal)
}

template<int n=2, typename T=int> // P.Template sin Tipo (con un valor por defecto de 2)
class Polinomio{
private:
    vector<T> coef; // vector de coeficientes
public:
    Polinomio(){
        for(int i=0; i <= n; i++)
            coef.push_back((T)(r()*10-5));  // [0-10]-> rand()%11
    }
    void print(){
        string s="";
        for(int i=0; i < n; i++){
            s += a_string(coef[i]);
            if (coef[i] != 0) {
                s += "x^";
                s += to_string(n - i);
            }
        }
        s+= a_string(coef[n]);
        cout << s << endl;
    }
    void eval(T x);
};

template<int n, typename T>
void Polinomio<n,T>::eval(T x){
    int res = 0;
    for(int i=0; i <= n; i++){
        res += coef[i] * pow(x,n-i);
    }
    cout << "eval(" << x << ")=" << res << endl;
}

template<template<typename> typename C, typename T>
//template<typename U>
void print_poly(C<T> cont){
    int exp = distance(cont.begin(), cont.end())-1;
    for(auto it=cont.begin(); it!=cont.end(); it++){
        cout << *it;
        if (exp > 0)
            cout << "x^" << exp << '+';
        exp--;
    }
    cout << endl;
}
int main() {
    /*
     * Ej. 1 y 2
    srand(time(0));

    Polinomio<3, float> pol1;
    pol1.print();

    Polinomio<4> pol2;
    pol2.print();		// Resultado: 3x^4 + 6x^3 + 7x^2 + 5x^1 + 3
    pol2.eval(1);		// Resultado: 24

    Polinomio<> pol3;
    pol3.print();		// Resultado: 5x^2 + 6x^1 + 2
    cout << RAND_MAX << endl;
    */
    vector<int> v1{3,2,7};
    vector<float> v2{0.1,-3.2, 1.1};
    list<float> l1{2.1,-2.2, 4.4, 4.1};

    print_poly(v1); // Resultado: 3x^2+2x^1+7
    print_poly(v2); // Resultado: 0.1x^2-3.2x^1+1.1
    print_poly(l1); // Resultado: 2.1x^3-2.2x^2+4.4x^1+4.1
    return 0;
}
