#include <iostream>
#include <vector>   // Necesario para usar vectores
#include <string>   // Necesario para usar strings

using namespace std;

template<typename T>
T Max(vector<T>& vec){
    T max = vec[0];
    for(int i = 1; i < vec.size(); i++){
        if(vec[i] > max)
            max = vec[i];
    }
    return max;
}

// Especialización para vector de strings
template<>
string Max(vector<string>& vec){
    string max = vec[0];
    for(int i = 1; i < vec.size(); i++){
        if(vec[i].size() > max.size())
            max = vec[i];
    }
    return max;
}

int main(){
    vector<int> v1 = {-3, 3, 6, 5, 0, -9};
    vector<string> v2 = {"Hola", "Mundo", "en", "C++"};

    cout << "Max in v1: " << Max(v1) << endl;  // Máximo número entero
    cout << "Max in v2: " << Max(v2) << endl;  // Palabra más larga

    return 0;
}
