CC = g++
CFLAGS = -g -Wall -Wextra -std=c++17 -Werror
LDFLAGS = -lgtest -pthread 
TARGET = s21_matrix_oop.a

TESTS = s21_tests/*.cc

GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov
CODE=code
OBJ_DIR=obj
CFOLD=cov
SRC_FILES = $(wildcard $(CODE)/*.cc)
OBJ_FILES = $(patsubst %.cc, $(OBJ_DIR)/%.o, $(notdir $(SRC_FILES)))
OBJ_COV = $(patsubst %.cc, $(CFOLD)/%_coverage.o,$(notdir $(SRC_FILES)))


all: clean $(TARGET)

$(OBJ_DIR)/%.o: $(CODE)/%.cc s21_matrix_oop.h prepare_obj
	$(CC) $(CFLAGS) -c $< -o $@

$(CFOLD)/%_coverage.o: $(CODE)/%.cc s21_matrix_oop.h prepare_cov
	$(CC) $(CFLAGS) -c --coverage $< -o $@

s21_matrix_oop.a: $(OBJ_FILES)
	ar -crs $@ $(OBJ_DIR)/*.o 

s21_matrix_oop_cov.a: $(OBJ_COV)
	ar -crs $@ $(CFOLD)/*.o 



prepare_obj:
	mkdir -p $(OBJ_DIR)

prepare_cov:
	mkdir -p $(CFOLD)

test: clean s21_matrix_oop.a $(TESTS) s21_tests/s21_tests.h
	$(CC) $(CFLAGS) -o s21_tests.out $(TESTS) -L. -l:s21_matrix_oop.a $(LDFLAGS)

s21_matrix_oop_tests_cov: s21_matrix_oop_cov.a $(TESTS) s21_tests/s21_tests.h
	$(CC) $(CFLAGS) -o $@ $(TESTS) -L. -l:$< $(GCOV_FLAGS) $(LDFLAGS)

gcov_report: s21_matrix_oop_tests_cov
	./$<
	-lcov --directory $(shell pwd) -c -o coverage.info 
	mkdir -p html
	genhtml -o html coverage.info
	open html/index.html

clang:
	cp ../materials/linters/.clang-format .
	find . \( -name '*.c' -o -name '*.h' \) -exec clang-format -i {} \;
	
clang_check:
	cp ../materials/linters/.clang-format .
	find . \( -name '*.c' -o -name '*.h' \) -exec clang-format -n {} \;

valgrind: test 
	valgrind --tool=memcheck --leak-check=yes ./s21_tests.out

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem .

clean: 
	rm -rf $(OBJ_DIR) $(CFOLD) html
	rm -f main.out s21_tests.out s21_matrix_oop_cov.a s21_matrix_oop.a s21_matrix_oop_tests_cov *.gcda *.gcno coverage.info