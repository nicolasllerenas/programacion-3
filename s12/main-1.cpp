#include <iostream>
#include <stack>
#include <queue>
#include <sstream>

using namespace std;

// Precedencia de los operadores
int precedencia(char operador) {
    if (operador == '+' || operador == '-') return 1;
    if (operador == '*' || operador == '/') return 2;
    return 0;
}

// Función para convertir expresión infija a postfija
queue<string> infijoapostfijo(const string& expresion) {
    stack<char> operadores;
    queue<string> salida;
    stringstream token;
    
    for (char c: expresion) {
        if (isdigit(c)) {
            token << c;  // Agregamos números al token
        } else {
            if (!token.str().empty()) { // Si hay un número en el token, lo agrega a la salida
                salida.push(token.str());
                token.str("");
                token.clear();
            }

            if (c == ' ') continue; // Ignoramos los espacios

            if (c == '(') {
                operadores.push(c);
            } else if (c == ')') {
                while (!operadores.empty() && operadores.top() != '(') {
                    salida.push(string(1, operadores.top()));
                    operadores.pop();
                }
                operadores.pop(); // Eliminamos el '('
            } else if (c=='+'||c == '-' || c=='/'||c == '*') {
                while (!operadores.empty() && precedencia(operadores.top()) >= precedencia(c)) {
                    salida.push(string(1, operadores.top()));
                    operadores.pop();
                }
                operadores.push(c);
            }
        }
    }

    if (!token.str().empty()) {
        salida.push(token.str());
    }

    while (!operadores.empty()) {
        salida.push(string(1, operadores.top()));
        operadores.pop();
    }

    return salida;
}

// Función para evaluar una expresión en notación postfija
int evaluarpostfijo(queue<string> postfijo) {
    stack<int>resultados;

    while (!postfijo.empty()) {
        string token = postfijo.front();
        postfijo.pop();

        if (isdigit(token[0])) {
            resultados.push(stoi(token));
        } else {
            int b = resultados.top(); resultados.pop();
            int a = resultados.top(); resultados.pop();

            if (token == "+") resultados.push(a + b);
            else if (token == "-") resultados.push(a - b);
            else if (token == "*") resultados.push(a * b);
            else if (token == "/") resultados.push(a / b);
        }
    }

    return resultados.top();
}

int main() {
    string inf1 = "2 + 3";
    string inf2 = "5 + (1 + 2) * 4 - 3";
    string inf3 = "(2 + 13) / 5";
    string inf4 = "((10 * (6 / ((9 + 3) * 11))) + 17) + 5";
    string inf5 = "5 + ((1 + 2) * 4) - 3";

    queue<string> pf1 = infijoapostfijo(inf1);  // 2 3 +
    queue<string> pf2 = infijoapostfijo(inf2);  // 5 1 2 + 4 * + 3 -
    queue<string> pf3 = infijoapostfijo(inf3);  // 2 13 + 5 /
    queue<string> pf4 = infijoapostfijo(inf4);  // 10 6 9 3 + 11 * / 17 + 5 +
    queue<string> pf5 = infijoapostfijo(inf5);  // 5 1 2 + 4 * + 3 -

    cout << inf1 << " = " << evaluarpostfijo(pf1) << endl; // 5
    cout << inf2 << " = " << evaluarpostfijo(pf2) << endl; // 14
    cout << inf3 << " = " << evaluarpostfijo(pf3) << endl; // 3
    cout << inf4 << " = " << evaluarpostfijo(pf4) << endl; // 22
    cout << inf5 << " = " << evaluarpostfijo(pf5) << endl; // 14

    return 0;
}
