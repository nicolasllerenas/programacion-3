#include <iostream>

using namespace std;
int findMax(const vector<int>& numbers){
    return *max_element(numbers.begin(), numbers.end())

}
int main() {
    vector<int> numbers = {9, 12, 4, 7, 1, 18, 3, 5, 10};
    int Max1 = findMax(numbers);
    
    return 0;
}