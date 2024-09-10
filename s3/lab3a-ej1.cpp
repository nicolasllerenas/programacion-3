#include <iostream>

using namespace std;
template<typename T1, typename T2, typename T3>
T1 foo(T1 x, T2* y, T3& z){
    // El tipo de dato de 'x' define el tipo de dato de la salida
    z = z + x;
    return x * (*y);

}
int main() {
    double x = 3;
    double y = 4.1;
    double z = 5.09;

    cout <<"foo = "<< foo(x,&y,&z)<<endl;
    cout <<"z = " << z << endl;
    return 0;
}