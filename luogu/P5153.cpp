// https://www.luogu.com.cn/problem/P5153
// 简单的函数

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int F[50];
const int A[21] = {2, 3, 2, 5, 7, 2, 3, 11, 13, 2, 17, 19, 23, 5, 3, 29,
  31, 2, 37, 41, 43};
const int B[21] = {2, 3, 4, 5, 7, 8, 9, 11, 13, 16, 17, 19, 23, 25, 27, 29,
  31, 32, 37, 41, 43};

void init() {
  F[2] = 1;
  for (int i = 3; i < 50; i++) {
    for (int j = 2; j < i; j++) {
      if (i % j != 0) {
        F[i] = F[j] + 1;
        break;
      }
    }
  }
}

int qpow(int a, int64_t n) {
  int64_t ret = 1;
  while (n) {
    if (n & 1) ret = (ret * a) % MOD;
    a = (1LL * a * a) % MOD;
    n >>= 1;
  }
  return ret;
}

int64_t solve(int64_t n, int idx) {
  if (n == 0) return 1;
  int b = A[idx];
  int64_t n2 = n / b;
  int64_t n1 = (n-1) - n2;
  int64_t ret = qpow(F[B[idx]]+1, n1);
  if (n2 >= 1 && idx > 0) ret = (ret * (F[B[idx+1]]+1)) % MOD;
  return (ret * solve(n2, idx+1)) % MOD;
}

int main() {
  init();
  int64_t n;
  scanf("%ld", &n);
  printf("%ld\n", solve(n, 0));
  return 0;
}
