#include "../s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  CreateMatrix(rows, cols);
}
int S21Matrix::GetCols() { return cols_; }
int S21Matrix::GetRows() { return rows_; }

double** S21Matrix::GetMatrix() { try { return matrix_; } catch(std::exception& e) {  std::cerr << e.what(); return nullptr; } }
void S21Matrix::SetMatrixElem(int row, int col, double num) {
  if (row < rows_ && col < cols_)
    matrix_[row][col] = num;
  else
    throw std::out_of_range("Out of range");
}

void S21Matrix::CreateMatrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument(
        "There is rows or cols equals or lesser of zero. ");
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double*[rows];
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new double[cols];
  }
}
S21Matrix::~S21Matrix() { 
    if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      if (matrix_[i]) delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0; 
    }
}
void S21Matrix::DeleteMatrix(S21Matrix& mtr) {
  if (mtr.matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      if (mtr.matrix_[i]) delete[] mtr.matrix_[i];
    }
    delete[] mtr.matrix_;
    mtr.matrix_ = nullptr;
    mtr.rows_ = 0;
    mtr.cols_ = 0;
  }
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  CreateMatrix(other.rows_, other.cols_);
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  CreateMatrix(other.rows_, other.cols_);
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  other.~S21Matrix();
}
S21Matrix S21Matrix::MoveMatrix(S21Matrix&& other) {
  if (cols_ == other.cols_ && rows_ == other.rows_) {
    for (int r = 0; r < rows_; r++) {
      for (int c = 0; c < cols_; c++) {
        matrix_[r][c] = other.matrix_[r][c];
        other.matrix_[r][c] = 0;
      }
    }
    other.cols_ = 0;
    other.rows_ = 0;
    other.matrix_ = nullptr;
  } else
    throw std::invalid_argument("Matices are not compatible. ");

  return *this;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int r = 0; r < rows_; r++) {
      for (int c = 0; c < cols_; c++) {
        matrix_[r][c] += other.matrix_[r][c];
      }
    }
  } else {
    throw std::invalid_argument("Matices are not compatible. ");
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int r = 0; r < rows_; r++) {
      for (int c = 0; c < cols_; c++) {
        matrix_[r][c] -= other.matrix_[r][c];
      }
    }
  } else {
    throw std::invalid_argument("Matices are not compatible. ");
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      matrix_[r][c] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (rows_ <= 0 || cols_ <= 0 || other.rows_ <= 0 || other.cols_ <= 0) {
    throw std::invalid_argument("Values of matrices are unacceptable");
  }
  if (cols_ == other.rows_) {
    S21Matrix temp(rows_, other.cols_);
    for (int r = 0; r < rows_; r++) {
      for (int c = 0; c < other.cols_; c++) {
        temp.matrix_[r][c] = 0;
        for (int k = 0; k < cols_; k++) {
          temp.matrix_[r][c] += matrix_[r][k] * other.matrix_[k][c];
        }
      }
    }
    *this = temp;
  } else {
    throw std::invalid_argument(
        "Columns first matrix is not equal rows of second matrix ");
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix o = S21Matrix(cols_, rows_);
  // printf("%d %d", cols_, rows_);
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      o.matrix_[c][r] = matrix_[r][c];
      // printf("sega catch");
    }
  }
  return o;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  int status = true;
  for (int r = 0; r < rows_ && status; r++) {
    for (int c = 0; c < cols_ && status; c++) {
      double num = s21_dabs((double)matrix_[r][c] - other.matrix_[r][c]);
      double ernum = 1e-6;
      if (num > ernum || num < 0) {
        status = false;
      }
    }
  }
  return status;
}

double S21Matrix::MinorOfElement(int i, int j) {
  S21Matrix result = S21Matrix(rows_ - 1, cols_ - 1);
  int subc = 0, subr = 0;
  for (int r = 0; r < rows_; r++) {
    if (r == i) {
      subr++;
      continue;
    }
    subc = 0;
    for (int c = 0; c < cols_; c++) {
      if (c == j) {
        subc++;
        continue;
      }
      result.matrix_[r - subr][c - subc] = matrix_[r][c];
    }
  }
  double double_res = result.Determinant();
  result.~S21Matrix();
  return double_res;
}

double S21Matrix::Determinant() {
  double result;
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix is not square");
  }
  if (cols_ == 1) {
    result = matrix_[0][0];
  } else if (cols_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    S21Matrix complement = this->CalcComplements();
    for (int i = 0; i < cols_; i++) {
      result += matrix_[0][i] * complement.matrix_[0][i];
    }
    complement.~S21Matrix();
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix is not square");
  }
  S21Matrix result = S21Matrix(rows_, cols_);
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      result.matrix_[r][c] =
          this->MinorOfElement(r, c) * (((r + c) % 2 == 0) ? 1 : -1);
    }
  }
  return result;
}

double s21_dabs(double value) { return (value < 0) ? -value : value; }

double S21Matrix::GetElem(int row, int col){
  return matrix_[row][col];
}
S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix is not square");
  }
  double determinant = 0;
  determinant = this->Determinant();
  S21Matrix result = S21Matrix(*this);
  if (s21_dabs(determinant) > __DBL_EPSILON__) {
    result = result.CalcComplements();
    result = result.Transpose();
    result.MulNumber(1 / determinant);
  } else {
    throw std::invalid_argument("Matrix is not invertible");
  }
  return result;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (*this == other) return *this;
  *this = other;
  other.~S21Matrix();
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
  return *this;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (*this == other) return *this;
  this->~S21Matrix();
  CreateMatrix(other.rows_, other.cols_);
  for(int r = 0; r < rows_; r++) {
    for(int c = 0; c < cols_; c++) {
      matrix_[r][c] = other.matrix_[r][c];
    }
    
  }
  return *this;
}
bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }