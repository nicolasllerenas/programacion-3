#include <iostream>
#include <cmath>

using namespace std;

class Vector3D{
friend void print(const Vector3D& vec);
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
    ptr = new double[3];
    ptr[0] = x;
    ptr[1] = y;
    ptr[2] = z;
  }

  double modulo(){
    return sqrt(ptr[0]*ptr[0]+ptr[1]*ptr[1]+ptr[2]*ptr[2]);
  }
  ~Vector3D(){
    delete[] ptr;
    ptr = NULL;
  }
};

void print(const Vector3D& vec){
  cout<<'('<<vec.ptr[0]<<','<<vec.ptr[1]<<','<<vec.ptr[2] << endl;
}

int main(){
  Vector3D v1(3.3,4.4,5.5);
  cout << v1.modulo() << endl;

  Vector3D v2;
  cout << v2.modulo() << endl;
}