
#ifndef UNTITLED14_MATRIX_H
#define UNTITLED14_MATRIX_H

#include <iostream>
#include <cfloat>

template <class T>
class Matrix
{
private:
    T **data;
    int rows;
    int columns;

public:
    Matrix(): data(nullptr), rows(0), columns(0) {}
    Matrix(int rows, int cols):rows(rows), columns(cols)
    {
        data = new T*[rows];
        for (int i = 0; i < rows; i++)
        {
            data[i] = new T[columns]();
        }
    }
    ~Matrix()
    {
        if(data!=nullptr)
        {
            for(int i=0;i<rows;i++)
            {
                delete[] data[i];
            }
            delete data;
            rows=0;
            columns=0;
        }
    }
    Matrix(const Matrix &mat):rows(mat.rows),columns(mat.columns)
    {
        if(mat.data!=nullptr)
        {
            data = new T*[rows];
            for(int i=0;i<rows;i++)
            {
                data[i] = new T[columns]();
                for(int j=0;j<columns;j++)
                {
                    data[i][j]=mat.data[i][j];   //do we have to use get?
                }
            }
        }
    }
    int getRows ()const
    {
        return rows;
    }
    int getCols ()const
    {
        return columns;
    }
    T getData (int row,int col)const
    {
        if(data!=nullptr && row<rows && col< columns)
        {
            return data[row][col];
        }
        return 0;//throw exception
    };
//mat+scalar
    friend Matrix operator+(const Matrix& mat,const T& scalar)
    {
        Matrix result(mat);

            for(int i=0;i<result.rows;i++)
            {
                for(int j=0;j<result.columns;j++)
                {
                    result[i][j]+=scalar;

                }
            }

        return result;
    }
    //mat-scalar
    friend Matrix operator-(const Matrix& mat,const int &number)
    {
        int num=(number*(-1));
        mat+num;
        return mat;
    }
    //scalar multiplication
    friend Matrix operator*(const Matrix& mat,const int &number)
    {
        Matrix result(mat);

            for(int i=0;i<mat.rows;i++)
            {
                for(int j=0;j<mat.columns;j++)
                {
                    mat[i][j]*=number;
                }
            }
        return mat;
    }
    friend Matrix operator*(const Matrix& mat1,const Matrix &mat2)
    {
        if (mat1.columns == mat2.rows)
        {
            Matrix result(mat1.rows,mat2.columns);
            for(int i=0;i<result.rows;i++)
            {
                for(int j=0;j<mat2.columns;j++)
                {
                    for(int k=0;k<mat1.columns;k++)
                    {
                        result.data[i][j]+= (mat1.data[i][k]*mat2.data[k][j]);
                    }
                }
            }
            return result;

        }

    }
    Matrix getIdentityMatrix()
    {
        if(rows != columns)
        {
            //throw exception
        }

        Matrix result(rows,columns);
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<columns;j++)
            {
                result.data[i][j]=(i==j)?1:0;
            }
        }
        return result;
    }
    friend Matrix operator++(const Matrix &mat1)
    {
        return (mat1+1);
    }
    friend Matrix operator--(const Matrix &mat1)
    {
        return (mat1-1);
    }
    T* getDiag(int &number)const
    {
        int min= (rows < columns)? rows : columns;
        number=min; //?
        T *diag= new T*[min];
        for(int i=0;i<min;i++)
        {
            diag[i]=data[i][i];
        }
        return diag;
    }
    friend bool operator==(const Matrix& mat1, const Matrix& mat2)
    {
        if(mat1.rows!=mat2.rows || mat1.columns!= mat2.columns)
            return false;
        for(int i=0;i<mat1.rows;i++)
        {
            for(int j=0;j<mat1.columns;j++)
            {
                T diff=mat1.data[i][j]-mat2.data[i][j];
                diff= (diff>=0)?diff:-diff;
                if(diff>=DBL_EPSILON)
                    return false;
            }
        }
        return true;

    }
    friend bool operator!=(const Matrix& mat1, const Matrix& mat2)
    {
        return !(mat1==mat2);
    }
     operator T()const
    {
        T trace=0;
        int minLen= (rows< columns)? rows:columns;
        for(int i=0;i<minLen;i++)
        {
            trace+=data[i][i];
        }
        return trace;
    }
    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat)
    {
        for(int i=0;i<mat.rows;i++)
        {
            for(int j=0;j<mat.columns;j++)
            {
                os<<mat.data[i][j]<<' ';
            }
            os<< '\n';

        }
        return os;
    }
     T& operator()( const int i,const int j)
    {
        return data[i][j];
    }
    const T& operator()( const int i,const int j) const
    {
        return data[i][j];
    }









};




#endif //UNTITLED14_MATRIX_H
