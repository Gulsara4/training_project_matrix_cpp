#include <math.h>
//#include <stdarg.h>
//#include <stdexcept>
// #include "stdio.h"
#include <cstdarg>
#include <iostream>
#define EPS 0.0000001
#define n_test 3
#define m_test 3
#define rows_1 1
#define cols_1 1
enum MyStrings {
  DIFF_DIM,
  NOT_K,
  NOT_SQ,
  DET_0,
  IOOR,
  NULL_PTR,
  INF,
  WR,

};

constexpr const char* code[] = {
    "Различная размерность матриц",
    "Число столбцов 1-й матрицы != числу строк 2-й матрицы",
    "Матрица не квадратная",
    "Определитель матрицы == 0",
    "Индекс за пределами матрицы",
    "Указатель NULL",
    "Элемент матрицы равен бесконечности",
    "Неправильный порядок матрицы"

};
class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated

 public:
  int GetRows_();
  int GetCols_();
  void SetRows_(int rows);
  void SetCols_(int cols);
  S21Matrix();
  S21Matrix(int row_, int col_);
  S21Matrix(const S21Matrix& other);  // копирование
  S21Matrix(S21Matrix&& other);       //пенреноса
  ~S21Matrix();
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  S21Matrix Deletions(int index_i, int index_j);
  S21Matrix InverseMatrix();

  double Determinant2(const S21Matrix& other);
  double Determinant3(const S21Matrix& other);
  double Determinant();

  S21Matrix operator+(S21Matrix& a);
  S21Matrix operator-(S21Matrix& a);
  S21Matrix operator*(double num);
  S21Matrix operator*(S21Matrix a);
  S21Matrix& operator+=(S21Matrix a);
  S21Matrix& operator-=(S21Matrix a);
  S21Matrix& operator*=(double num);
  S21Matrix& operator*=(S21Matrix a);
  bool operator==(S21Matrix other);
  double& operator()(int i, int j);
  const double& operator()(int i, int j) const;
  void Print() const;
  void Set(double v, int i, int j);
  static void CorrectMatrix(int count, ...);
  double* operator[](int i) { return matrix_[i]; }
  const double* operator[](int i) const { return matrix_[i]; }

  void operator=(S21Matrix& other);
  void operator=(S21Matrix&& other);
};