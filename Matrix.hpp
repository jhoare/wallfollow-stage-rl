#pragma once 
#include <iostream>
#include <cstring>
extern "C"{
#include <assert.h>
}

template <typename elType>
class Matrix;

template <typename elType> 
std::istream& operator>>(std::istream& in, Matrix<elType>& m){
    int height,width;
    in >> height >> width;
    assert(height>0 && width>0);
    m.create(width,height);
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            in >> m(j,i);
    return in;
}

template <class elType>
class Matrix {
    private:
        Matrix();
    public:
        ~Matrix(){ this->clearMatrix(); };
        Matrix(int width, int height, elType value=0):
                pData(0), height(0), width(0){
            create(width,height);
        }
        Matrix(const Matrix& m):
                pData(0), height(0), width(0){
            clearMatrix();
            int w = m.width;
            int h = m.height;
            pData = new elType [w*h];
            memcpy(pData, m.pData, w*h*sizeof(elType));
            width = w;
            height = h;
        }
        int operator*=(const double &rhs){
            int sizeMatrix = height * width;
            for(int i = 0; i < sizeMatrix; i++ )
                pData[i] *= rhs;
            return 0;
        }
        Matrix operator* (const double &rhs){
            Matrix result(*this);
            result *= rhs;
            return result;
        }
        int operator+=(const double &rhs){
            int sizeMatrix = height * width;
            for(int i = 0; i < sizeMatrix; i++ )
                pData[i] += rhs;
            return 0;
        }

        /// Element-wise Addition
        int operator+=(const Matrix &m){
            assert(sameDim(m));
            elType* ptrData = pData;
            elType* ptrSource = m.pData;
            int sizeMatrix = height * width;
            for(int i = 0; i < sizeMatrix; i++ ){
                *(ptrData) += *(ptrSource);
                ptrData++;
                ptrSource++;
            }
            return 0;
        }
        elType& at(int x, int y){
            assert(!(pData==NULL || x<0 || x>=width || y<0 || y>=height)); 
            return pData[x*height+y];
        }
        inline elType& operator ()(int x, int y) const{
            //std::cout << "(" << x << "," << y << ")" << std::endl;
            assert(!(pData==NULL || x<0 || x>=width || y<0 || y>=height)); 
            return pData[x*height+y];
        }
        int getHeight(){ return height; }
        int getWidth(){ return width; }
        friend std::istream& operator>><>(std::istream& in, Matrix<elType>& m);
    protected:
        void create(int w, int h){
            if(w != width || h != height){
                clearMatrix();
                pData = new elType [w*h];
                width = w;
                height = h;
            }
            std::memset(pData,0,w*h*sizeof(elType));
        }
        bool sameDim(const Matrix &m){
            return (m.width == width && m.height == height);
        }
        void clearMatrix(){
            if (pData) delete pData;
            pData = 0;
            width = 0;
            height = 0;
        }

    protected:
        elType* pData;
        int height,width;
};

template <typename elType> 
std::ostream& operator<<(std::ostream& out, Matrix<elType>& m){
    int height = m.getHeight();
    int width = m.getWidth();
    // First print out height,width
    out << height << " " << width << std::endl;
    // Now print out the elements..
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++)
            out << m(j,i) << " ";
        out << std::endl;
    }
    return out;
}


typedef Matrix<double> dMatrix;
