// https://www.luogu.com.cn/problem/P4270
// [USACO18FEB]Cow Gymnasts P

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int qpow(int64_t x, int n) {
  int64_t ans = 1;
  x %= MOD;
  while (n) {
    if (n & 1) ans = (ans * x) % MOD;
      n >>= 1;
      x = (x * x) % MOD;
  }
  return ans;
}

vector<pair<int64_t, int>> factor;

void divide(int64_t n) {
  for (int i = 2; 1LL*i*i <= n; i++) {
    int cnt = 0;
    while (n == n/i*i) {
      n /= i;
      cnt++;
    }
    if (cnt) factor.push_back(make_pair(i, cnt));
  }
  if (n != 1) factor.push_back(make_pair(n, 1));
}

int64_t N, ans;
void dfs(int t, int64_t g, int64_t numer, int64_t denom) {
  if (t == (int)factor.size()) {
    if (g == 1) return;
    ans = (g / denom * numer % MOD * qpow(2, (N/g)%(MOD-1)) %MOD + ans) % MOD;
    return;
  }
  dfs(t+1, g, numer, denom);
  numer = numer * (factor[t].first - 1) % MOD;
  denom = denom * factor[t].first;
  for (int i = 1; i <= factor[t].second; i++) {
    g *= factor[t].first;
    dfs(t+1, g, numer, denom);
  }
}

int main() {
  scanf("%ld", &N);
  divide(N);
  dfs(0, 1, 1, 1);
  ans = ((ans + 2 - N) % MOD + MOD) % MOD;
  printf("%ld\n", ans);
  return 0;
}
