// https://www.luogu.com.cn/problem/P5074
// Eat the Trees

#include <bits/stdc++.h>
using namespace std;

int T, N, M, A[15][15];
int64_t dp[2][1<<13];

int64_t solve() {
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      scanf("%d", &A[i][j]);
    }
  }
  memset(dp, 0, sizeof(dp));
  int curr = 0, prev = 1;
  dp[prev][0] = 1;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      for (int s = 0; s < (1 << (M+1)); s++) {
        int left = (s >> j) & 1;
        int up = (s >> (j+1)) & 1;
        if (A[i][j] == 0) {
          if (!left && !up) dp[curr][s] += dp[prev][s];
          continue;
        }
        if (!left && !up) {
          int s2 = s & (~(3 << j));
          s2 |= 3 << j;
          dp[curr][s2] += dp[prev][s];
        } else if (left && up) {
          int s2 = s & (~(3 << j));
          dp[curr][s2] += dp[prev][s];
        } else {
          int s2 = s & (~(3 << j));
          int s3 = s2 | (1 << j);
          dp[curr][s3] += dp[prev][s];
          s3 = s2 | (2 << j);
          dp[curr][s3] += dp[prev][s];
        }
      }
      memset(dp[prev], 0, sizeof(dp[prev]));
      swap(curr, prev);
    }
    for (int s = 0; s < (1<<M); s++) {
      dp[curr][s<<1] = dp[prev][s];
    }
    memset(dp[prev], 0, sizeof(dp[prev]));
    swap(curr, prev);
  }
  return dp[prev][0];
}

int main() {
  scanf("%d", &T);
  while (T--) {
    printf("%ld\n", solve());
  }
  return 0;
}
