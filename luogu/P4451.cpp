// https://www.luogu.com.cn/problem/P4451
// [国家集训队]整数的lqp拆分

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;

int add(int64_t a, int64_t b) {
  return (a + b) % MOD;
}

int mul(int64_t a, int64_t b) {
  return (a * b) % MOD;
}

struct Matrix {
  int64_t a, b, c, d;
  Matrix operator * (const Matrix& other) const {
    Matrix ret;
    ret.a = add(mul(a, other.a), mul(b, other.c));
    ret.b = add(mul(a, other.b), mul(b, other.d));
    ret.c = add(mul(c, other.a), mul(d, other.c));
    ret.d = add(mul(c, other.b), mul(d, other.d));
    return ret;
  }

  Matrix& operator = (const Matrix& other) {
    a = other.a;
    b = other.b;
    c = other.c;
    d = other.d;
    return *this;
  }
}; 

Matrix qpow(const Matrix& m, int n) {
  Matrix ret{1, 0, 0, 1};
  Matrix x = m;
  while (n) {
    if (n&1) ret = ret * x;
    x = x * x;
    n >>= 1;
  }
  return ret;
}

int main() {
  int n;
  scanf("%d", &n);
  Matrix m{2, 1, 1, 0};
  Matrix ret = qpow(m, n-1);
  printf("%ld\n", ret.a);
  return 0;
}
