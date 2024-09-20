#include <iostream>
#include <cmath>

using namespace std;

template<typename T, typename... Ts>
T Max
T Max(T a, Ts... args){
    if (sizeof...(args) == 0)
    return a;
    return Max(a,Max(args...));
}


int main() {
    cout << Max(3,4,5,6) << endl;
    return 0;
}