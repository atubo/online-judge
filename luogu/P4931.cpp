// https://www.luogu.com.cn/problem/P4931
// [MtOI2018]情侣？给我烧了！（加强版）

#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 5000010;
int F[MAXN];
int FC[MAXN], FI[MAXN];
int P[MAXN];
int INV[MAXN];

int mul(int64_t a, int64_t b) {
  return (a * b) % MOD;
}

int add(int64_t a, int64_t b) {
  return (a + b) % MOD;
}

void init() {
  F[0] = 1;
  F[1] = 0;
  for (int i = 2; i < MAXN; i++) {
    F[i] = mul(mul(2*i, 2*i-2), add(F[i-1], mul(2*i-2, F[i-2])));
  }
  P[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    P[i] = (P[i-1] * 2) % MOD;
  }

  INV[1] = 1;
  for (int i = 2; i < MAXN; i++) {
    INV[i] = mul(MOD - MOD/i, INV[MOD%i]);
  }

  FC[0] = 1, FI[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    FC[i] = mul(FC[i-1], i);
    FI[i] = mul(FI[i-1], INV[i]);
  }
}

int main() {
  init();
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, k;
    scanf("%d%d", &n, &k);
    int ans = mul(P[k], F[n-k]);
    ans = mul(mul(FC[n], FC[n]), ans);
    ans = mul(ans, FI[k]);
    ans = mul(ans, mul(FI[n-k], FI[n-k]));
    printf("%d\n", ans);
  }

  return 0;
}
