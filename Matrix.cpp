#include "Matrices.h"
#include <cmath>

namespace Matrices
{
    Matrix::Matrix(int _rows, int _cols)
    {
        //assign member variables
        rows = _rows;
        cols = _cols;
        //resize the vector
       a.resize(rows);
        for (size_t i = 0; i < rows; i++)
          {
            a[i].resize(cols);
            for (size_t j = 0; j < cols; j++)
              {
                a[i][j] = 0;
              }
          }
        a.resize(rows, vector<double>(cols, 0));
    }
    ostream& operator<<(ostream& os, const Matrix& a)
    {
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                os << setw(15) << a(i, j) << " ";
            }
            cout << endl;
        }
        return os; //cout << a << endl;
    }
    Matrix operator+(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getCols() || a.getRows() != b.getRows())
        {
            throw runtime_error("Eror: dimensions must agree");
        }
        //add stuff
        Matrix c(a.getRows(), a.getCols());
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                c(i, j) = a(i, j) + b(i, j);
            }
        }
        return c;
    }

    Matrix operator*(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getRows())
        {
            throw runtime_error("Eror: dimensions must agree");
        }
        Matrix c(a.getRows(), b.getCols()); //cells init to 0;

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int k = 0; k < b.getCols(); k++)
            {
                for (int j = 0; j < a.getCols(); j++)
                {
                    c(i, k) += a(i, j) * b(j, k);
                }
            }
        }
        return c;
    }

    bool operator==(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            return false;
        }
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < b.getCols(); j++)
            {
                if (fabs(a(i, j) - b(i, j)) > 0.001)
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator!=(const Matrix& a, const Matrix& b)
    {
        //return !(a==b);
        if (a.getRows() == b.getRows() || a.getCols() == b.getCols())
        {
            return false;
        }
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < b.getCols(); j++)
            {
                if (fabs(a(i, j) - b(i, j)) > 0.001)
                {
                    return true;
                }
            }
        }
        return false;
    }
    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
    {
        a[0][0] = cos(theta);
        a[0][1] = -sin(theta);
        a[1][0] = sin(theta);
        a[1][1] = cos(theta);
    }
    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
    {
        a[0][0] = scale;
        a[0][1] = 0;
        a[1][0] = 0;
        a[1][1] = scale;
    }
    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
    {
        for (int j = 0; j < nCols; j++)
        {
            a[0][j] = xShift;
            a[1][j] = yShift;
        }
    }
}