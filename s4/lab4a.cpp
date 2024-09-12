#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/* Ej. 1
template<typename T>
T sumar(T inp1, T inp2){
    return inp1 + inp2;
}

template<typename T1, typename T2>
char sumar(T1 inp1, T2 inp2){
    return inp1 + inp2;
}
*/
/*
 * Ej. 2
template<typename T>
T Max(vector<T>& vec){
    T max = vec[0];
    for(int i=1; i < vec.size(); i++){
        if(vec[i] > max)
            max = vec[i];
    }
    return max;
}

// Especializacion
template<>
string Max(vector<string>& vec){
    string max = vec[0];
    for(int i=1; i < vec.size(); i++){
        if(vec[i].size() > max.size())
            max = vec[i];
    }
    return max;
}
*/
/*
// General (1)
template<typename T>
string Tipo(T a){
    return "No es puntero.";
}


// Para punteros (2)
template<typename T>
string Tipo(T* a){
    return "Es puntero.";
}

// Especializacion de (2)
template<>
string Tipo(int* a){
    return "Es puntero 'int'.";
}
*/

template<typename... Ts>
double norma2(Ts... xs){
    return sqrt((pow(xs,2)+...));
}

template<typename... Ts>
double MA(Ts... xs){
    return (double)(xs+...)/sizeof...(xs);
}
template<typename... Ts>
double MH(Ts... xs){
    return (double)sizeof...(xs)/((1./xs)+...);
}
template<typename... Ts>
double MG(Ts... xs){
    return pow((xs*...), 1./sizeof...(xs));
}
int main() {
    /* Ej. 1
    cout << sumar(1,3) << endl;     // 4
    cout << sumar('A',1) << endl;   // B
    cout << sumar(2,'A') << endl;   // C
    cout << sumar('<','=') << endl; // y
    */
    /* Ej. 2
    vector<int> v1 = {-3,3,6,5,0,-9};
    vector<string> v2 = {"Hola","Mundo","en","C++"};

    cout << Max(v1) << endl;
    cout << Max(v2) << endl;
    return 0;
    */
    /* Ej. 3
    double x = 7;
    int u = 5;
    double* ptr1 = &x;
    int* ptr2 = &u;

    cout << Tipo(x) << endl;
    cout << Tipo(ptr1) << endl;
    cout << Tipo(ptr2) << endl;
    */
    /*
     *  Ej.4
    cout << norma2(3.3,4.4) << endl;            // 5.5
    cout << norma2(3,4,5) << endl;	            // (50)^(½)
    cout << norma2(3,4,5,6,7,8,8,9) << endl;	//
    */
    cout << MA(1,2,3,4,5) << endl;
    cout << MG(1,2,3,4,5) << endl;
    cout << MH(1,2,3,4,5) << endl;
}
