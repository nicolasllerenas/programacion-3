#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

template<typename T>
void print(vector<T>& v){
    for_each(v.begin(), v.end(), [](T x){cout << x << ' ';});
    cout << endl;
}

/* Ej. 1
//template<typename T>
void bubble_sort(vector<int>& A, bool (*f)(int, int)){
    for(int i=0; i < A.size()-1; i++){
        for(int j=0; j < A.size()-i-1; j++){
            if (f(A[j],A[j+1]))
                swap(A[j], A[j+1]);
        }
    }
}

bool crec(int x, int y){ return x > y;}
bool decr(int x, int y){ return x < y;}
bool vabs(int x, int y){ return abs(x) > abs(y);}



double f(double x){
    return (pow(x,3) + x) + 2 * pow(x,2);
}
double dF(double (*f)(double), double x0){
    double h = 0.000001;
    return (f(x0+h) - f(x0))/h;
}
*/
/*
class Cifrar{
private:
    int a, b;
public:
    Cifrar(int _a, int _b): a(_a), b(_b){}
    char operator()(char letra){
        int x = letra - 65;  // A -> 0, B -> 1, ..., Z -> 25
        int c = (a * x + b) % 26;
        return c + 65;
    }
};
*/
int main(){
    /*
    vector<int> v1 = {5,12,3,13,-3,5,0,1,2,6,2,4};
    print(v1);
    bubble_sort(v1, decr);
    print(v1);
    */
    /* Ej.2
    Cifrar C(2,0);
    string s = "HOLA";
    for(const char& letra: s)
        cout << C(letra);
    cout << endl;
    */
    vector<string> deck(52);
    string figs = "CDET";
    generate(deck.begin(), deck.end(),
             [n=0,figs]()mutable {return to_string((n++)%13+1) + figs[n/13];});
    print(deck);
    return 0;
}