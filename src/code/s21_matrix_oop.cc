#include "../s21_matrix_oop.h"

S21Matrix::S21Matrix() {
rows_ = 0; cols_ = 0; matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols):rows_(rows), cols_(cols) {
    CreateMatrix(rows, cols);
}
int S21Matrix::GetCols(){
    return cols_;
}
int S21Matrix::GetRows(){
    return rows_;
}

double** S21Matrix::GetMatrix(){
    return matrix_;
}
void S21Matrix::SetMatrixElem(int row, int col, double num){
    matrix_[row][col] = num;
}

void S21Matrix::CreateMatrix(int rows, int cols){
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
    if(mtr.matrix_!=nullptr){
      for(int i = 0; i < rows_; i++){
        if(mtr.matrix_[i])
            delete [] mtr.matrix_[i];
    }
    delete [] mtr.matrix_;
    mtr.matrix_= nullptr;
    mtr.rows_ = 0;
    mtr.cols_ = 0;
    }
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
    CreateMatrix(other.rows_, other.cols_);
    for(int i = 0; i < other.rows_; i++){
        for(int j = 0; j < other.cols_; j++){
            matrix_[i][j]=other.matrix_[i][j];
        }
    }
    DeleteMatrix(other);
}

void S21Matrix::SumMatrix(const S21Matrix & other){
    if(rows_ == other.rows_ && cols_==other.cols_){
        for(int r = 0; r < rows_; r++){
            for(int c = 0; c < cols_; c++){
                matrix_[r][c] += other.matrix_[r][c];
            }
        }
    }
    else {
        throw std::invalid_argument("Matices are not compatible. ");
    }
}

void S21Matrix::SubMatrix(const S21Matrix & other){
    if(rows_ == other.rows_ && cols_==other.cols_){
        for(int r = 0; r < rows_; r++){
            for(int c = 0; c < cols_; c++){
                matrix_[r][c] -= other.matrix_[r][c];
            }
        }
    }
    else {
        throw std::invalid_argument("Matices are not compatible. ");
    }
}

void S21Matrix::MulNumber(const double num){
    for(int r = 0; r < rows_; r++){
        for(int c = 0; c < cols_; c++){
            matrix_[r][c] *= num;
        }
    }
}

void S21Matrix::MulMatrix(const S21Matrix& other){
    if(rows_<=0 || cols_ <= 0||other.rows_ <= 0 || other.cols_ <= 0){
        throw std::invalid_argument("Values of matrices are unacceptable");
    }
    if(cols_!=other.rows_){
        S21Matrix *temp = new S21Matrix(rows_, other.cols_);
        for(int r = 0; r < rows_; r++){
            for(int c = 0; c < other.cols_; c++){
                for(int k = 0; k < other.rows_; k++){
                    temp->matrix_[r][c] += matrix_[r][k]*other.matrix_[k][c];
                }
            }
        }
        S21Matrix::~S21Matrix();
        S21Matrix(*this);
        S21Matrix::DeleteMatrix(*temp);
    }
    else{
        throw std::invalid_argument("Columns first matrix equals rows of second matrix ");
    }
}

   S21Matrix S21Matrix::Transpose(){
    S21Matrix o = S21Matrix(cols_,rows_);
    for(int r = 0; r < rows_; r++){
        for(int c = 0; c < cols_; c++){
            o.matrix_[c][r] = matrix_[r][c];
        }
    }
    return o;
   }