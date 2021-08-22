// https://codeforces.com/problemset/problem/53/E
// Dead Ends

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1 << 10;
int dp[MAXN][MAXN];
vector<int> g[15];
int cc[MAXN];

void init() {
  for (int i = 0; i < MAXN; i++) {
    cc[i] = __builtin_popcount(i);
  }
}

int main() {
  init();
  int n, m, K;
  scanf("%d%d%d", &n, &m, &K);
  for (int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    g[v].push_back(u);
    g[u].push_back(v);
  }
  int mx = (1 << n) - 1;
  for (int i = 1; i <= mx; i <<= 1) dp[i][i] = 1;
  for (int i = 1; i <= mx; i++) {
    for (int j = i; j; j--) {
      if (dp[i][j]) {
        for (int k = 0; k < n; k++) {
          if (i & (1 << k)) {
            for (int u : g[k]) {
              if (~ i & (1 << u)) {
                int v;
                if (cc[i] == 1) v = i | (1 << u);
                else v = (j & (~(1<<k))) | (1 << u);
                if (!(v >> u+1)) dp[i|(1<<u)][v] += dp[i][j];
              }
            }
          }
        }
      }
    }
  }

  int64_t ans = 0;
  for (int i = 0; i <= mx; i++) {
    if (cc[i] == K) {
      ans += dp[mx][i];
    }
  }
  cout << ans << endl;

  return 0;
}
