// https://www.luogu.com.cn/problem/P4351
// [CERC2015]Frightful Formula

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000003;

int add(int64_t a, int64_t b) {
  return (a + b) % MOD;
}

int sub(int64_t a, int64_t b) {
  return (a + MOD - b) % MOD;
}

int mul(int64_t a, int64_t b) {
  return (a * b) % MOD;
}

const int MAXN = 200010;
int N, A, B, C;
int L[MAXN];
int T[MAXN];
int C2[MAXN], PA[MAXN],PB[MAXN];
int INV[MOD];

void build() {
  INV[1] = 1;
  for (int i = 2; i < MOD; i++) {
    INV[i] = mul(MOD-MOD/i, INV[MOD%i]);
  }
  C2[0] = PA[0] = PB[0] = 1;
  for (int i = 1; i < N; i++) {
    C2[i] = mul(mul(C2[i-1], N-2+i), INV[i]);
    PA[i] = mul(PA[i-1], A);
    PB[i] = mul(PB[i-1], B);
  }
}

int solve() {
  int ans = 0;
  int curr = 1;
  int ab = add(A, B);
  for (int i = N-1; i >= 1; i--) {
    ans = add(ans, curr);
    curr = mul(curr, ab);
  }
  for (int i = N-1; i >= 2; i--) {
    curr = sub(curr, mul(C2[N-1-i], mul(PA[N-1], PB[N-1-i])));
    curr = sub(curr, mul(C2[N-1-i], mul(PA[N-1-i], PB[N-1])));
    ans = add(ans, curr);
    curr = mul(curr, ab);
  }
  return ans;
}

int main() {
  scanf("%d%d%d%d", &N, &A, &B, &C);
  for (int i = 0; i < N; i++) {
    scanf("%d", &L[i]);
  }
  for (int i = 0; i < N; i++) {
    scanf("%d", &T[i]);
  }
  build();
  int ans = 0;
  for (int i = 0; i <= N-2; i++) {
    ans = add(ans, mul(L[N-1-i], mul(mul(C2[i], PA[N-1]), PB[i])));
  }
  for (int i = 0; i <= N-2; i++) {
    ans = add(ans, mul(T[N-1-i], mul(mul(C2[i], PB[N-1]), PA[i])));
  }
  ans = add(ans, mul(C, solve()));
  printf("%d\n", ans);
  return 0;
}
