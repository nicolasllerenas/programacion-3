#include <iostream>
#include <utility>
#include <vector>
using namespace std;
class Foo {
private:
    int* _num;

public:
    Foo(int arg) : _num(new int(arg)) {
        cout << "Clase Foo: Constructor -> " << arg << std::endl;
    }

    ~Foo() {
        if (_num) {
            cout << "Clase Foo: Destructor -> " << *_num << endl;
            delete _num;
        } else {
            cout << "Clase Foo: Destructor -> nullptr" << endl;
        }
    }

    Foo(const Foo& other) : _num(new int(*other._num)) {
        cout << "Clase Foo: Constructor Copia -> " << *_num << endl;
    }

    Foo(Foo&& other) noexcept : _num(other._num) {
        cout << "Clase Foo: Constructor Mov -> " << *_num << endl;
        other._num = nullptr;
    }

    Foo& operator=(const Foo& other) {
        if (this != &other) {
            delete _num;
            _num = new int(*other._num);
            cout << "Clase Foo: Operador de asignación de copia -> " << *_num << endl;
        }
        return *this;
    }

    Foo& operator=(Foo&& other) noexcept {
        if (this != &other) {
            delete _num;
            _num = other._num;
            other._num = nullptr;
            cout << "Clase Foo: Operador de asignación de movimiento -> " << *_num << endl;
        }
        return *this;
    }
};

void test1() {
    Foo f1(3);
}

void test2() {
    Foo f1(3);
    Foo f2(f1);
    Foo f3(Foo(5));
}

void test3() {
    vector<Foo> v;
    v.push_back(Foo(4));
}

void test4() {
    Foo f1(3);
    Foo f2(move(f1));
}

int main() {
    cout << "Test 1:" << endl;
    test1();
    
    cout << "\nTest 2:" << endl;
    test2();
    
    cout << "\nTest 3:" << endl;
    test3();
    
    cout << "\nTest 4:" << endl;
    test4();

    return 0;
}