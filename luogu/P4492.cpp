// https://www.luogu.org/problem/P4492
// [HAOI2018]苹果树

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2010;
int N, P;
int C[MAXN][MAXN];
int F[MAXN];

int add(int64_t a, int64_t b) {
  return (a + b) % P;
}

int mul(int64_t a, int64_t b) {
  return (a * b) % P;
}

void build() {
  C[0][0] = 1;
  for (int i = 1; i <= N; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      C[i][j] = add(C[i-1][j-1], C[i-1][j]);
    }
  }
  F[0] = 1;
  for (int i = 1; i <= N; i++) {
    F[i] = mul(F[i-1], i);
  }
}

int main() {
  scanf("%d%d", &N, &P);
  build();

  int ret = 0;
  for (int i = 2; i <= N; i++) {
    for (int s = 1; s <= N-i+1; s++) {
      int64_t t = F[s];
      t = mul(t, C[N-i][s-1]);
      t = mul(t, s);
      t = mul(t, N-s);
      t = mul(t, F[N-s-1]);
      t = mul(t, i);
      t = mul(t, i-1);
      ret = add(ret, t);
    }
  }
  printf("%d\n", ret);
  return 0;
}
