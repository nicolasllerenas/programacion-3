#include <iostream>
#include <vector>
#include <algorithm>
#include <forward_list>
using namespace std;

template<typename T>
void print(T it_begin, T it_end){
    for_each(it_begin, it_end, [](auto x){cout << x << ' ';});
    cout << endl;
}

template<typename T>
T maximo(T it_begin, T it_end){
    T max_it = it_begin;
    for(auto it=it_begin; it!=it_end; it++){
        // Verificamos si el elemento al cual apunta
        // 'it' es mayor al elemento que apunta 'max_it'
        if(*it > *max_it)
            max_it = it;
    }
    return max_it;
}

template<typename T>
double promedio(T it_begin, T it_end){
    double sum = 0.;
    for(auto it=it_begin; it!=it_end; it++)
        sum += *it;
    // sum = accumulate(it_begin, it_end, 0);
    return sum / distance(it_begin, it_end);
}

bool es_compuesto(int x){
    if (x == 1)
        return true;
    for(int d=2; d < x; d++){
        if (x % d == 0)
            return true;
    }
    return false;
}

void push_back(forward_list<int>& FL, int x){
    auto it = FL.before_begin();
    // Se repite 'N' veces (N es el tamaño de FL)
    for(int i=0; i < distance(FL.begin(),FL.end()); i++)
        ++it;
    // Al final 'it' apunta al último elemento

    // it = FL.end();
    // --it; (NO SE PUEDE)
    FL.insert_after(it, x);
}

void bubble_sort(vector<int> &A){
    for (int i = 1; i < A.size(); i++)
        for (int j = A.size()-1; j >= i; j--)
            if (A[j] < A[j - 1])
                swap(A[j],A[j-1]);
}

template<typename T>
void bubble_sort(T it_begin, T it_end){
    for(auto it=next(it_begin); it!=it_end; it++){
        for(auto itr=prev(it_end); itr!=prev(it); itr--){
            if(*itr < *(prev(itr)))
                swap(*itr,*prev(itr));
        }
    }
}

int main() {
    srand(time(NULL));
    /*
    // Ej. 1
    vector<int> vec(10);
    generate(vec.begin(), vec.end(), [](){return rand()%100;});
    print(vec.begin(),vec.end());
    cout << "maximo: " << *maximo(vec.begin(), vec.end()) << endl;
    cout << "maximo: " << *max_element(vec.begin(), vec.end()) << endl;

    cout << "promedio: " << promedio(vec.begin(), vec.end()) << endl;
    */
    /*
     * Ej. 2
    forward_list<int> FL;
    for(int i=0; i<100; i++)
        FL.push_front(rand()%99 + 1);
    FL.remove_if(es_compuesto);
    print(FL.begin(),FL.end());
    return 0;
    */
    /*
    forward_list<int> L = {2,4,1,4,7,9,3,6,32,3};
    print(L.begin(),L.end());
    push_back(L,7);
    print(L.begin(), L.end());
    */
    vector<int> vec = {5,2,7,2,5,9,3,1};
    bubble_sort(vec);
    print(vec.begin(), vec.end());
}
