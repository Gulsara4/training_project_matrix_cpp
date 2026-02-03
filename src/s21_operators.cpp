#include "s21_matrix_oop.h"
S21Matrix S21Matrix::operator+(S21Matrix& a) {
  S21Matrix tmp = S21Matrix(a);
  tmp.SumMatrix(a);

  return tmp;
}
S21Matrix S21Matrix::operator-(S21Matrix& a) {
  S21Matrix tmp = S21Matrix(a);
  tmp.SubMatrix(a);
  return tmp;
}

S21Matrix S21Matrix::operator*(S21Matrix a) {
  S21Matrix tmp = S21Matrix(*this);
  tmp.MulMatrix(a);
  return tmp;
}

S21Matrix S21Matrix::operator*(double num) {
  S21Matrix tmp = S21Matrix(*this);
  tmp.MulNumber(num);
  return tmp;
}
S21Matrix& S21Matrix::operator+=(S21Matrix a) {
  SumMatrix(a);
  return *this;
}
S21Matrix& S21Matrix::operator-=(S21Matrix a) {
  SubMatrix(a);
  return *this;
}
S21Matrix& S21Matrix::operator*=(S21Matrix a) {
  MulMatrix(a);
  return *this;
}
S21Matrix& S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}
bool S21Matrix::operator==(S21Matrix other) { return EqMatrix(other); }
double& S21Matrix::operator()(int i, int j) {
  if (!(0 <= i && i < rows_ && 0 <= j && j < cols_)) {
    throw std::range_error(code[IOOR]);
  }
  return matrix_[i][j];
}
void S21Matrix::operator=(S21Matrix& other) {
  // printf("akhlsdhl\n");
  if (this == &other) {
    return;
  }
  (*this).~S21Matrix();
  cols_ = other.cols_;
  rows_ = other.rows_;

  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}
void S21Matrix::operator=(S21Matrix&& other) {
  if (this == &other) {
    return;
  }
  (*this).~S21Matrix();
  cols_ = other.cols_;
  rows_ = other.rows_;

  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}
const double& S21Matrix::operator()(int i, int j) const {
  if (!(0 <= i && i < rows_ && 0 <= j && j < cols_)) {
    throw std::range_error(code[IOOR]);
  }
  return matrix_[i][j];
}