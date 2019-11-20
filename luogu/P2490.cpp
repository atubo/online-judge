// https://www.luogu.org/problem/P2490
// [SDOI2011]黑白棋

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 10010;
const int MAXK = 210;
int C[MAXN][MAXK];
int P2[15];

int add(int64_t a, int64_t b) {
  return (a + b) % MOD;
}

int sub(int64_t a, int64_t b) {
  return (a - b + MOD) % MOD;
}

int mul(int64_t a, int64_t b) {
  return (a * b) % MOD;
}

void build() {
  C[0][0] = 1;
  for (int i = 1; i < MAXN; i++) {
    C[i][0] = 1;
    for (int j = 1; j < MAXK; j++) {
      C[i][j] = add(C[i-1][j-1], C[i-1][j]);
    }
  }

  P2[0] = 1;
  for (int i = 1; i < 15; i++) {
    P2[i] = mul(P2[i-1], 2);
  }
}

int N, K, D;
int dp[MAXN][15];
int solve(int n, int l) {
  if (n < 2*K) return 0;
  if (l == -1) return C[n-K][K];
  if (dp[n][l] >= 0) return dp[n][l];
  int& ret = dp[n][l] = 0;
  int maxj = min((n-2*K)/(P2[l]*(D+1)), K/(D+1));
  for (int j = 0; j <= maxj; j++) {
    ret = add(ret, mul(C[K][j*(D+1)], solve(n-P2[l]*(D+1)*j, l-1)));
  }
  return ret;
}

int main() {
  memset(dp, -1, sizeof(dp));
  build();
  scanf("%d%d%d", &N, &K, &D);
  K /= 2;
  int ans;
  if (D >= K) {
    ans = sub(C[N][2*K], C[N-K][K]);
  } else {
    ans = sub(C[N][2*K], solve(N, 14));
  }
  printf("%d\n", ans);

  return 0;
}
