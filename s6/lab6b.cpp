#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <forward_list>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace std;


int moda(map<int,int> contador){
    // moda_: es el primer número en el contador (1 - 20)
    int moda_ = contador.begin()->first;  // accediento a la primera CLAVE
                                        // el equivalente es "(*constador.begin()).first"
    for(const auto p: contador){
        // En 'p' existen dos enteros, el primero es el número (1-20)
        // y el segundo representa sus repeticiones (p.second)
        if(p.second > contador[moda_])
            moda_ = p.first;
    }
    return moda_;
}

bool es_compuesto(int n){
    if (n==1)
        return true;
    // Si 'n' es primo, entonces es divisible unicamente entre
    // 1 y el mismo 'n'.
    // 'd' varia entre 2 y 'n-1'
    for(int d=2; d < n; d++){
        if(n % d == 0) // Si existe un 'd' que divide a 'n' entonces no es primo.
            return true;
    }
    return false;
}

void bubble_sort(vector<int>& A){
    for (int i=0; i<A.size(); i++)
        for (int j=0; j<A.size()-i-1; j++)
            if (A[j]>A[j+1])
                swap(A[j],A[j+1]);
}

int main() {
    /*
    unordered_map<string,int> contador;
    string palabra;

    while(getline(cin, palabra)){
        if (palabra.begin() == palabra.end()) // Cuando se presiona ENTER si ingresar una
            break;                            // una palabra se rompe el bucle
        for(char& c: palabra)
            c = tolower(c);
        contador[palabra]++; // insertamos la palabra como clave
    }

    for(const pair<string,int> e: contador){
        cout << e.first << ": " << e.second << endl;
    }
    */
    /*
    // Ej. 2
    srand(time(NULL));
    vector<int> v1(100);
    generate(v1.begin(),v1.end(), []{return rand()%20+1;});
    for_each(v1.begin(),v1.end(),[](int x){cout << x << ' ';});cout << endl;

    map<int,int> contador;
    for(const int x: v1)
        contador[x]++;
    for_each(contador.begin(),contador.end(),
             [](pair<int,int> p){cout<<p.first<<": "<<p.second<<endl; });
    cout << "Moda: " << moda(contador) << endl;
    return 0;
    */
    /*
    forward_list<int> f;
    for(int i=0; i < 100; i++)
        f.push_front(rand()%50+1);
    f.remove_if(es_compuesto);
    for_each(f.begin(),f.end(),[](int x){cout << x << ' ';}); cout << endl;

    unordered_set<int> s(f.begin(),f.end());
    for_each(s.begin(),s.end(),[](int x){cout << x << ' ';}); cout << endl;
     */

    vector<int> vec = {5,3,6,8,1,4,6,5,3,1,1};
    for_each(vec.begin(),vec.end(),[](int x){cout << x << ' ';});cout << endl;
    set<int> s(vec.begin(),vec.end());
    //for_each(s.begin(),s.end(),[](int x){cout << x << ' ';});cout << endl;

    if (s.find(7) != s.end()){

    }
    bubble_sort(vec);
    auto it = unique(vec.begin(),vec.end());
    vec.erase(it,vec.end());
    for_each(vec.begin(),vec.end(),[](int x){cout << x << ' ';});cout << endl;

    // ==> 1,3,4,5,6,8
}
