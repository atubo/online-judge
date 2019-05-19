// https://www.luogu.org/problemnew/show/P4454
// [CQOI2018]破解D-H协议

#include <bits/stdc++.h>
using namespace std;

namespace discrete_logarithm {

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
        table[p] = j;
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
}

int G, P;
int N;
int A, B;

int qpow(int64_t n) {
    int ans = 1;
    int g = G;
    while (n) {
        if (n & 1) ans = (1LL * ans * g) % P;
        g = (1LL * g * g) % P;
        n >>= 1;
    }
    return ans;
}

int main() {
    using namespace discrete_logarithm;
    scanf("%d%d", &G, &P);
    scanf("%d", &N);
    while (N--) {
        scanf("%d%d", &A, &B);
        int a = babystepGiantstep(G, A, P);
        int b = babystepGiantstep(G, B, P);
        int ans = qpow(1LL*a*b);
        printf("%d\n", ans);
    }
    return 0;
}
