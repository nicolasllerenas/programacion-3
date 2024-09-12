#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
template<typename... Ts>
double norma2(Ts... xs){
    return sqrt((pow(xs,2)+...));
}

int main() {
    cout << norma2(3.3,4.4) << endl;            // 5.5
    cout << norma2(3,4,5) << endl;	            // (50)^(½)
    cout << norma2(3,4,5,6,7,8,8,9) << endl;	
    return 0;
}