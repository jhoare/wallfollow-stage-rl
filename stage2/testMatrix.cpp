#include "Matrix.hpp"
#include <iostream>
using namespace std;

int main(){
    dMatrix mat(2,2);
    mat(0,0) = 1;
    mat(1,0) = 2;
    mat(0,1) = 3;
    mat(1,1) = 4;

    dMatrix add(mat);

    cout << mat;

    cout << " * 0.5 " << endl;

    dMatrix mat2 = mat * 0.5;

    cout << " == " << endl;
    cout << mat2 << endl;


    cout << endl << mat << " *= 0.5" << endl;
    mat *= 0.5;
    cout << mat << endl;

    cout << endl << mat << " += " << endl << add;
    cout << " == " << endl;
    mat += add;
    cout << mat;
}
