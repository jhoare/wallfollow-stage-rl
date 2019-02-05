#include "Matrix.hpp"
#include <iostream>
#include <fstream>
using namespace std;

int main(){
    dMatrix mat(2,2);
    mat(0,0) = 1;
    mat(1,0) = 2;
    mat(0,1) = 3;
    mat(1,1) = 4;

    {
        fstream matOut("mat_test.dat", ios::out);
        matOut << mat;
        matOut.close();
    }


    dMatrix mat2(1,1);
    {
        fstream matIn("mat_test.dat", ios::in);
        matIn >> mat2;
        cout << mat2;
    }
}
