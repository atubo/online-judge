// https://www.luogu.com.cn/problem/P3704
// [SDOI2017]数字表格

#include <bits/stdc++.h>
using namespace std;

// (g, x, y) that a*x + b*y = g
void ext_gcd(int64_t a, int64_t b, int64_t &g, int64_t &x, int64_t &y) {
    if (b == 0) {
        g = a; x = 1; y = 0;
        return;
    }
    int64_t dp, xp, yp;
    ext_gcd(b, a % b, dp, xp, yp);
    g = dp;
    x = yp;
    y = xp - a / b * yp;
}

// find x that a*x = b mod n
int64_t mod_solve(int64_t a, int64_t b, int n) {
    int64_t d, xp, yp;
    ext_gcd(a, n, d, xp, yp);
    if (b % d == 0) {
        int64_t x0 = (xp * (b / d) % n + n) % n;
        return x0;
    } else {
        abort();
    }
}

class EulerSieve {
 private:
 public:
  vector<bool> isPrime;
  vector<int> primes, mu;

  EulerSieve(int N) {
    assert(N > 1);

    isPrime.resize(N+1, true);
    mu.resize(N+1);

    isPrime[0] = isPrime[1] = false;
    mu[1] = 1;
    for (int i = 2; i <= N; i++) {
      if (isPrime[i]) {
        primes.push_back(i);
        mu[i] = -1;
      }

      for (int j = 0; j < (int)primes.size(); j++) {
        int64_t t = (int64_t)i * primes[j];
        if ( t > N) break;
        isPrime[t] = false;
        if (i % primes[j] == 0) {
          mu[t] = 0;
          break;
        } else {
          mu[t] = -mu[i];
        }
      }
    }
  }
};

const int MAXN = 1000010;
const int N = 1000000;
const int MOD = 1000000007;
int F[MAXN], FI[MAXN];
int G[MAXN];

int mul(int64_t a, int64_t b) {
  return (a * b) % MOD;
}

void init() {
  EulerSieve sieve(1000000);
  F[0] = 0;
  F[1] = 1;
  FI[1] = 1;
  for (int i = 2; i <= N; i++) {
    F[i] = (F[i-2] + F[i-1]) % MOD;
    FI[i] = mod_solve(F[i], 1, MOD);
  }
  for (int i = 0; i <= N; i++) G[i] = 1;
  for (int d = 1; d <= N; d++) {
    for (int i = 1; i*d <= N; i++) {
      assert(sieve.mu[i] == 0 || abs(sieve.mu[i]) == 1);
      if (sieve.mu[i] == 1) {
        G[i*d] = mul(G[i*d], F[d]);
      } else if (sieve.mu[i] == -1) {
        G[i*d] = mul(G[i*d], FI[d]);
      }
    }
  }
  for (int i = 1; i <= N; i++) {
    G[i] = mul(G[i], G[i-1]);
  }
}

int qpow(int64_t a, int64_t n) {
  int64_t ret = 1;
  while (n) {
    if (n & 1) ret = (ret * a) % MOD;
    a = (a * a) % MOD;
    n >>= 1;
  }
  return ret;
}

void solve(int n, int m) {
  int ans = 1;
  for (int l = 1, r; l <= n; l = r+1) {
    r = min(n/(n/l), m/(m/l));
    int t = G[r];
    t = mul(t, mod_solve(G[l-1], 1, MOD));
    t = qpow(t, 1LL*(n/l)*(m/l));
    ans = mul(ans, t);
  }
  printf("%d\n", ans);
}

int main() {
  init();
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, m;
    scanf("%d%d", &n, &m);
    if (n > m) swap(n, m);
    solve(n, m);
  }
  return 0;
}
