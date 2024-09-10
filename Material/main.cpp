#include <iostream>
using namespace std;

// Forward declaration of class B
class B;

class A {
    int a = 0;
public:
    explicit A(int x) : a(x) {}
    void print(B& b);
};

class B {
    int b = 0;
public:
    explicit B(int x): b(x) {}
    friend class A;
    friend void A::print(B& b); 
    friend void f(B& b);
    friend ostream& operator<<(std::ostream& os, B& b);
};

void f(B& b) {
    cout << b.b << std::endl;
}

ostream& operator<<(ostream& os, B& b) {
    os << b.b << std::endl;
    return os;
}


void A::print(B &b) {
    cout << b.b << std::endl;
}

int main() {
    A a(1);
    B b(2);
    a.print(b);
    f(b);
    cout << b << std::endl;
    return 0;
}
