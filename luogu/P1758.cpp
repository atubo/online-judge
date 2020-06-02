// https://www.luogu.com.cn/problem/P1758
// [NOI2009]管道取珠

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1024523;

const int MAXN = 505;
int N, M;
char U[MAXN], L[MAXN];
int dp[2][MAXN][MAXN];

int main() {
  scanf("%d%d", &N, &M);
  scanf("%s%s", U+1, L+1);
  dp[0][0][0] = 1;
  for (int l = 0; l < N+M; l++) {
    int curr = l & 1;
    int next = curr ^ 1;
    memset(dp[next], 0, sizeof(dp[next]));
    for (int i = 0; i <= min(l, N); i++) {
      int u1 = i+1, l1 = l-i+1;
      for (int j = 0; j <= min(l, N); j++) {
        if (dp[curr][i][j] == 0) continue;
        int u2 = j+1, l2 = l-j+1;
        int x = dp[curr][i][j];
        if (u1 <= N && u2 <= N && U[u1] == U[u2]) {
          dp[next][i+1][j+1] += x;
          if (dp[next][i+1][j+1] >= MOD) {
            dp[next][i+1][j+1] -= MOD;
          }
        }
        if (u1 <= N && l2 <= M && U[u1] == L[l2]) {
          dp[next][i+1][j] += x;
          if (dp[next][i+1][j] >= MOD) {
            dp[next][i+1][j] -= MOD;
          }
        }
        if (l1 <= M && u2 <= N && L[l1] == U[u2]) {
          dp[next][i][j+1] += x;
          if (dp[next][i][j+1] >= MOD) {
            dp[next][i][j+1] -= MOD;
          }
        }
        if (l1 <= M && l2 <= M && L[l1] == L[l2]) {
          dp[next][i][j] += x;
          if (dp[next][i][j] >= MOD) {
            dp[next][i][j] -= MOD;
          }
        }
      }
    }
  }
  printf("%d\n", dp[(N+M)&1][N][N]);

  return 0;
}
