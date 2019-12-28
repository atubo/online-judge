// https://www.luogu.com.cn/problem/P2831
// 愤怒的小鸟

#include <bits/stdc++.h>
using namespace std;

const int INF = 100;
const double EPS = 1e-9;
const int MAXN = 18;
struct Point {
  double x, y;
  bool operator < (const Point& other) const {
    if (x != other.x) return x < other.x;
    return y < other.y;
  }
} P[MAXN];

int dp[1<<MAXN];

int solve(int mask) {
  if (mask == 0) return 0;
  if (dp[mask]) return dp[mask];
  int len = __builtin_popcount(mask);
  int d[len];
  int m = mask;
  int cnt = 0;
  while (m) {
    d[cnt++] = __builtin_ctz(m);
    m = m & (m-1);
  }
  assert(cnt == len);

  int& ret = dp[mask] = INF;
  for (int i = 0; i < cnt; i++) {
    ret = min(ret, 1 + solve(mask-(1<<d[i])));
    for (int j = i+1; j < cnt; j++) {
      double x1 = P[d[i]].x, y1 = P[d[i]].y;
      double x2 = P[d[j]].x, y2 = P[d[j]].y;
      if (x1 == x2) continue;
      if (y1*x2-y2*x1 <= 0) continue;
      double denom = x1*x2*(x1-x2);
      double a = (y1*x2-y2*x1)/denom;
      double b = (y2*x1*x1-y1*x2*x2)/denom;
      m = (1<<d[i]) | (1<<d[j]);
      for (int k = j+1; k < cnt; k++) {
        double x3 = P[d[k]].x, y3 = P[d[k]].y;
        if (fabs(a*x3*x3+b*x3-y3) < EPS) {
          m |= (1<<d[k]);
        }
      }
      ret = min(ret, 1 + solve(mask - m));
    }
  }
  return ret;
}

int T;
int N, M;

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
      scanf("%lf%lf", &P[i].x, &P[i].y);
    }
    sort(P, P+N);
    memset(dp, 0, (1<<N)*sizeof(int));
    printf("%d\n", solve((1<<N)-1));
  }

  return 0;
}
