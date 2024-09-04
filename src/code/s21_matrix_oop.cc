#include "../s21_matrix_oop.h"

S21Matrix::S21Matrix() {
rows_ = 0; cols_ = 0; matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols):rows_(rows), cols_(cols) {
    CreateMatrix(rows, cols);
}
S21Matrix& S21Matrix::CreateMatrix(int rows, int cols){
     if(rows <= 0|| cols <= 0){
        throw std::invalid_argument("There is rows or cols equals or lesser of zero. ");
    }
    rows_ = rows;
    cols_ = cols;
    matrix_ = new double *[rows];
    for(int i = 0; i < rows; i++){
        matrix_[i] = new double [cols];
    }
}
S21Matrix::~S21Matrix(){
  DeleteMatrix(*this);
}
void S21Matrix::DeleteMatrix(S21Matrix & mtr){
      for(int i = 0; i < rows_; i++){
        delete mtr.matrix_[i];
    }
    delete mtr.matrix_;
    mtr.matrix_= nullptr;
    mtr.rows_ = 0;
    mtr.cols_ = 0;
}

S21Matrix::S21Matrix(const S21Matrix& other){
    CreateMatrix(other.rows_, other.cols_);
    for(int i = 0; i < other.rows_; i++){
        for(int j = 0; j < other.cols_; j++){
            matrix_[i][j]=other.matrix_[i][j];
        }
    }
}

S21Matrix::S21Matrix(S21Matrix && other){
    S21Matrix(*other);
    DeleteMatrix(other);
}