// https://www.luogu.org/problem/P3989
// [SHOI2013]阶乘字符串

#include <bits/stdc++.h>
using namespace std;

int dp[1<<21];
int nxt[500][21];
int INF = 0x7F7F7F7F;

void buildNext(int n, const string& s) {
  memset(nxt, 0x7F, sizeof(nxt));
  int len = s.length();
  for (int i = len-1; i >= 0; i--) {
    for (int c = 0; c < n; c++) {
      nxt[i][c] = nxt[i+1][c];
      if (c == s[i] - 'a') nxt[i][c] = i;
    }
  }
}

void solve(int n, const string& str) {
  if (n > 21) {
    printf("NO\n");
    return;
  }
  memset(dp, 0, sizeof(dp));
  buildNext(n, str);
  dp[0] = -1;
  for (int s = 1; s < (1<<n); s++) {
    for (int i = 0; i < n; i++) {
      if ((s>>i) & 1) {
        int t = s ^ (1<<i);
        if (dp[t] == INF) {
          dp[s] = INF;
          break;
        }
        int x = nxt[dp[t]+1][i];
        dp[s] = max(dp[s], x);
      }
    }
  }
  if (dp[(1<<n)-1] == INF) {
    printf("NO\n");
  } else {
    printf("YES\n");
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    string s;
    cin >> n >> s;
    solve(n, s);
  }

  return 0;
}
