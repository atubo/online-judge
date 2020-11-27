// https://www.luogu.com.cn/problem/P4195
// 【模板】扩展BSGS

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

// returns x that alpha ^ x == beta mod prime
// alpha must be a primitive root
int babystepGiantstep(int alpha, int beta, int prime) {
    const int n = prime - 1;
    const int m = int(sqrt(n) + 1);
    unordered_map<int, int> table;
    int p = 1;
    for (int j = 0; j < m; j++) {
        if (table.find(p) == table.end()) {
          table[p] = j;
        }
        p = (1LL * p * alpha) % prime;
    }
    int fac = mod_solve(p, 1, prime);
    int gamma = beta;
    for (int i = 0; i < m; i++) {
        auto it = table.find(gamma);
        if (it != table.end()) {
            return (i * m + it->second) % n;
        }
        gamma = (1LL * gamma * fac) % prime;
    }
    return -1;
}

int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a%b);
}

int extBsgs(int a, int b, int p) {
  if (a == 0) return b == 0 ? 1 : -1;
  if (b == 1) return 0;
  int g = gcd(a, p);
  if (g == 1) return babystepGiantstep(a, b, p);
  if (b % g != 0) return -1;
  int t = mod_solve(a/g, 1, p/g);
  int x = extBsgs(a, 1LL * b/g * t % (p/g), p/g);
  return (x == -1 ? -1 : x + 1);
}

int main() {
  int a, p, b;
  while (true) {
    scanf("%d%d%d", &a, &p, &b);
    if (a == 0 && p == 0 && b == 0) break;
    int ans = extBsgs(a % p, b % p, p);
    if (ans != -1) printf("%d\n", ans);
    else printf("No Solution\n");
  }

  return 0;
}
