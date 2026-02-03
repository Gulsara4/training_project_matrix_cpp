#include "s21_matrix_oop.h"
int S21Matrix::GetRows_() { return (*this).rows_; }
int S21Matrix::GetCols_() { return (*this).cols_; }
void S21Matrix::SetRows_(int rows) {
  if (rows <= 0) {
    throw std::invalid_argument(code[WR]);
  }
  S21Matrix copy(rows, cols_);
  int bord = 0;
  if (rows_ < rows) {
    bord = rows_;

  } else {
    bord = rows;  //уменьшенеи
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i < bord) {
        copy.matrix_[i][j] = matrix_[i][j];
      } else {
        copy.matrix_[i][j] = 0;
      }
    }
  }

  (*this).~S21Matrix();
  matrix_ = copy.matrix_;
  copy.matrix_ = nullptr;
  rows_ = rows;
}
void S21Matrix::SetCols_(int cols) {
  if (cols <= 0) {
    throw std::invalid_argument(code[WR]);
  }
  S21Matrix copy(rows_, cols);
  int bord = 0;
  if (cols_ < cols) {
    bord = cols_;

  } else {
    bord = cols;  //уменьшенеи
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols; j++) {
      if (j < bord) {
        copy.matrix_[i][j] = matrix_[i][j];
      } else if (i < cols) {
        copy.matrix_[i][j] = 0;
      }
    }
  }
  (*this).~S21Matrix();
  matrix_ = copy.matrix_;

  copy.matrix_ = nullptr;
  cols_ = cols;
}

void S21Matrix::Print() const {
  printf("\n");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << (matrix_[i][j]) << ' ';
    }
    std::cout << '\n';
  }
}
void S21Matrix::Set(double v, int i, int j) {
  if (!(0 <= i && i < rows_ && 0 <= j && j < cols_)) {
    throw std::range_error(code[IOOR]);
  }
  matrix_[i][j] = v;
}

S21Matrix::S21Matrix() : rows_(rows_1), cols_(cols_1) {
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
      // matrix_[i] = nullptr;
    }
    delete[] matrix_;
    // matrix_ = nullptr;
  }
}
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument(code[WR]);
  }
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  CorrectMatrix(1, &other);

  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}
S21Matrix::S21Matrix(S21Matrix&& other) {
  CorrectMatrix(1, &other);
  matrix_ = other.matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}
void S21Matrix::SumMatrix(const S21Matrix& other) {
  CorrectMatrix(2, this, &other);
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error(code[DIFF_DIM]);
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}
void S21Matrix::SubMatrix(const S21Matrix& other) {
  S21Matrix::CorrectMatrix(2, this, &other);
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error(code[DIFF_DIM]);
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}
void S21Matrix::MulNumber(const double num) {
  S21Matrix::CorrectMatrix(1, this);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}
void S21Matrix::MulMatrix(const S21Matrix& other) {
  S21Matrix::CorrectMatrix(2, this, &other);

  if (cols_ != other.rows_) {
    // throw std::logic_error(code[NOT_K]);
  }
  S21Matrix result = S21Matrix(rows_, other.cols_);
  int k = cols_;
  double pop = 0;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int z = 0; z < k; z++) {
        pop += matrix_[i][z] * other.matrix_[z][j];
      }
      result.matrix_[i][j] = pop;
      pop = 0;
    }
  }
  *this = result;
  result.~S21Matrix();
  result.matrix_ = nullptr;
}
S21Matrix S21Matrix::Transpose() {
  S21Matrix::CorrectMatrix(1, this);
  S21Matrix tmp = S21Matrix(cols_, rows_);
  for (int i = 0; i < cols_; ++i) {
    for (int j = 0; j < rows_; ++j) {
      tmp.matrix_[i][j] = matrix_[j][i];
    }
  }

  return tmp;
}
S21Matrix S21Matrix::Deletions(int a, int b) {
  int index_i = 0, index_j = 0;
  S21Matrix tmp = S21Matrix(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; ++i) {
    if (i == a) {
      continue;
    }
    for (int j = 0; j < cols_; ++j) {
      if (j == b) {
        continue;
      }
      tmp.matrix_[index_i][index_j] = matrix_[i][j];

      index_j++;
    }
    index_i++;
    index_j = 0;
  }
  return tmp;
}

double S21Matrix::Determinant2(const S21Matrix& A) {
  return A.matrix_[0][0] * A.matrix_[1][1] - A.matrix_[0][1] * A.matrix_[1][0];
}
double S21Matrix::Determinant3(const S21Matrix& A) {
  double res = 0, o1 = 0, o2 = 0, o3 = 0;

  o1 = A.matrix_[0][0] *
       (A.matrix_[1][1] * A.matrix_[2][2] - A.matrix_[1][2] * A.matrix_[2][1]);
  o2 = -A.matrix_[0][1] *
       (A.matrix_[1][0] * A.matrix_[2][2] - A.matrix_[1][2] * A.matrix_[2][0]);
  o3 = A.matrix_[0][2] *
       (A.matrix_[1][0] * A.matrix_[2][1] - A.matrix_[1][1] * A.matrix_[2][0]);
  res = o1 + o2 + o3;
  return res;
}
double S21Matrix::Determinant() {
  S21Matrix::CorrectMatrix(1, this);
  if (cols_ != rows_) {
    throw std::logic_error(code[NOT_SQ]);
  }
  double result = 0;

  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = Determinant2(*this);
  } else if (rows_ == 3) {
    result = Determinant3(*this);
  } else {
    for (int i = 0; i < rows_; i++) {
      S21Matrix mini_matr = Deletions(i, 0);
      double tmp = mini_matr.Determinant();
      result += matrix_[i][0] * tmp * pow(-1, i + 0);
    }
  }
  return result;
}
S21Matrix S21Matrix::CalcComplements() {
  S21Matrix::CorrectMatrix(1, this);
  if (cols_ != rows_) {
    throw std::logic_error(code[NOT_SQ]);
  }
  // double tmp = 0;
  S21Matrix result = S21Matrix(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = 1;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix mini_matr = Deletions(i, j);
      double tmp = mini_matr.Determinant();

      result.matrix_[i][j] = tmp * pow(-1, i + j);
    }
  }
  return result;
}
S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix::CorrectMatrix(1, this);
  double det = (*this).Determinant();
  if (det == 0) {
    throw std::logic_error(code[DET_0]);
  }
  S21Matrix result = S21Matrix(rows_, cols_);
  if (rows_ == 1 && cols_ == 1) {
    result.matrix_[0][0] = 1 / ((*this).matrix_[0][0]);
  } else {
    S21Matrix intermediate = (*this).CalcComplements();
    S21Matrix trans = intermediate.Transpose();
    trans.MulNumber(1 / det);

    result = trans;
  }
  return result;
}
bool S21Matrix::EqMatrix(const S21Matrix& other) {
  S21Matrix::CorrectMatrix(2, this, &other);
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error(code[DIFF_DIM]);
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= EPS) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::CorrectMatrix(int count, ...) {
  va_list args;
  va_start(args, count);
  for (int z = 0; z < count; z++) {
    S21Matrix* tmp = va_arg(args, S21Matrix*);

    if (tmp == nullptr) {
      va_end(args);
      throw std::invalid_argument(code[NULL_PTR]);

    } else if ((tmp->matrix_) == nullptr) {
      va_end(args);
      throw std::invalid_argument(code[NULL_PTR]);

    } else if (tmp->cols_ <= 0 || tmp->rows_ <= 0) {
      va_end(args);
      throw std::invalid_argument(code[WR]);
    } else {
      for (int i = 0; i < tmp->rows_; i++) {
        for (int j = 0; j < tmp->cols_; j++) {
          if (isinf((*tmp).matrix_[i][j]) == 1) {
            throw std::invalid_argument(code[INF]);
          }
        }
      }
    }
  }
  va_end(args);
}
