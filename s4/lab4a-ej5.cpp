#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
template<typename... Ts>
double MA(Ts... xs){
    return (double)(xs+...)/sizeof...(xs);
}
template<typename... Ts>
double MH(Ts... xs){
    return (double)sizeof...(xs)/((1./xs)+...);
}
template<typename... Ts>
double MG(Ts... xs){
    return pow((xs*...), 1./sizeof...(xs));
}
int main() {
    cout << MA(1,2,3,4,5) << endl;
    cout << MG(1,2,3,4,5) << endl;
    cout << MH(1,2,3,4,5) << endl;
    return 0;
}