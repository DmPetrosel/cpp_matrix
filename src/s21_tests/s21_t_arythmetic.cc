#include "s21_tests.h"
TEST(sum, sum_1){
    S21Matrix A = S21Matrix(1,2);
    S21Matrix B = S21Matrix(1, 2);
    A.SetMatrixElem(0,0, 1.0);
    A.SetMatrixElem(0,1, 2.0);
    B.SetMatrixElem(0,0, 1.0);
    B.SetMatrixElem(0,1, 2.0);
    A.SumMatrix(B);
    EXPECT_DOUBLE_EQ(A.GetMatrix()[0][0], 2.0);
    EXPECT_DOUBLE_EQ(A.GetMatrix()[0][1], 4.0);
}

TEST(sum, sum_2){
    S21Matrix A = S21Matrix(1,2);
    S21Matrix B = S21Matrix(1, 3);
    A.SetMatrixElem(0,0, 1.0);
    A.SetMatrixElem(0,1, 2.0);
    B.SetMatrixElem(0,0, 1.0);
    B.SetMatrixElem(0,1, 2.0);
    B.SetMatrixElem(0,2, 2.0);
    EXPECT_ANY_THROW(A.SumMatrix(B));
}
TEST(sub, sub_1){
    S21Matrix A = S21Matrix(1,2);
    S21Matrix B = S21Matrix(1, 2);
    A.SetMatrixElem(0,0, 1.0);
    A.SetMatrixElem(0,1, 4.0);
    B.SetMatrixElem(0,0, 1.0);
    B.SetMatrixElem(0,1, 2.0);
    A.SubMatrix(B);
    EXPECT_DOUBLE_EQ(A.GetMatrix()[0][0], 0.0);
    EXPECT_DOUBLE_EQ(A.GetMatrix()[0][1], 2.0);
}

TEST(sub, sub_2){
    S21Matrix A = S21Matrix(1,2);
    S21Matrix B = S21Matrix(1, 3);
    A.SetMatrixElem(0,0, 1.0);
    A.SetMatrixElem(0,1, 2.0);
    B.SetMatrixElem(0,0, 1.0);
    B.SetMatrixElem(0,1, 2.0);
    B.SetMatrixElem(0,2, 2.0);
    EXPECT_ANY_THROW(A.SumMatrix(B));
}

TEST(mulNumber, muln_1){
    S21Matrix A = S21Matrix(1,2);
    A.SetMatrixElem(0,0, 1.0);
    A.SetMatrixElem(0,1, 4.0);
    double number = 3;
    A.MulNumber(number);
    EXPECT_DOUBLE_EQ(A.GetMatrix()[0][0], 3.0);
    EXPECT_DOUBLE_EQ(A.GetMatrix()[0][1], 12.0);
}

TEST(multMatrix, mm_1){
    S21Matrix A = S21Matrix(1,2);
    S21Matrix B = S21Matrix(1, 3);
    A.SetMatrixElem(0,0, 1.0);
    A.SetMatrixElem(0,1, 2.0);
    B.SetMatrixElem(0,0, 1.0);
    B.SetMatrixElem(0,1, 2.0);
    B.SetMatrixElem(0,2, 2.0);
    EXPECT_ANY_THROW(A.MulMatrix(B));
}
TEST(multMatrix, mm_2){
    S21Matrix A = S21Matrix(3,2);
    S21Matrix B = S21Matrix(2,3);
    A.SetMatrixElem(0,0, 1.0);
    A.SetMatrixElem(0,1, 4.0);
    A.SetMatrixElem(1,0, 2.0);
    A.SetMatrixElem(1,1, 5.0);
    A.SetMatrixElem(2,0, 3.0);
    A.SetMatrixElem(2,1, 6.0);

    B.SetMatrixElem(0,1, 1.0);
    B.SetMatrixElem(0,2, -1.0);
    B.SetMatrixElem(0,3, 1.0);
    B.SetMatrixElem(1,1, 2.0);
    B.SetMatrixElem(1,2, 3.0);
    B.SetMatrixElem(1,3, 4.0);
    A.MulMatrix(B);
    EXPECT_DOUBLE_EQ(A.GetMatrix()[0][0], 9.0);
    EXPECT_DOUBLE_EQ(A.GetMatrix()[0][1], 11.0);
    EXPECT_DOUBLE_EQ(A.GetMatrix()[0][2], 17.0);
    EXPECT_DOUBLE_EQ(A.GetMatrix()[1][0], 12.0);
    EXPECT_DOUBLE_EQ(A.GetMatrix()[1][1], 13.0);
    EXPECT_DOUBLE_EQ(A.GetMatrix()[1][2], 22.0);
    EXPECT_DOUBLE_EQ(A.GetMatrix()[2][0], 15.0);
    EXPECT_DOUBLE_EQ(A.GetMatrix()[2][1], 15.0);
    EXPECT_DOUBLE_EQ(A.GetMatrix()[2][2], 27.0);
}
