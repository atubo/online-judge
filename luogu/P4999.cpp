// https://www.luogu.com.cn/problem/P4999
// 烦人的数学作业

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 20;
int A[MAXN], B[MAXN], C[MAXN], P[MAXN];

int add(int64_t a, int64_t b) {
  return (a + b) % MOD;
}

int sub(int64_t a, int64_t b) {
  return (a - b + MOD) % MOD;
}

int solve1(int i) {
  int x = A[i];
  if (i == 0) {
    return x * (x + 1) / 2;
  }

  int ans = (1LL * x * B[i-1]) % MOD;
  ans = add(ans, 1LL * x * (x - 1) / 2 * P[i]);
  (ans += add(1LL * x * (C[i-1] + 1) % MOD, solve1(i-1))) %= MOD;
  return ans;
}

void init() {
  P[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    P[i] = (10LL * P[i-1]) % MOD;
  }

  B[0] = 45;
  for (int i = 1; i < MAXN; i++) {
    B[i] = (45LL * P[i] + 10LL * B[i-1]) % MOD;
  }
}

void prep(int64_t x) {
  int64_t t = x;
  for (int i = 0; i < MAXN; i++) {
    A[i] = t % 10;
    t /= 10;
  }
  C[0] = A[0];
  for (int i = 1; i < MAXN; i++) {
    C[i] = ((1LL * A[i] * P[i]) % MOD + C[i-1]) % MOD;
  }
}

int solve2(int64_t x) {
  prep(x);
  for (int i = 0; i < MAXN; i++) {
    if (x < 10) return solve1(i);
    x /= 10;
  }
  assert(0);
  return 0;
}

int solve(int64_t l, int64_t r) {
  int ans = sub(solve2(r), solve2(l-1));
  return ans;
}

int main() {
  init();
  int t;
  scanf("%d", &t);
  while (t--) {
    int64_t a, b;
    scanf("%ld%ld", &a, &b);
    printf("%d\n", solve(a, b));
  }

  return 0;
}
