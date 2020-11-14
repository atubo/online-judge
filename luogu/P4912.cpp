// https://www.luogu.com.cn/problem/P4912
// 帕秋莉的魔法

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 51;
int N, M;
int A[MAXN], B[MAXN];
int W[MAXN][MAXN];
int dp[MAXN][MAXN][5010];
const int IMIN = 0x80808080;

int main() {
  memset(dp, 0x80, sizeof(dp));
  scanf("%d%d", &N, &M);
  int upper = 0, lower = 0;
  for (int i = 1; i <= N; i++) {
    scanf("%d%d", &A[i], &B[i]);
    if (A[i] > 0) upper += A[i];
    if (A[i] < 0) lower += A[i];
  }
  if (M > upper || M < lower) {
    printf("-1\n");
    return 0;
  }
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      int w;
      scanf("%d", &w);
      W[i][j] = w;
    }
  }
  const int offset = -lower;
  dp[0][0][offset] = 0;
  for (int i = 1; i <= N; i++) {
    for (int w = lower; w <= upper; w++) {
      for (int j = 0; j < i; j++) {
        dp[i][j][w+offset] = dp[i-1][j][w+offset];
      }
      int w2 = w - A[i];
      if (w2 >= lower && w2 <= upper) {
        for (int k = 0; k < i; k++) {
          if (dp[i-1][k][w2+offset] != IMIN) {
            dp[i][i][w+offset] = max(dp[i][i][w+offset],
                                     dp[i-1][k][w2+offset] + B[i] + W[k][i]);
          }
        }
      }
    }
  }
  int ans = IMIN;
  for (int k = 0; k <= N; k++) {
    ans = max(ans, dp[N][k][M+offset]);
  }
  printf("%d\n", ans == IMIN ? -1 : ans);
  return 0;
}
