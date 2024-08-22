#include <iostream>
#include <cmath>

using namespace std;

class Vector3D{
friend void print(const Vector3D& vec);
friend class Matriz2D;
private:
  double* ptr;
public:
  Vector3D(){
    ptr = new double[3];
    ptr[0] = 0;
    ptr[1] = 0;
    ptr[2] = 0;
  }
  Vector3D(double x, double y, double z){
    ptr = new double[3]{x,y,z};
  }
  double modulo(){
    return sqrt(ptr[0]*ptr[0]+ptr[1]*ptr[1]+ptr[2]*ptr[2]);
  }
  ~Vector3D(){
    delete[] ptr;
    ptr = NULL;
  }
};

class Matriz2D{
friend void print(const Matriz2D& m);
private:
  int** ptr;
  int filas;
  int columnas;
public:
  Matriz2D(const Vector3D& v, int k){
    filas = 3;
    columnas = k;
    ptr = new int*[3];
    for(int i=0; i < filas; i++){
      ptr[i] = new int[columnas];
      for(int j=0; j < columnas; j++){
        ptr[i][j] = (int) v.ptr[i];
      }
    }
  }
  Matriz2D(int f, int c): filas(f), columnas(c){
    ptr = new int*[filas];
    for(int i=0; i < filas; i++){
      ptr[i] = new int[columnas];
      for(int j=0; j < columnas; j++){
        ptr[i][j] = rand() % 10;
      }
    }
  }
  Matriz2D(int l): Matriz2D(l,l){}
  Matriz2D(): Matriz2D(3,3){}
};
void print(const Matriz2D& m){
  for(int i=0; i < m.filas; i++){
    for(int j=0; j < m.columnas; j++){
      cout << m.ptr[i][j] << ' ';
    }
    cout << endl;
  }
}
void print(const Vector3D& vec){
  cout<<'('<<vec.ptr[0]<<','<<vec.ptr[1]<<','<<vec.ptr[2] <<')'<< endl;
}

int main(){
  Vector3D v1(3.3,4.4,5.5);
  cout << v1.modulo() << endl;
  //print(v1);
  
  Vector3D v2;
  //cout << v2.modulo() << endl;

  Matriz2D m1(4,3);
  print(m1);

  Matriz2D m2(v1, 4);
  print(m2);
}