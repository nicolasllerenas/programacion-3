
#ifndef FOO_H
#define FOO_H

#include <iostream>
#include <vector>
#include <cmath>
    using namespace std;

    class PyList;

    struct Data {
        friend ostream& print(ostream& os, const Data data);
        friend bool is_equal(const Data &l, float x);
        void *p;
        char t;
        template <typename T>
        Data(T n){
            p = new T(n);
            t = typeid(n).name()[0];
        };

        Data(const char *pc);

        bool operator==(const Data &other) const;

        template<typename T>
        Data& operator=(T x){
            p = new T(x);
            t = typeid(x).name()[0];
            return *this;
        };
    };


    class PyList {
        friend ostream &operator<<(ostream &os, const PyList &item);
        friend int len(const PyList &item);

    private:
        vector<Data> vec;
        int length = 0;
    public:
        PyList() {}

        template<typename... Ts>
        PyList(Ts... args){
            this->append(args...);
        };

        template<typename T>
        void append(T x){
            vec.push_back(Data(x));
            length++;
        };

        template<typename T, typename... Ts>
        void append(T x, Ts... args){
            vec.push_back(Data(x));
            length++;
            append(args...);
        };

        Data &operator[](int i);

        const Data &operator[](int i) const;

        PyList &operator=(const PyList &other);

        PyList from_to(int i, int j);

    };
#endif

