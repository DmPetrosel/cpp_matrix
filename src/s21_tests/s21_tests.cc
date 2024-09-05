#include "s21_tests.h"

int main(int argc, char **argv){
    ::testing::initGoogleTest(argc, argv);
    return RUN_ALL_TESTS();
}