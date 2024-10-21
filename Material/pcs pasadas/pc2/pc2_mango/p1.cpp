#include <forward_list>
#include <iostream>
#include <algorithm>
using namespace std;

void revertir(forward_list<int>& list) {
    auto i = list.begin();
    auto j = i;
    i++;
    while(i != list.end()) {
        list.push_front(*i);
        i++;
        list.erase_after(j);
    }
}

void print(const forward_list<int>& list) {
    for_each(list.begin(), list.end(), [](int num) {
        cout << num << " ";
    });
}


int main() {
    srand(time(nullptr));
    int n = 10;
    forward_list<int> list(n);
    generate(list.begin(), list.end(), []() {
        return rand() % 1000;
    });

    cout << "Lista original:" << endl;
    print(list);
    cout << endl;
    revertir(list);

    cout << "Lista revertida:" << endl;
    print(list);
    cout << endl << endl;

    //Complejidad algorítmica: O(n)
    cout << "Complejidad algoritmica: O(n)";
}