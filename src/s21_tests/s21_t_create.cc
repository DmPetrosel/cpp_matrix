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