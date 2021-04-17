// https://www.luogu.com.cn/problem/P3791
// 普通数学题

#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
unordered_map<int64_t, int64_t> mp;
int64_t N, M, V;

int add(int64_t a, int64_t b) {
  return (a + b) % MOD;
}

int sub(int64_t a, int64_t b) {
  return (a + MOD - b) % MOD;
}

int mul(int64_t a, int64_t b) {
  return (a % MOD) * (b % MOD) % MOD;
}

int64_t calc_sd(int64_t n) {
  if (n < 0) return 0;
  if (mp.count(n)) return mp[n];
  int64_t ans = 0;
  for (int64_t l = 1, r; l <= n; l = r+1) {
    r = n / (n / l);
    ans = add(ans, mul(r-l+1, n/l));
  }
  return mp[n] = ans;
}

int64_t calc_ans(int64_t x, int64_t y, int lx, int ly) {
  if (lx < ly) {
    swap(x, y);
    swap(lx, ly);
  }
  int64_t prefix = (x ^ y ^ V) & (~((1LL << lx) - 1));
  int64_t val1 = calc_sd(prefix + (1LL << lx) - 1);
  int64_t val2 = calc_sd(prefix - 1);
  return mul(sub(val1, val2), 1LL << ly);
}

int main() {
  scanf("%ld%ld%ld", &N, &M, &V);
  N++; M++;
  int64_t ans = 0;
  for (int i = 0; i <= 50; i++) {
    if ((N >> i) & 1) {
      for (int j = 0; j <= 50; j++) {
        if ((M >> j) & 1) {
          ans = add(ans, calc_ans(N ^ (1LL << i), M ^ (1LL << j), i, j));
        }
      }
    }
  }
  printf("%ld\n", ans);
  return 0;
}
