#include "s21_tests.h"
TEST(sum, sum_1) {
  S21Matrix A = S21Matrix(1, 2);
  S21Matrix B = S21Matrix(1, 2);
  A.SetMatrixElem(0, 0, 1.0);
  A.SetMatrixElem(0, 1, 2.0);
  B.SetMatrixElem(0, 0, 1.0);
  B.SetMatrixElem(0, 1, 2.0);
  A.SumMatrix(B);
  EXPECT_DOUBLE_EQ(A.GetMatrix()[0][0], 2.0);
  EXPECT_DOUBLE_EQ(A.GetMatrix()[0][1], 4.0);
}

TEST(sum, sum_2) {
  S21Matrix A = S21Matrix(1, 2);
  S21Matrix B = S21Matrix(1, 3);
  A.SetMatrixElem(0, 0, 1.0);
  A.SetMatrixElem(0, 1, 2.0);
  B.SetMatrixElem(0, 0, 1.0);
  B.SetMatrixElem(0, 1, 2.0);
  B.SetMatrixElem(0, 2, 2.0);
  EXPECT_ANY_THROW(A.SumMatrix(B));
}
TEST(sub, sub_1) {
  S21Matrix A = S21Matrix(1, 2);
  S21Matrix B = S21Matrix(1, 2);
  A.SetMatrixElem(0, 0, 1.0);
  A.SetMatrixElem(0, 1, 4.0);
  B.SetMatrixElem(0, 0, 1.0);
  B.SetMatrixElem(0, 1, 2.0);
  A.SubMatrix(B);
  EXPECT_DOUBLE_EQ(A.GetMatrix()[0][0], 0.0);
  EXPECT_DOUBLE_EQ(A.GetMatrix()[0][1], 2.0);
}

TEST(sub, sub_2) {
  S21Matrix A = S21Matrix(1, 2);
  S21Matrix B = S21Matrix(1, 3);
  A.SetMatrixElem(0, 0, 1.0);
  A.SetMatrixElem(0, 1, 2.0);
  B.SetMatrixElem(0, 0, 1.0);
  B.SetMatrixElem(0, 1, 2.0);
  B.SetMatrixElem(0, 2, 2.0);
  EXPECT_ANY_THROW(A.SumMatrix(B));
}

TEST(mulNumber, muln_1) {
  S21Matrix A = S21Matrix(1, 2);
  A.SetMatrixElem(0, 0, 1.0);
  A.SetMatrixElem(0, 1, 4.0);
  double number = 3;
  A.MulNumber(number);
  EXPECT_DOUBLE_EQ(A.GetMatrix()[0][0], 3.0);
  EXPECT_DOUBLE_EQ(A.GetMatrix()[0][1], 12.0);
}

TEST(multMatrix, mm_1) {
  S21Matrix A = S21Matrix(1, 2);
  S21Matrix B = S21Matrix(1, 3);
  A.SetMatrixElem(0, 0, 1.0);
  A.SetMatrixElem(0, 1, 2.0);
  B.SetMatrixElem(0, 0, 1.0);
  B.SetMatrixElem(0, 1, 2.0);
  B.SetMatrixElem(0, 2, 2.0);
  EXPECT_ANY_THROW(A.MulMatrix(B));
}
TEST(multMatrix, mm_2) {
  S21Matrix A = S21Matrix(3, 2);
  S21Matrix B = S21Matrix(2, 3);
  A.SetMatrixElem(0, 0, 1.0);
  A.SetMatrixElem(0, 1, 4.0);
  A.SetMatrixElem(1, 0, 2.0);
  A.SetMatrixElem(1, 1, 5.0);
  A.SetMatrixElem(2, 0, 3.0);
  A.SetMatrixElem(2, 1, 6.0);

  B.SetMatrixElem(0, 0, 1.0);
  B.SetMatrixElem(0, 1, -1.0);
  B.SetMatrixElem(0, 2, 1.0);
  B.SetMatrixElem(1, 0, 2.0);
  B.SetMatrixElem(1, 1, 3.0);
  B.SetMatrixElem(1, 2, 4.0);
  A.MulMatrix(B);
  EXPECT_LE(s21_dabs( 9.0 - A.GetMatrix()[0][0]), __DBL_EPSILON__);
  EXPECT_LE(s21_dabs(11.0 - A.GetMatrix()[0][1]), __DBL_EPSILON__);
  EXPECT_LE(s21_dabs(17.0 - A.GetMatrix()[0][2]), __DBL_EPSILON__);
  EXPECT_LE(s21_dabs(12.0 - A.GetMatrix()[1][0]), __DBL_EPSILON__);
  EXPECT_LE(s21_dabs(13.0 - A.GetMatrix()[1][1]), __DBL_EPSILON__);
  EXPECT_LE(s21_dabs(22.0 - A.GetMatrix()[1][2]), __DBL_EPSILON__);
  EXPECT_LE(s21_dabs(15.0 - A.GetMatrix()[2][0]), __DBL_EPSILON__);
  EXPECT_LE(s21_dabs(15.0 - A.GetMatrix()[2][1]), __DBL_EPSILON__);
  EXPECT_LE(s21_dabs(27.0 - A.GetMatrix()[2][2]), __DBL_EPSILON__);
  A.~S21Matrix();
  B.~S21Matrix();
}

TEST(s21_eq, eq_1) {
  S21Matrix A = S21Matrix(3, 2);
  S21Matrix B = S21Matrix(3, 2);

  double num = 5.51;
  for (int r = 0; r < A.GetRows(); r++) {
    for (int c = 0; c < A.GetCols(); c++) {
      A.GetMatrix()[r][c] = B.GetMatrix()[r][c] = (r + c) * num;
    }
  }
  int status = A.EqMatrix(B);
  EXPECT_TRUE(status);
}

TEST(s21_eq, eq_2) {
  S21Matrix A = S21Matrix(3, 2);
  S21Matrix B = S21Matrix(3, 2);

  double num = 5.51;
  for (int r = 0; r < A.GetRows(); r++) {
    for (int c = 0; c < A.GetCols(); c++) {
      A.GetMatrix()[r][c] = B.GetMatrix()[r][c] = (r + c) * num;
    }
  }
  A.GetMatrix()[0][1] = 4;
  int status = A.EqMatrix(B);
  EXPECT_FALSE(status);
}

TEST(s21_eq, eq_3) {
  S21Matrix A = S21Matrix(3, 2);
  S21Matrix B = S21Matrix(4, 3);

  double num = 5.51;
  for (int r = 0; r < A.GetRows(); r++) {
    for (int c = 0; c < A.GetCols(); c++) {
      A.SetMatrixElem(r, c, (r + c) * num);
    }
  }
  for (int r = 0; r < B.GetRows(); r++) {
    for (int c = 0; c < B.GetCols(); c++) {
      B.SetMatrixElem(r,c, (r + c) * num);
    }
  }
  int status = A.EqMatrix(B);
  EXPECT_FALSE(status);
}

TEST(s21_eq, eq_4) {
  S21Matrix A = S21Matrix(2, 3);
  S21Matrix B = S21Matrix(2, 3);

  A.SetMatrixElem(0,0, 1.123456789);
  A.SetMatrixElem(0,1, 1.123456789);
  A.SetMatrixElem(0,2, 1.123456789);
  A.SetMatrixElem(1,0, 1.123456789);
  A.SetMatrixElem(1,1, 1.123456789);
  A.SetMatrixElem(1,2, 1.123456789);
  B.SetMatrixElem(0,0, 1.123456789);
  B.SetMatrixElem(0,1, 1.123456789);
  B.SetMatrixElem(0,2, 1.123456789);
  B.SetMatrixElem(1,0, 1.123456789);
  B.SetMatrixElem(1,1, 1.123456789);
  B.SetMatrixElem(1,2, 1.123456111);

  int status = A.EqMatrix(B);
  EXPECT_TRUE(status);
}
TEST(s21_eq, eq_5) {
  S21Matrix A = S21Matrix(2, 3);
  S21Matrix B = S21Matrix(2, 3);

  A.SetMatrixElem(0,0, 1.123456789);
  A.SetMatrixElem(0,1, 1.123456789);
  A.SetMatrixElem(0,2, 1.123456789);
  A.SetMatrixElem(1,0, 1.123456789);
  A.SetMatrixElem(1,1, 1.123456789);
  A.SetMatrixElem(1,2, 1.123456789);
  B.SetMatrixElem(0,0, 1.123456789);
  B.SetMatrixElem(0,1, 1.123456789);
  B.SetMatrixElem(0,2, 1.123456789);
  B.SetMatrixElem(1,0, 1.123456789);
  B.SetMatrixElem(1,1, 1.123456789);
  B.SetMatrixElem(1,2, 1.123451111);

  int status = A.EqMatrix(B);
  EXPECT_FALSE(status);
}

TEST(s21_compl, compl_1) {
  S21Matrix A = S21Matrix(3, 3);

  A.SetMatrixElem(0,0, 5);
  A.SetMatrixElem(0,1, 7);
  A.SetMatrixElem(0,2, 1);
  A.SetMatrixElem(1,0, -4);
  A.SetMatrixElem(1,1, 1);
  A.SetMatrixElem(1,2, 0);
  A.SetMatrixElem(2,0, 2);
  A.SetMatrixElem(2,1, 0);
  A.SetMatrixElem(2,2, 3);

  A = A.CalcComplements();
  EXPECT_LE(s21_dabs(A.GetMatrix()[2][2] - 33), __DBL_EPSILON__);

}
TEST(s21_compl, compl_2) {
 S21Matrix A = S21Matrix(3, 3);

  A.SetMatrixElem(0,0, 1);
  A.SetMatrixElem(0,1, 2);
  A.SetMatrixElem(0,2, 3);
  A.SetMatrixElem(1,0, 0);
  A.SetMatrixElem(1,1, 4);
  A.SetMatrixElem(1,2, 2);
  A.SetMatrixElem(2,0, 5);
  A.SetMatrixElem(2,1, 2);
  A.SetMatrixElem(2,2, 1);


  A = A.CalcComplements();
  EXPECT_LE(s21_dabs(A.GetMatrix()[0][0] - 0), __DBL_EPSILON__);

}
TEST(s21_compl, compl_3) {
  S21Matrix A = S21Matrix(3, 3);


  A.SetMatrixElem(0,0,1);
  A.SetMatrixElem(0,1,2);
  A.SetMatrixElem(0,2,3);
  A.SetMatrixElem(1,0,0);
  A.SetMatrixElem(1,1,4);
  A.SetMatrixElem(1,2,2);
  A.SetMatrixElem(2,0,5);
  A.SetMatrixElem(2,1,2);
  A.SetMatrixElem(2,2,1);


  A = A.CalcComplements();
  EXPECT_LE(s21_dabs(A.GetMatrix()[0][1] - 10), __DBL_EPSILON__);
}
TEST(s21_compl, compl_4) {
  S21Matrix A = S21Matrix(3, 3);
  A.SetMatrixElem(0,0, 1);
  A.SetMatrixElem(0,1, 2);
  A.SetMatrixElem(0,2, 3);
  A.SetMatrixElem(1,0, 0);
  A.SetMatrixElem(1,1, 4);
  A.SetMatrixElem(1,2, 2);
  A.SetMatrixElem(2,0, 5);
  A.SetMatrixElem(2,1, 2);
  A.SetMatrixElem(2,2, 1);

A = A.CalcComplements();

  EXPECT_LE(s21_dabs(A.GetMatrix()[0][2] + 20), __DBL_EPSILON__);
}

TEST(s21_compl, compl_5) {
 S21Matrix A = S21Matrix(2, 3);
  A.SetMatrixElem(0,0, 1);
  A.SetMatrixElem(0,1, 2);
  A.SetMatrixElem(0,2, 3);
  A.SetMatrixElem(1,0, 0);
  A.SetMatrixElem(1,1, 4);
  A.SetMatrixElem(1,2, 2);


EXPECT_ANY_THROW(A.CalcComplements());
}

TEST(s21_det, det_1) {
  S21Matrix A = S21Matrix(3, 3);


  A.SetMatrixElem(0,0, 1);
  A.SetMatrixElem(0,1, 2);
  A.SetMatrixElem(0,2, 3);
  A.SetMatrixElem(1,0, 4);
  A.SetMatrixElem(1,1, 5);
  A.SetMatrixElem(1,2, 6);
  A.SetMatrixElem(2,0, 7);
  A.SetMatrixElem(2,1, 8);
  A.SetMatrixElem(2,2, 9);

  EXPECT_LE(s21_dabs(A.Determinant() - 0), __DBL_EPSILON__);
}
TEST(s21_det, det_2) {
S21Matrix A = S21Matrix(3, 3);
  A.SetMatrixElem(0,0, 5);
  A.SetMatrixElem(0,1, 6);
  A.SetMatrixElem(0,2, 7);
  A.SetMatrixElem(1,0, 8);
  A.SetMatrixElem(1,1, 9);
  A.SetMatrixElem(1,2, 0);
  A.SetMatrixElem(2,0, 1);
  A.SetMatrixElem(2,1, 2);
  A.SetMatrixElem(2,2, 3);

  EXPECT_LE(s21_dabs(A.Determinant()- 40), __DBL_EPSILON__);
}
TEST(s21_det, det_3) {
  S21Matrix A = S21Matrix(2, 3);

  A.SetMatrixElem(0,0, 1);
  A.SetMatrixElem(0,1, 2);
  A.SetMatrixElem(0,2, 3);
  A.SetMatrixElem(1,0, 0);
  A.SetMatrixElem(1,1, 4);
  A.SetMatrixElem(1,2, 2);

  EXPECT_ANY_THROW(A.Determinant());
}

TEST(s21_inverseб , inverse_1) {
  S21Matrix A = S21Matrix(3, 3);
  A.SetMatrixElem(0,0, 2);
  A.SetMatrixElem(0,1, 5);
  A.SetMatrixElem(0,2, 7);
  A.SetMatrixElem(1,0, 6);
  A.SetMatrixElem(1,1, 3);
  A.SetMatrixElem(1,2, 4);
  A.SetMatrixElem(2,0, 5);
  A.SetMatrixElem(2,1, -2);
  A.SetMatrixElem(2,2, -3);

  A = A.InverseMatrix();

  EXPECT_LE(s21_dabs(A.GetMatrix()[0][0] - 1), __DBL_EPSILON__);
}
TEST(s21_inverse, inverse_2) {
S21Matrix A = S21Matrix(3, 3);

  A.SetMatrixElem(0,0, 2);
  A.SetMatrixElem(0,1, 5);
  A.SetMatrixElem(0,2, 7);
  A.SetMatrixElem(1,0, 6);
  A.SetMatrixElem(1,1, 3);
  A.SetMatrixElem(1,2, 4);
  A.SetMatrixElem(2,0, 5);
  A.SetMatrixElem(2,1, -2);
  A.SetMatrixElem(2,2, -3);

A = A.InverseMatrix();
  EXPECT_LE(s21_dabs(A.GetMatrix()[1][0] + 38), __DBL_EPSILON__);
}
TEST(s21_inverse, inverse_3) {
  S21Matrix A = S21Matrix(2, 3);
  
  A.SetMatrixElem(0,0, 1);
  A.SetMatrixElem(0,1, 2);
  A.SetMatrixElem(0,2, 3);
  A.SetMatrixElem(1,0, 0);
  A.SetMatrixElem(1,1, 4);
  A.SetMatrixElem(1,2, 2);

EXPECT_ANY_THROW(A.InverseMatrix());
}