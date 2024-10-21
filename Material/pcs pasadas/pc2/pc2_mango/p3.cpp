#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

template<typename T>
void print(T begin, T end) {
    for_each(begin, end, [](double num) {
        cout << num << " ";
    });
}

template<typename T>
void print_mat(T begin, T end) {
    for_each(begin, end, [](vector<double> vec) {
        for_each(vec.begin(), vec.end(), [](double num) {
           cout << num << " ";
        });
        cout << endl;
    });
}

void g(vector<double> y, const vector<vector<double>>& W, const vector<double>& x, const vector<double>& b, int total, int num) {
    int inicio = (num)*b.size()/total;
    int final = (num + 1)*b.size()/total;
    int suma = 0;
    for(int i = inicio; i < final; i++) {
        for(int j = 0; j < W[0].size(); j++) {
            suma += W[i][j] * x[j];
        }
        y[i] = 1.0/1 + exp((suma + b[i] * -1));
    }
}

int main() {
    srand(time(nullptr));

    int n = 10000;
    int m = 100;
    vector<double> x(n);
    vector<double> b(m);
    vector<vector<double>> W(n);


    generate(x.begin(), x.end(), []() {
        return ((double)rand()) / RAND_MAX;
    });

    print(x.begin(), x.end());
    cout << endl;

    generate(W.begin(), W.end(), [m]() {
        vector<double> vec(m);
        generate(vec.begin(), vec.end(), []() {
            return ((double)rand()) / RAND_MAX;
        });
        return vec;
    });

    print_mat(W.begin(), W.end());
    cout << endl;

    generate(b.begin(), b.end(), []() {
        return (((double)rand() / RAND_MAX)/5) - 0.1;
    });

    print(b.begin(), b.end());
    cout << endl;



    return 0;
}