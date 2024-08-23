#include <iostream>
#include <utility>
#include <vector>

class Foo {
private:
    int* _num;

public:
    Foo(int arg) : _num(new int(arg)) {
        std::cout << "Clase Foo: Constructor -> " << arg << std::endl;
    }

    ~Foo() {
        if (_num) {
            std::cout << "Clase Foo: Destructor -> " << *_num << std::endl;
            delete _num;
        } else {
            std::cout << "Clase Foo: Destructor -> nullptr" << std::endl;
        }
    }

    Foo(const Foo& other) : _num(new int(*other._num)) {
        std::cout << "Clase Foo: Constructor Copia -> " << *_num << std::endl;
    }

    Foo(Foo&& other) noexcept : _num(other._num) {
        std::cout << "Clase Foo: Constructor Mov -> " << *_num << std::endl;
        other._num = nullptr;
    }

    Foo& operator=(const Foo& other) {
        if (this != &other) {
            delete _num;
            _num = new int(*other._num);
            std::cout << "Clase Foo: Operador de asignación de copia -> " << *_num << std::endl;
        }
        return *this;
    }

    Foo& operator=(Foo&& other) noexcept {
        if (this != &other) {
            delete _num;
            _num = other._num;
            other._num = nullptr;
            std::cout << "Clase Foo: Operador de asignación de movimiento -> " << *_num << std::endl;
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
    std::vector<Foo> v;
    v.push_back(Foo(4));
}

void test4() {
    Foo f1(3);
    Foo f2(std::move(f1));
}

int main() {
    std::cout << "Test 1:" << std::endl;
    test1();
    
    std::cout << "\nTest 2:" << std::endl;
    test2();
    
    std::cout << "\nTest 3:" << std::endl;
    test3();
    
    std::cout << "\nTest 4:" << std::endl;
    test4();

    return 0;
}