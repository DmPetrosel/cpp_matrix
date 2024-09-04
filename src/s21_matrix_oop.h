#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_
#include <iostream>

class S21Matrix{
    private:
        double **matrix_;
        int rows_, cols_;
    public: 
        S21Matrix();
        S21Matrix(int rows, int cols); 
        S21Matrix(const S21Matrix& other);
        S21Matrix(S21Matrix&& other);
        ~S21Matrix();

        bool EqMatrix(const S21Matrix& other);
        void SumMatrix(const S21Matrix& other);
        void SubMatrix(const S21Matrix& other);
        void MulNumber(const double num) ;
        void MulMatrix(const S21Matrix& other);
        S21Matrix Transpose();
        S21Matrix CalcComplements();
        double Determinant();
        S21Matrix InverseMatrix();

        S21Matrix& operator=(S21Matrix &other);
        S21Matrix& operator=(S21Matrix &&other);
        S21Matrix& operator=(S21Matrix other);
        
        S21Matrix& CreateMatrix(int rows, int cols);
        void DeleteMatrix(S21Matrix &mtr);

};

#endif // S21_MATRIX_OOP_H_