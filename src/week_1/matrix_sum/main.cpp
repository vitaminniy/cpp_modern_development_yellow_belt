#include <iostream>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

class Matrix {
public:
  inline Matrix() { Reset(0, 0); }
  inline Matrix(int rows, int cols) { Reset(rows, cols); }

  void Reset(int rows, int cols);

  int At(int row, int col) const;
  int &At(int row, int col);

  inline int GetNumRows() const { return rows_; }
  inline int GetNumColumns() const { return cols_; }

  bool operator==(const Matrix &m) const;
  Matrix operator+(const Matrix &m) const;

private:
  friend std::ostream &operator<<(std::ostream &dst, const Matrix &m);
  friend std::istream &operator>>(std::istream &dst, Matrix &m);

  inline bool empty() const { return rows_ == 0 || cols_ == 0; }

  int rows_;
  int cols_;
  std::vector<std::vector<int>> matrix;
};

void Matrix::Reset(int rows, int cols) {
  if (rows < 0 || cols < 0)
    throw std::out_of_range("");

  rows_ = rows;
  cols_ = cols;

  matrix = std::vector<std::vector<int>>(rows);
  for (int i = 0; i < rows; i++)
    matrix[i] = std::vector<int>(cols);
}

int Matrix::At(int row, int col) const {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
    throw std::out_of_range("");

  return matrix[row][col];
}

int &Matrix::At(int row, int col) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
    throw std::out_of_range("");

  return matrix[row][col];
}

bool Matrix::operator==(const Matrix &m) const {
  if (empty() && m.empty())
    return true;

  if (rows_ != m.rows_ || cols_ != m.cols_)
    return false;

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix[i][j] != m.matrix[i][j])
        return false;
    }
  }
  return true;
}

Matrix Matrix::operator+(const Matrix &m) const {
  if (empty() && m.empty())
    return Matrix();

  if (rows_ != m.rows_ || cols_ != m.cols_)
    throw std::invalid_argument("");

  Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix[i][j] = matrix[i][j] + m.matrix[i][j];
    }
  }

  return result;
}

std::ostream &operator<<(std::ostream &dst, const Matrix &m) {
  dst << m.rows_ << " " << m.cols_ << std::endl;
  for (const auto &col : m.matrix) {
    for (const auto v : col) {
      dst << v << " ";
    }
    dst << std::endl;
  }
  return dst;
}

std::istream &operator>>(std::istream &src, Matrix &m) {
  int rows, cols;
  src >> rows >> cols;
  m.Reset(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      src >> m.matrix[i][j];
    }
  }
  return src;
}

int main() {
  Matrix one;
  Matrix two;

  std::cin >> one >> two;
  std::cout << one + two << std::endl;

  return 0;
}
