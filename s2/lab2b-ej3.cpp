//
// Created by Profesor08 on 29/08/2024.
//
#include <iostream>
using namespace std;


class Forma{
    friend ostream& operator<<(ostream& os, const Forma& f);
protected:
    double area=0;
public:
    virtual void calcularArea(){}
};

class Cuadrado: public Forma{
private:
    double lado;
public:
    Cuadrado(double l): lado(l){}
    void calcularArea(){
        area = lado * lado;
    }
};
class Circulo: public Forma{
private:
    double radio;
public:
    Circulo(double r): radio(r){}
    void calcularArea(){
        area = radio * radio * 3.14159;
    }
};

ostream& operator<<(ostream& os, const Forma& f){
    os << f.area;
    return os;
}
int main(){
    Forma* forma;

    forma = new Cuadrado(2);
    forma->calcularArea();
    cout << *forma << endl;

    forma = new Circulo(1);
    forma->calcularArea();
    cout << *forma << endl;

    //forma = new Triangulo(2,3);
    //forma->calcularArea();
    //cout << *forma << endl;

    return 0;
}