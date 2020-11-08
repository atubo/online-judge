// https://www.luogu.com.cn/problem/P5025
// [SNOI2017]炸弹

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500010;
const int MOD = 1e9+7;
int N;
int64_t X[MAXN], R[MAXN];
int LOG[MAXN];
struct Bomb {
  int x;
  int y;
} B[20][MAXN];
const int D = 19;
Bomb A[20][MAXN];

void init() {
  LOG[1] = 0;
  for (int i = 2; i <= N; i++) {
    LOG[i] = LOG[i/2] + 1;
  }
}

Bomb merge(const Bomb& a, const Bomb& b) {
  return Bomb{min(a.x, b.x), max(a.y, b.y)};
}

void build(Bomb *b) {
  for (int i = 0; i < N; i++) {
    A[0][i] = b[i];
  }
  for (int d = 1; d <= D; d++) {
    for (int i = 0; i < N; i++) {
      int j = i + (1 << (d-1));
      if (j < N) {
        A[d][i] = merge(A[d-1][i], A[d-1][j]);
      } else {
        A[d][i] = A[d-1][i];
      }
    }
  }
}

Bomb solve(int l, int r) {
  int d = LOG[r-l+1];
  return merge(A[d][l], A[d][r+1-(1<<d)]);
}

int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    scanf("%ld%ld", &X[i], &R[i]);
  }
  init();
  for (int i = 0; i < N; i++) {
    int x = lower_bound(X, X+N, X[i]-R[i]) - X;
    int y = upper_bound(X, X+N, X[i]+R[i]) - X - 1;
    B[0][i] = {x, y};
  }
  for (int d = 1; d <= D; d++) {
    build(B[d-1]);
    for (int i = 0; i < N; i++) {
      B[d][i] = solve(B[d-1][i].x, B[d-1][i].y);
    }
  }
  int64_t ans = 0;
  for (int i = 0; i < N; i++) {
    ans += 1LL * (i+1) * (B[D][i].y - B[D][i].x + 1);
  }
  printf("%ld", ans % MOD);
  return 0;
}
