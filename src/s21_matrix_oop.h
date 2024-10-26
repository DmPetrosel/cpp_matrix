#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_
#include <iostream>

class S21Matrix {
 private:
  double **matrix_;
  int rows_, cols_;

 public:
  // All constructors are written, tested
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  int GetCols();
  int GetRows();
  double **GetMatrix();
  void SetMatrixElem(int row, int col, double num);

  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);  // Written, Tested
  void SubMatrix(const S21Matrix &other);  // Written, Tested
  void MulNumber(const double num);        // Written, Tested
  void MulMatrix(const S21Matrix &other);  // Written, Tested
  S21Matrix Transpose();                   // Written
  double MinorOfElement(int i, int j);
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other);

  void CreateMatrix(int rows, int cols);
  void DeleteMatrix(S21Matrix &mtr);
  bool operator==(const S21Matrix &other);
  S21Matrix MoveMatrix(S21Matrix &&other);
  double **operator=(double **other);
  double GetElem(int row, int col);
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double num);
  S21Matrix operator+=(const S21Matrix &other);
  S21Matrix operator-=(const S21Matrix &other);
  S21Matrix operator*=(const S21Matrix &other);
  S21Matrix operator*=(const double num);
  double &operator()(int i, int j);
  double &operator()(int i, int j) const;
};
double s21_dabs(double num);
#endif  // S21_MATRIX_OOP_H_