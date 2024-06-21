#ifndef UNTITLED14_MATRIX_H
#define UNTITLED14_MATRIX_H

#include <iostream>
#include <cfloat>

template <int row, int col, typename T=double >
class Matrix
{
private:
    T **data;
    int rows;
    int cols;


public:
    Matrix(): data(nullptr), rows(0), cols(0) {}
    Matrix(int rows, int cols): rows(row), cols(col)
    {
        data = new T*[rows];
        for (int i = 0; i < rows; i++)
        {
            data[i] = new T[col]();
        }
    }
    Matrix(int val) : rows(row), cols(col)
    {
        data = new T *[rows];
        for (int i = 0; i < rows; i++)
        {
            data[i] = new T[cols];
            for (int j = 0; j < cols; j++)
            {
                data[i][j] = val;
            }
        }
    }
    ~Matrix()
    {
        if(data!=nullptr)
        {
            for(int i=0; i < rows; i++)
            {
                delete[] data[i];
            }
            delete data;
            rows=0;
            cols=0;
        }
    }
    Matrix(const Matrix &mat): rows(mat.rows), cols(mat.cols)
    {
        if(mat.data!=nullptr)
        {
            data = new T*[rows];
            for(int i=0; i < rows; i++)
            {
                data[i] = new T[cols]();
                for(int j=0; j < cols; j++)
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
        return cols;
    }
//    T getData (int rows,int cols)const
//    {
//        if(data!=nullptr && rows < rows && cols < cols)
//        {
//            return data[rows][cols];
//        }
//        return 0;//throw exception
//    };
//mat+scalar
    friend Matrix operator+(const T &scalar,Matrix & mat)
    {
        Matrix result(mat);
        for(int i=0;i<mat.rows; i++)
        {
            for(int j=0;j<mat.cols; j++)
            {
                result.data[i][j]=mat.data[i][j]+scalar;
            }
        }
        return result;
    }
   friend Matrix operator+(Matrix & mat, const T &scalar)
    {
        Matrix result(mat);
        for(int i=0;i<mat.rows; i++)
        {
            for(int j=0;j<mat.cols; j++)
            {
                result.data[i][j]=mat.data[i][j]+scalar;
            }
        }
        return result;
    }
    friend Matrix operator+(const Matrix &mat1, const Matrix &mat2)
    {
        //check if they are the same size

        Matrix result(mat1.rows,mat2.cols);
        for(int i=0;i<mat1.rows; i++)
        {
            for(int j=0;j<mat1.cols; j++)
            {
                result.data[i][j]=(mat1.data[i][j]+mat2.data[i][j]);
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

        for(int i=0;i<mat.row; i++)
        {
            for(int j=0;j<mat.col; j++)
            {
                mat[i][j]*=number;
            }
        }
        return mat;
    }
    friend Matrix operator*(const Matrix& mat1,const Matrix &mat2)
    {
        if (mat1.col == mat2.row)
        {
            Matrix result(mat1.row, mat2.col);
            for(int i=0;i<result.row; i++)
            {
                for(int j=0;j<mat2.col; j++)
                {
                    for(int k=0;k<mat1.col; k++)
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
        if(row != col)
        {
            //throw exception
        }

        Matrix result(row, col);
        for(int i=0; i < row; i++)
        {
            for(int j=0; j < col; j++)
            {
                result.data[i][j]=(i==j)?1:0;
            }
        }
        return result;
    }
     Matrix operator++(const Matrix &mat1)
    {
        return (mat1 + 1);
    }
    friend Matrix operator--(const Matrix &mat1)
    {
        return (mat1-1);
    }
    T* getDiag(int &number)const
    {
        int min= (row < col) ? row : col;

        T *diag= new T[min];
        for(int i=0;i<min;i++)
        {
            diag[i]=data[i][i];
        }
        number=min;
        return diag;
    }
    friend bool operator==(const Matrix& mat1, const Matrix& mat2)
    {
        if(mat1.row != mat2.row || mat1.col != mat2.col)
            return false;
        for(int i=0;i<mat1.row; i++)
        {
            for(int j=0;j<mat1.col; j++)
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
        int minLen= (row < col) ? row : col;
        for(int i=0;i<minLen;i++)
        {
            trace+=data[i][i];
        }
        return trace;
    }
    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat)
    {
        for(int i=0;i<mat.rows; i++)
        {
            for(int j=0;j<mat.cols; j++)
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