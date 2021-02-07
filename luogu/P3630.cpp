// https://www.luogu.com.cn/problem/P3630
// [APIO2010]信号覆盖

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1510;
int N;
struct Point {
  int x, y;
} P[MAXN];

int64_t solve(int u) {
  vector<double> a(N), b;
  for (int i = 0; i < N; i++) {
    if (i == u) continue;
    double dx = P[i].x - P[u].x;
    double dy = P[i].y - P[u].y;
    a[i] = atan2(dy, dx);
    b.push_back(a[i]);
  }
  sort(b.begin(), b.end());
  int64_t ans = 0;
  for (int v = 0; v < N; v++) {
    if (v == u) continue;
    double t = a[v];
    int m = 0;
    if (t <= 0) {
      m = upper_bound(b.begin(), b.end(),M_PI+t)
          - upper_bound(b.begin(), b.end(), t);
    } else {
      m = b.end() - upper_bound(b.begin(), b.end(), t)
          + upper_bound(b.begin(), b.end(), -M_PI+t) - b.begin();
    }
    ans += m * (m-1) / 2;
  }
  ans = 1LL*(N-1)*(N-2)*(N-3)/6 - ans;

  return ans;
}

int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    scanf("%d%d", &P[i].x, &P[i].y);
  }
  int64_t k = 0;
  for (int i = 0; i < N; i++) {
    k += solve(i);
  }
  double ans = 3;
  ans += double(1LL*N*(N-1)*(N-2)*(N-3)/12 - k) / (1LL*N*(N-1)*(N-2)/6);
  printf("%.6f\n", ans);
  return 0;
}
