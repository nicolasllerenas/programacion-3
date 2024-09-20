#include <iostream>
#include <cmath>
using namespace std;
class Vec{
    private:
    vector<T> vec;
    public:
    void push_back_many(T x){
        vec.push_back(x);
    }
}
template<typename... Ts>
void push_back_many(T primero, Ts... pack){
    vec.push_back(primero);
    push_back_many(pack...);
}
void print(){
    for(auto e: vec)
        cout << e<< ' ';
    cout << endl;
}
int main() {
    
    return 0;
}