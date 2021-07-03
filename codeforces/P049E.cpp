// https://codeforces.com/problemset/problem/49/E
// Common ancestor

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 51;
int S[2][MAXN], S2[MAXN];
int N[2];
bool dp2[2][MAXN][MAXN][26];
int M;
struct Rule {
  int c, a, b;
} R[MAXN];
int dp[MAXN][MAXN];
const int INF = 0x3F3F3F3F;

void build2(int idx) {
  int n = N[idx];
  for (int i = 0; i < n; i++) {
    dp2[idx][i][i][S[idx][i]] = true;
  }
  for (int len = 2; len <= n; len++) {
    for (int i = 0; i < n - len + 1; i++) {
      for (int j = i+1; j <= i + len - 1; j++) {
        for (int k = 0; k < M; k++) {
          int c = R[k].c;
          int a = R[k].a;
          int b = R[k].b;
          dp2[idx][i][i+len-1][c] |=
              (dp2[idx][i][j-1][a] && dp2[idx][j][i+len-1][b]);
        }
      }
    }
  }
}

int solve(int i, int j) {
  if (dp[i][j] != -1) return  dp[i][j];
  for (int c = 0; c < 26; c++) {
    if (dp2[0][0][i][c] && dp2[1][0][j][c]) return dp[i][j] = 1;
  }
  int& ret = dp[i][j] = INF;
  for (int x = 0; x < i; x++) {
    for (int y = 0; y < j; y++) {
      for (int c = 0; c < 26; c++) {
        if (dp2[0][x+1][i][c] && dp2[1][y+1][j][c]) {
          ret = min(ret, solve(x, y) + 1);
        }
      }
    }
  }

  return ret;
}

int main() {
  memset(dp, -1, sizeof(dp));
  char s1[MAXN], s2[MAXN];
  scanf("%s%s", s1, s2);
  N[0] = strlen(s1);
  for (int i = 0; i < N[0]; i++) {
    S[0][i] = s1[i] - 'a';
  }
  N[1] = strlen(s2);
  for (int i = 0; i < N[1]; i++) {
    S[1][i] = s2[i] - 'a';
  }
  scanf("%d", &M);
  for (int i = 0; i < M; i++) {
    scanf("%s", s1);
    R[i].c = s1[0] - 'a';
    R[i].a = s1[3] - 'a';
    R[i].b = s1[4] - 'a';
  }
  build2(0);
  build2(1);
  int ret = solve(N[0]-1, N[1]-1);
  printf("%d\n", ret >= INF ? -1 : ret);
  return 0;
}
