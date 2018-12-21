// https://www.luogu.org/problemnew/show/P3306
// [SDOI2013]随机数生成器

#include <bits/stdc++.h>
using namespace std;

// return (a * b) mod n, dealing with possible overflow
int64_t mul_long(int64_t x, int64_t y, int64_t mod) {
    if (y < 0) {
        x = -x;
        y = -y;
    }
    int64_t s = 0, n = y, t = x;
    while (n) {
        if (n & 1) (s += t) %= mod;
        (t += t) %= mod;
        n >>= 1;
    }
    return s;
}


// (g, x, y) that a*x + b*y = g
void ext_gcd(int64_t a, int64_t b,
                    int64_t &g, int64_t &x, int64_t &y) {
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

int64_t gcd(int64_t a, int64_t b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

// find x that a*x = b mod n
int64_t mod_solve(int64_t a, int64_t b, int64_t n) {
    int64_t d, xp, yp;
    ext_gcd(a, n, d, xp, yp);
    if (b % d == 0) {
        int64_t x0 = (mul_long(xp, b/d, n) + n) % n;
        return x0;
    } else {
        //abort();
        return -1;
    }
}

int pow(int64_t x, int y, int m) {
    int64_t ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % m;
        x = x * x % m;
        y >>= 1;
    }
    return ans;
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
            if (pow(i, y, p) == 1) {
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

int sub(int64_t a, int64_t b, int64_t p) {
    return (a + p - b) % p;
}

int T;

int solve0(int b, int x1, int t) {
    if (x1 == t) return 1;
    if (b == t) return 2;
    return -1;
}

int solve1(int p, int b, int x1, int t) {
    if (t != x1 && b == 0) return -1;
    int x = sub(t, x1, p);
    int64_t invb = mod_solve(b, 1, p);
    return (invb * x) % p + 1;
}

int solve2(int64_t p, int64_t a, int64_t b, int64_t x1, int64_t t) {
    int64_t inv1 = mod_solve(a-1, 1, p);
    int64_t dem = (x1 + b*inv1) % p;
    int64_t nom = (t + b*inv1) % p;
    if (dem == 0 && nom == 0) return 1;
    if (dem == 0 || nom == 0) return -1;
    int64_t inv2 = mod_solve(dem, 1, p);
    int64_t rhs = (nom * inv2) % p;
    int alpha = primeRoot(p);
    int l = babystepGiantstep(alpha, a, p);
    int r = babystepGiantstep(alpha, rhs, p);
    int64_t x = mod_solve(l, r, p-1);
    if (x == -1) return -1;
    x = x % ((p-1)/gcd(l, p-1));
    return x + 1;
}

int solve() {
    int p, a, b, X1, t;
    scanf("%d%d%d%d%d", &p, &a, &b, &X1, &t);
    if (a == 0) return solve0(b, X1, t);
    else if (a == 1) return solve1(p, b, X1, t);
    return solve2(p, a, b, X1, t);
}

int main() {
    scanf("%d", &T);
    while (T--) {
        int ans = solve();
        printf("%d\n", ans);
    }
    return 0;
}
