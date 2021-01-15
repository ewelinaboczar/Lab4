#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <Matrix/matrix.hpp>

using namespace std;

class WrongRow : public exception
{
    virtual const char *what() const throw()
    {
        return "Exeption4: Brak zadanego wiersza";
    }
};

class WrongElement : public exception
{
    virtual const char *what() const throw()
    {
        return "Exeption1: Brak zadanego elementu";
    }
};

class WrongOpenFile : public exception
{
    virtual const char *what() const throw()
    {
        return "Exeption2: Blad otwarcia pliku";
    }
};

class WrongSize : public exception
{
    virtual const char *what() const throw()
    {
        return "Exeption3: Zly rozmiar macierzy";
    }
};

matrix::matrix(std::string path)

{
    ifstream file;
    file.open(path);
    if(file.is_open()==false)
    {
        throw WrongOpenFile();
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
        file.close();
    }  
}

matrix::matrix (int r, int c)
{
    if(r<=0 || c<=0)
    {
        throw WrongElement();
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
        throw WrongElement();
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
    if((n<0 || n>row) || (m<1 || m>column))
    {
        throw WrongElement();
    }
    else
    {
        mac[n-1][m-1]=val;
    }
}

double matrix::get(int n,int m)
{
    if((n<0 || n>=row) || (m<1 || m>=column))
    {
        throw WrongElement();
    }
    else
    {
        return mac[n-1][m-1];
    }
}

matrix matrix::operator+(matrix &m2)
{
    if(row == m2.rows() && column == m2.cols())
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
    else
    {
        throw WrongSize();
    }     
}

matrix matrix::operator-(matrix &m2)
{
    if(row == m2.rows() && column == m2.cols())
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
    else
    {
        throw WrongSize();
    }
}

matrix matrix::operator*(matrix &m2)
{
    if(column == m2.rows())
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
    else
    {
        throw WrongSize();
    }
}

void matrix::store(string filename, string path)
{
    path += "\\" + filename;
    ofstream  file(path);

    if(file.is_open())
    {
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
    else
    {
        throw WrongOpenFile();
    }
}

void matrix::operator==(matrix &m2)
{
    if(row==m2.rows() && column==m2.cols())
    {
        int stan=0;
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<column;j++)
            {
                if(mac[i][j]==m2.mac[i][j])
                {
                    stan++;
                }
            }
        }
        if(stan==row*column)
        {
            cout<<"obie macierze sa identycze"<<endl;
        }
        else
        {
            cout<<"te dwie macierze sa rozne"<<endl;
        }
    }
    else
    {
        throw WrongSize();
    } 
}

void matrix::operator[](int no_row)
{
    if(no_row>=1 && no_row<=row)
    {
        for(int i=0;i<column;i++)
        {
            cout<<mac[no_row-1][i]<<"\t";
        }
        cout<<endl; 
    }   
    else
    {
        throw WrongRow();
    }
}

void matrix::operator++(int value)
{
    double wartosc;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<column;j++)
        {
            wartosc=mac[i][j]+value;
            mac[i][j]=wartosc;
            wartosc=0;
        }
    }
}

void matrix::operator--(int value)
{
    double wartosc;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<column;j++)
        {
            wartosc=mac[i][j]-value;
            mac[i][j]=wartosc;
            wartosc=0;
        }
    }
}
