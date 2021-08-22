// https://codeforces.com/problemset/problem/54/C
// First Digit Law

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
int64_t T[20];
double dp[MAXN][MAXN];

void init() {
  T[0] = 1;
  for (int i = 1; i < 20; i++) {
    T[i] = T[i-1] * 10;
  }
}

int64_t calc(int64_t x) {
  int64_t ret = 0;
  for (int i = 1; i < 20; i++) {
    if (x < T[i-1]) break;
    ret += min(T[i-1], x - T[i-1] + 1);
  }
  return ret;
}

int main() {
  init();
  int n;
  scanf("%d", &n);
  dp[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    int64_t l, r;
    cin >> l >> r;
    int64_t x = calc(r) - calc(l-1);
    double q = 1.0 * x / (r - l + 1);
    double p = 1 - q;
    dp[i][0] = p * dp[i-1][0];
    for (int j = 1; j <= n; j++) {
      dp[i][j] = p * dp[i-1][j] + q * dp[i-1][j-1];
    }
  }

  double ans = 0;
  int t;
  scanf("%d", &t);
  int k = (t*n + 99) / 100;
  for (int i = k; i <= n; i++) {
    ans += dp[n][i];
  }
  printf("%.15f\n", ans);

  return 0;
}
