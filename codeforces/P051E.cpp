// https://codeforces.com/problemset/problem/51/E
// Pentagon

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 710;
int64_t dp[3][MAXN][MAXN];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    dp[0][a][b] = dp[0][b][a] = 1;
  }
  for (int l = 0; l < 2; l++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (dp[l][i][j]) {
          for (int k = 0; k < n; k++) {
            if (dp[0][j][k]) {
              dp[l+1][i][k] += dp[l][i][j];
            }
          }
        }
      }
    }
  }
  int64_t ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      for (int k = 0; k < n; k++) {
        if (dp[0][i][k] && dp[0][k][j] && dp[2][i][j]) {
          ans += dp[2][i][j] - dp[1][i][k] - dp[1][j][k];
          if (dp[0][i][j]) {
            ans -= dp[1][i][i] + dp[1][j][j] - 3;
          }
        }
      }
    }
  }
  cout << ans/5 << endl;
  return 0;
}
