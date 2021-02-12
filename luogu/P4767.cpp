// https://www.luogu.com.cn/problem/P4767
// [IOI2000]邮局

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3F3F3F3F;
const int MAXV = 3005;
int dp[305][MAXV];
int V, P;
int A[MAXV], S[MAXV];

int eval(int k, int j, int l, int i) {
  return dp[k-1][j] + (V-i+1) * (A[j] - A[i]) + (i-l) * (A[i] + A[j])
      - 2 * (S[i-1] - S[l-1]);
}

int main() {
  memset(dp, 0x3F, sizeof(dp));
  scanf("%d%d", &V, &P);
  for (int i = 1; i <= V; i++) {
    scanf("%d", &A[i]);
    S[i] = S[i-1] + A[i];
  }
  for (int i = 1; i <= V; i++) {
    dp[1][i] = (i-1) * A[i] - S[i-1] + S[V] - S[i] - (V-i) * A[i];
  }

  for (int k = 2; k <= P; k++) {
    int last = 1;
    for (int i = k; i <= V; i++) {
      dp[k][i] = INF;
      int mpos = -1;
      int l = last + 1;
      for (int j = last; j < i; j++) {
        for (; l <= i; l++) {
          if (A[i] - A[l] <= A[l] - A[j]) {
            int t = eval(k, j, l, i);
            if (t < dp[k][i]) {
              mpos = j;
              dp[k][i] = t;
            }
            break;
          }
        }
      }
      last = mpos;
    }
  }

  int ans = INT_MAX;
  for (int i = P; i <= V; i++) {
    ans = min(ans, dp[P][i]);
  }
  printf("%d\n", ans);

  return 0;
}
