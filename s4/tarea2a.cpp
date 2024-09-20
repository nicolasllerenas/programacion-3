#include <iostream>
#include <vector>
#include <variant>
#include <string>
#include <sstream>

using namespace std;

class pylist;

using var_t = variant<int, double, char, bool, pylist>;

class pylist {
private:
    vector<var_t> data;

public:
    pylist() = default;

    template<typename... Args>
    pylist(Args... args) {
        (append(args), ...);
    }

    void append(const var_t& value) {
        data.push_back(value);
    }

    size_t size() const {
        return data.size();
    }

    var_t& operator[](size_t index) {
        return data[index];
    }

    const var_t& operator[](size_t index) const {
        return data[index];
    }

    friend ostream& operator<<(ostream& os, const pylist& list) {
        os << "[";
        for (size_t i = 0; i < list.size(); ++i) {
            visit([&os](const auto& item) {
                using T = decay_t<decltype(item)>;
                if constexpr (is_same_v<T, char>) {
                    os << item;
                } else if constexpr (is_same_v<T, bool>) {
                    os << (item ? "true" : "false");
                } else if constexpr (is_same_v<T, pylist>) {
                    os << item;
                } else {
                    os << item;
                }
            }, list[i]);
            if (i < list.size() - 1) os << ",";
        }
        os << "]";
        return os;
    }

    friend bool operator==(const var_t& lhs, const var_t& rhs) {
        return visit([](const auto& a, const auto& b) -> bool {
            using T1 = decay_t<decltype(a)>;
            using T2 = decay_t<decltype(b)>;
            if constexpr (is_same_v<T1, T2>) {
                return a == b;
            } else {
                return false;
            }
        }, lhs, rhs);
    }
};

size_t len(const pylist& list) {
    return list.size();
}

int main() {
    pylist l1; // P.1
    cout << l1 << endl; // []
    l1.append(3); // P.2
    cout << l1 << endl; // [3]
    l1.append('A');
    l1.append(true);
    l1.append(3.0012);
    cout << l1 << endl; // [3,A,true,3.0012]
    pylist l2(1, 2.1, 'A', 'B'); // P.3
    cout << l2 << endl; // [1,2.1,A,B]
    // P.4 (Una lista dentro de otra)
    l1.append(l2);
    cout << l1 << endl; // [3,A,true,3.0012,[1,2.1,A,B]]
    cout << len(l1) << endl; // 5
    cout << len(l2) << endl; // 4
    // P.5
    cout << l1[1] << endl; // A
    cout << l1[4] << endl; // [1,2.1,A,B]
    // P.6
    l1[0] = 'X';
    cout << l1 << endl; // [X,A,true,3.0012,[1,2.1,A,B]]
    // P.7
    cout << (l1[1] == 'A') << endl; // 1 (verdadero)
    cout << (l1[3] == 3.0) << endl; // 0 (falso)
}