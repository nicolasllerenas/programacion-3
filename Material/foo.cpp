#include "foo.h"

Data::Data(const char *pc) {
    string s = pc;
    p = new string(s);
    t = 's';
}

bool Data::operator==(const Data &other) const {
    if (t != other.t)
        return false;
    switch (t) {
        case 'i':
            return *(int *)p == *(int *)other.p;
        case 'd':
            return *(double *)p == *(double *)other.p;
        case 'b':
            return *(bool *)p == *(bool *)other.p;
        case 'c':
            return *(char *)p == *(char *)other.p;
        case 's':
            return *(string *)p == *(string *)other.p;
        default:
            return false;
    }
}



const Data& PyList::operator[](int i) const {
    return vec[i];
}
Data& PyList::operator[](int i) {
    return vec[i];
}
PyList& PyList::operator=(const PyList& other) {
    vec = other.vec;
    length = other.length;
    return *this;
}

PyList PyList::from_to(int i, int j) {
    PyList res;
    for (int k = i; k < j; k++)
        res.append(vec[k]);
    return res;
}

int len(const PyList &item) {
    return item.length;
}
ostream& operator<<(ostream& os, const PyList& item) {
    if (item.length == 0) {
        os << "[]";
        return os;
    }
    os << '[';
    for (int i = 0; i < item.length - 1; i++) {
        print(os, item[i]);
        os << ',';
    }
    print(os, item[item.length - 1]);
    os << ']';
    return os;
}
ostream& print(ostream& os, const Data data) {
    switch (data.t) {
        case 'i': os << *(int*)data.p; break;
        case 'd': os << *(double*)data.p; break;
        case 'b': os << *(bool*)data.p; break;
        case 'c': os << *(char*)data.p; break;
        case 's': os << *(string*)data.p; break;
        case '6': typeid(PyList).name();
            cout << *(PyList*)data.p;
            break;
        default: os << "unknown"; break;
    }
    return os;
}
bool is_equal(const Data &data, float x){
    float eps = 0.0001;
    if (abs(x - *(double*)data.p) < eps)
        return true;
    return false;
}

