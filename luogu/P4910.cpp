// https://www.luogu.com.cn/problem/P4910
// 帕秋莉的手环

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int mul(int64_t a, int64_t b) {
  return (a * b) % MOD;
}

int add(int64_t a, int64_t b) {
  return (a + b) % MOD;
}

// square matrix fast power
class Matrix {
 public:
  int **m_;
  int n_;

 public:
  Matrix(int n): n_(n) {
    alloc();
  }

  Matrix(const Matrix &other) {
    n_ = other.n_;
    alloc();
    for (int i = 0; i < n_; i++) {
      memcpy(m_[i], other.m_[i], n_ * sizeof(int));
    }
  }


  ~Matrix() {
    for (int i = 0; i < n_; i++) {
      delete[] m_[i];
    }
    delete[] m_;
  }

  static Matrix power(Matrix x, int64_t n) {
    Matrix ret(x.n_), tmp(x.n_);
    for (int i = 0; i < x.n_; i++) ret.m_[i][i] = 1;
    while (n) {
      if (n & 1) ret.mul(x, tmp);
      x.mul(x, tmp);
      n >>= 1;
    }
    return ret;
  }

  void print() const {
    for (int i = 0; i < n_; i++) {
      for (int j = 0; j < n_; j++) {
        printf("%d ", m_[i][j]);
      }
      printf("\n");
    }
  }

 private:
  void alloc() {
    m_ = new int*[n_]{};
    for (int i = 0; i < n_; i++) {
      m_[i] = new int[n_]{};
    }
  }

  void mul(const Matrix &rhs, Matrix &tmp) {
    for (int i = 0; i < n_; i++) {
      memset(tmp.m_[i], 0, n_ * sizeof(int));
      for (int k = 0; k < n_; k++) {
        if (!m_[i][k]) continue;
        for (int j = 0; j < n_; j++) {
          tmp.m_[i][j] = add(tmp.m_[i][j], ::mul(m_[i][k], rhs.m_[k][j]));
        }
      }
    }
    swap(tmp);
  }

  void swap(Matrix &other) {
    std::swap(m_, other.m_);
  }
};

int T;

int main() {
  scanf("%d", &T);
  Matrix m(2);
  m.m_[0][1] = m.m_[1][0] = m.m_[1][1] = 1;

  while (T--) {
    int64_t n;
    scanf("%ld", &n);
    auto res = Matrix::power(m, n-1);
    int ans = add(add(res.m_[0][1], res.m_[1][0]), res.m_[1][1]);
    printf("%d\n", ans);
  }

  return 0;
}
