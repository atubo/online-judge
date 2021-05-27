// https://codeforces.com/problemset/problem/37/D
// Lesson Timetable

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
int C[1010][1010];
int dp[110][1010];

void build(int n) {
  C[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
    }
  }
}

int add(int64_t a, int64_t b) {
  return (a + b) % MOD;
}

int mul(int64_t a, int64_t b) {
  return (a * b) % MOD;
}

int M;
int X[110], Y[110], Z[110];

int solve(int i, int k) {
  if (dp[i][k] != -1) return dp[i][k];
  int& ans = dp[i][k] = 0;
  if (i == M-1) return ans = 1;
  for (int j = max(0, k-Z[i+1]); j <= min(Y[i], k); j++) {
    ans = add(ans, mul(C[k][j], solve(i+1, X[i+1]+k-j)));
  }
  return ans;
}

int main() {
  scanf("%d", &M);
  int tot = 0;
  for (int i = 0; i < M; i++) {
    scanf("%d", &X[i]);
    tot += X[i];
  }
  for (int i = 0; i < M; i++) {
    scanf("%d", &Y[i]);
  }
  build(tot);
  for (int i = M-1; i >= 0; i--) {
    Z[i] = Z[i+1] + Y[i] - X[i];
  }
  memset(dp, -1, sizeof(dp));
  solve(0, X[0]);
  int ans = dp[0][X[0]];
  int fac = 1;
  for (int i = 0, t = tot; i < M; i++) {
    fac = mul(fac, C[t][X[i]]);
    t -= X[i];
  }
  ans = mul(ans, fac);

  printf("%d\n", ans);
  return 0;
}
