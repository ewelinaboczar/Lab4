#ifndef matrix_hpp
#define matrix_hpp

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <string.h>


class matrix
{
    int row=0, column=0;
    double **mac; 
    
    public:
    matrix();
    matrix(std::string path);
    matrix(int r,int c);
    matrix(int r);
    ~matrix();

    void set(int n,int m,double val);
    double get(int n,int m);
    matrix operator+(matrix &m2);
    matrix operator-(matrix &m2);
    matrix operator*(matrix &m2);
    void operator==(matrix &m2);
    void operator[](int no_row);
    void operator++(int value);
    void operator--(int value);
    //void operator=(matrix &m2);
    int cols();
    int rows();
    void print();
    void store(std::string ,std::string );
  
};

#endif