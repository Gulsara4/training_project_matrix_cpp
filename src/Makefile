 FILES = s21_matrix.cpp s21_operators.cpp
HEADERS = s21_matrix_oop.h
GCC = gcc
CFLAGS = -std=c++17 -Wall -Werror -Wextra
STATIC_LIB = s21_matrix_oop.a
BINARY = s21_test
OS := $(shell uname -s)
OBJECTS = $(FILES:.cpp=.o)
NAME_TEST = tests/test_matrix_class.cpp tests/test_runner.cpp
GFLAGS=  -lgtest -lgtest_main -pthread
LFLAGS = -lm -lstdc++
ifeq ($(OS), Linux)
    LFLAGS += -lsubunit
endif

all: $(STATIC_LIB)

$(STATIC_LIB): $(OBJECTS)
	$(GCC) -c  $(CFLAGS) $(LFLAGS) $(FILES) 
	ar rc $@ $(OBJECTS)
	ranlib $@

%.o: %.cpp $(HEADERS)
	$(GCC) $(CFLAGS) -c $< -o $@

$(BINARY): $(STATIC_LIB) $(NAME_TEST)
	$(GCC) $(CFLAGS) $(NAME_TEST) $(STATIC_LIB) $(LFLAGS) -lgtest -lgtest_main -pthread -o $(BINARY)

test: $(BINARY)
	./$(BINARY)

clean:
	rm -rf out
	rm -rf *.o *.a $(BINARY) coverage.info report  *.h.gcov  *.h.gch *.dSYM *.gcno *.gcda *.h.gchn *.out *.info log.txt *.cpp.gcov *.gcov


cppcheck:
	cppcheck --enable=all $(FILES) $(HEADERS)

valgrind: $(BINARY)
	valgrind --leak-check=full ./$(BINARY) 2>log.txt

leaks: $(BINARY)
	leaks -atExit -- ./$(BINARY) | grep LEAK:
clang:
	cp ../materials/linters/.clang-format .
	clang-format -i tests/*.cpp $(FILES) $(HEADERS)

gcov_report:	
	g++  $(GFLAGS) $(LFLAGS) -fprofile-arcs -ftest-coverage -o $(BINARY) s21_matrix.cpp s21_operators.cpp tests/test_runner.cpp tests/test_matrix_class.cpp
	./$(BINARY)
	gcov s21_test-s21_matrix.cpp
	gcov s21_test-s21_operators.cpp
	gcov s21_test-test_matrix_class.cpp
	gcov s21_test-test_runner.cpp
	lcov --capture --directory . --output-file coverage.info --ignore-errors inconsistent
	lcov --remove coverage.info '*/usr/*' --output-file coverage.info
	genhtml coverage.info --output-directory out
	open out/index.html