#include <iostream>
using namespace std;

// Clase Point2d para representar un punto en 2D
class Point2d {
private:
    int x, y;

public:
    // Constructor para inicializar un punto
    Point2d(int x, int y) : x(x), y(y) {}

    // Función para imprimir las coordenadas
    void print() const {
        cout << "(" << x << ", " << y << ")";
    }
};

// Clase base Figure
class Figure {
public:
    // Destructor virtual para soporte polimórfico
    virtual ~Figure() {}

    // Función virtual pura para que las clases derivadas implementen
    virtual void print() const = 0;
};

// Clase Circle derivada de Figure
class Circle : public Figure {
private:
    Point2d centro;
    int radio;

public:
    // Constructor para inicializar el círculo
    Circle(Point2d c, int r) : centro(c), radio(r) {}

    // Implementación de la función print
    void print() const override {
        cout << "Circle: ";
        centro.print();
        cout << ", radio: " << radio << endl;
    }
};

// Clase Rectangle derivada de Figure
class Rectangle : public Figure {
private:
    Point2d esquina1, esquina2;

public:
    // Constructor para inicializar el rectángulo
    Rectangle(Point2d e1, Point2d e2) : esquina1(e1), esquina2(e2) {}

    // Implementación de la función print
    void print() const override {
        cout << "Rectangle: ";
        esquina1.print();
        cout << ", ";
        esquina2.print();
        cout << endl;
    }
};

// Clase Triangle derivada de Figure
class Triangle : public Figure {
private:
    Point2d punto1, punto2, punto3;

public:
    // Constructor para inicializar el triángulo
    Triangle(Point2d p1, Point2d p2, Point2d p3) : punto1(p1), punto2(p2), punto3(p3) {}

    // Implementación de la función print
    void print() const override {
        cout << "Triangle: ";
        punto1.print();
        cout << ", ";
        punto2.print();
        cout << ", ";
        punto3.print();
        cout << endl;
    }
};

// Función para imprimir figuras
void print(Figure* f) {
    f->print();
}

int main() {
    // Crear un arreglo de punteros a Figure
    Figure* f[3];

    // Inicializar las figuras
    f[0] = new Circle(Point2d(1, 2), 3);
    f[1] = new Rectangle(Point2d(1, 2), Point2d(3, 4));
    f[2] = new Triangle(Point2d(1, 2), Point2d(3, 4), Point2d(5, 6));

    // Imprimir cada figura
    for (int i = 0; i < 3; i++) {
        print(f[i]);
    }

    // Liberar memoria
    for (int i = 0; i < 3; i++) {
        delete f[i];
    }

    return 0;
}
