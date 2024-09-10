#include <iostream>
#include <vector>
using namespace std;

/*
 * Ej.1 y Ej. 2
template<typename T1, typename T2, typename T3>
T1 foo(T1 x, T2* y, T3& z){
    // El tipo de dato de 'x' define el tipo de dato de la salida
    z = z + x;
    return x * (*y);
}

template<typename T>
bool es_puntero(T* x){
    return true;
}

template<typename T>
bool es_puntero(T x){
    return false;
}

template<typename T>
void SWAP(T& x, T& y){
    T tmp = x;
    x = y;
    y = tmp;
}

template<typename T>
void SWAP(T* ptr1, T* ptr2){
    T tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
}
*/
/* Ej. 3
template<typename T>
class Par{
    template<typename U>
    friend void print(const Par<U>& p);
    template<typename U>
    friend ostream& operator<<(ostream& os, const Par<U>& p);
private:
    T x, y;
public:
    Par(T _x, T _y): x(_x), y(_y){}
    T suma(){return x + y;}
    T resta(){return x - y;}
    T multi(){return x * y;}
    T div(){return x / y;}
};

template<typename U>
void print(const Par<U>& p){
    cout << '(' << p.x << ',' << p.y << ')' << endl;
}
template<typename U>
ostream& operator<<(ostream& os, const Par<U>& p){
    os << '(' << p.x << ',' << p.y << ')';
    return os;
}
*/

// Valores aleatorios entre 0 y 1
double r(){
    return (double)rand() / RAND_MAX;
}

template<typename T>
class range{
private:
    vector<T> vec;
public:
    range(T a, T b, int N){
        for(int i=0; i<N; i++)
            vec.push_back((T)(r() * (b-a) + a));
    }
    void print(){
        for(int i=0; vec.size(); i++)
            cout << vec[i] << endl;
    }
};

// r() -> (0 - 1)
//     -> (a - b)
int main() {
    /*
     * Ej.1 y Ej. 2
    double x = 3;
    double y = 4.1;
    double z = 5.09;

    cout << "foo = " << foo<double,double,double>(x,&y,z) << endl;
    cout << "z = " << z << endl;
    cout << "x: " << x << ", y: " << y << endl;
    SWAP(x,y);
    cout << "x: " << x << ", y: " << y << endl;
    SWAP(&x,&y);
    cout << "x: " << x << ", y: " << y << endl;
    double* ptr = &x;
    cout << es_puntero(x) << endl;
    cout << es_puntero(ptr) << endl;
    */
    /* Ej.3
    Par p(3.2,5.1);
    cout << p.suma() << endl;
    cout << p.multi() << endl;
    print(p);
    */
    srand(time(0));
    cout << r() << endl;
    range r(3,7,10);
    r.print(); //
    return 0;
}
