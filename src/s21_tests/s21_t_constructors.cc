#include "s21_tests.h"
TEST(create, cr_1){
    S21Matrix m = S21Matrix();
    EXPECT_EQ(m.GetRows(), 0);
    EXPECT_EQ(m.GetCols(), 0);
}
TEST(create, cr_2){
    S21Matrix m = S21Matrix(1,5);
    EXPECT_EQ(m.GetRows(), 1);
    EXPECT_EQ(m.GetCols(), 5);
}
TEST(create, cr_3){ 
    EXPECT_ANY_THROW(S21Matrix(1,0));
}
TEST(create, cr_4){ 
    EXPECT_ANY_THROW(S21Matrix(0,1));
}
TEST(create, cr_5){ 
    EXPECT_ANY_THROW(S21Matrix(0,0));
}
TEST(create, cr_6){ 
    EXPECT_ANY_THROW(S21Matrix(-1,0));
}
TEST(create, cr_7){ 
    EXPECT_ANY_THROW(S21Matrix(1,-1));
}

TEST(copy_constructor, cc_1){
    S21Matrix A = S21Matrix(3,3);
    for(int r = 0; r < A.GetRows(); r++){
        for(int c = 0; c < A.GetCols(); c++){ 
            A.SetMatrixElem(r, c, 1+r*A.GetCols()+c);
        }
    }
    S21Matrix copyc = S21Matrix(A);
    ASSERT_DOUBLE_EQ(A.GetMatrix()[1][1],5.0);
    ASSERT_DOUBLE_EQ(copyc.GetMatrix()[1][1],5.0);
}
TEST(move_constructor, cc_1){
    S21Matrix A = S21Matrix(3,3);
    for(int r = 0; r < A.GetRows(); r++){
        for(int c = 0; c < A.GetCols(); c++){ 
            A.SetMatrixElem(r, c, 1+r*A.GetCols()+c);
        }
    }
    S21Matrix movec = std::move(A);
    EXPECT_EQ(A.GetMatrix(), nullptr);
    ASSERT_DOUBLE_EQ(movec.GetMatrix()[1][1],5.0);
}