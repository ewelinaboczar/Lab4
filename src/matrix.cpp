#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <Matrix/matrix.hpp>

using namespace std;

matrix::matrix(std::string path)

{
    ifstream file;
    file.open(path);
    if(file.is_open()==false)
    {
        file.close();cout << "Blad otwarcia pliku" << endl;
        exit(0);
    }
    else
    {
        file >> row;
        file >> column;

        mac =new double *[row];
        for(int i=0;i<row;i++)
        {
            mac[i]=new double [column];
        }

        for(int i =0; i<row; i++)
        {
            for(int j=0; j<column; j++)
            {
                file >> mac[i][j];
            }
        }
    }  
}

matrix::matrix (int r, int c)
{
    if(r<=0 && c<=0)
    {
        cout<<"Podales zle wymiary macierzy(1)"<<endl;
    }
    else
    {
        row=r;
        column=c;
        mac=new double *[r];

        for(int i=0;i<r;i++)
        {
            mac[i]=new double [c];
        }
        
        for(int i=0;i<r;i++)
        {
            for(int j=0;j<c;j++)
            {
                mac[i][j]={0};
            }
        }
    }
}

matrix::matrix (int r)
{
    if(r<=0)
    {
        cout<<"Podales zle wymiary macierzy(2)"<<endl;
    }
    else
    {
        row=r;
        column=r;
        mac=new double *[r];
        for(int i=0;i<r;i++)
        {
            mac[i]=new double [r];
        }
        
        for(int i=0;i<r;i++)
        {
            for(int j=0;j<r;j++)
            {
                mac[i][j]=0;
            }
        }
    }
}

matrix::~matrix()
{
    for(int i=0;i<row;i++)
    {
        delete[] mac[i];
    }
    delete[] mac;
}

int matrix::cols()
{
    return column;
}

int matrix::rows()
{
    return row;
}

void matrix::print()
{
    for(int i=0;i<row;i++)
        {
        for(int j=0;j<column;j++)
        {
            cout<<mac[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"\n";
}

void matrix::set(int n,int m,double val)
{
    if(n<1 && n>row && m<1 && m>column)
    {
        cout<<"Podana wspolrzedna macierzy nie istnieje";
    }
    else
    {
        mac[n-1][m-1]=val;
    }
}

double matrix::get(int n,int m)
{
    if(n<1 && n>row && m<1 && m>column)
    {
        cout<<"Podana wspolrzedna macierzy nie istnieje";
        return 0;
    }
    else
    {
        return mac[n-1][m-1];
    }
    
}

matrix matrix::add(matrix &m2)
{
    matrix add(rows(),cols());
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<column;j++)
        {
            add.mac[i][j]=mac[i][j]+m2.mac[i][j];
        } 
    }
    return add;
}

matrix matrix::subtract(matrix &m2)
{
    matrix new_mac(rows(),cols());
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<column;j++)
        {
            new_mac.mac[i][j]=mac[i][j]-m2.mac[i][j];
        }
    }
    return new_mac;
}

matrix matrix::multiply(matrix &m2)
{
    matrix mull(this->rows(),m2.cols());
		double multiplication=0;
    for(int i=0;i<this->rows();i++)
    {
        for(int j=0;j<m2.cols();j++)
         {
            for(int k=0;k<m2.rows();k++)
            {
                multiplication+=(this->mac[i][k]*m2.mac[k][j]);
            }
            mull.mac[i][j]=multiplication;
            multiplication=0;
        }
    }
    return mull;
}

void matrix::store(string filename, string path)
{
    path += "\\" + filename;
    ofstream  file(path);

    file << row << "\t" << column << endl;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<column; j++ )
        {
            double wart=mac[i][j];
            file <<wart<< "\t";
        }
        file << endl;
    }
    file.close();
}