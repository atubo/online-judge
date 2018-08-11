// https://www.luogu.org/problemnew/show/P2485
// [SDOI2011]计算器

#include <bits/stdc++.h>
using namespace std;

int T, K;

int qpow(int64_t x, int n, int p) {
    int64_t ret = 1;
    while (n) {
        if (n & 1) ret = (ret * x) % p;
        x = (x * x) % p;
        n >>= 1;
    }
    return ret;
}

void solve1() {
    while (T--) {
        int y, z, p;
        scanf("%d%d%d", &y, &z, &p);
        printf("%d\n", qpow(y, z, p));
    }
}

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

void solve2() {
    while (T--) {
        int y, z, p;
        scanf("%d%d%d", &y, &z, &p);
        if (y % p == 0 && z % p != 0) {
            printf("Orz, I cannot find x!\n");
        } else {
            printf("%ld\n", mod_solve(y, z, p));
        }
    }
}

int primeRoot(int p) {
    vector<int> factors;
    int x = p - 1;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            factors.push_back((p-1)/i);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) factors.push_back((p-1)/x);

    for (int i = 2; ; i++) {
        bool ok = true;
        for (int y: factors) {
            if (qpow(i, y, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return i;
    }
    return -1;
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

int64_t gcd(int64_t a, int64_t b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void solve3() {
    while (T--) {
        int y, z, p;
        scanf("%d%d%d", &y, &z, &p);
        if (bool(y % p) != bool(z % p)) {
            printf("Orz, I cannot find x!\n");
        } else if (y % p == 0 && z % p == 0) {
            printf("1\n");
        } else {
            int root = primeRoot(p);
            int ly = babystepGiantstep(root, y, p);
            int lz = babystepGiantstep(root, z, p);
            const int n = p - 1;
            if (lz % n == 0) {
                printf("0\n");
            } else if (bool(ly % n) != bool(lz % n) ||
                lz % gcd(ly, n) != 0) {
                printf("Orz, I cannot find x!\n");
            } else {
                int g = gcd(ly, n);
                int x = mod_solve(ly/g, lz/g, n/g);
                printf("%d\n", x);
            }
        }
    }
}

int main() {
    scanf("%d%d", &T, &K);
    if (K == 1) solve1();
    else if (K == 2) solve2();
    else solve3();
    return 0;
}
