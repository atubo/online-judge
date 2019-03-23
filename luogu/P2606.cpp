// https://www.luogu.org/problemnew/show/P2606
// [ZJOI2010]排列计数

#include <bits/stdc++.h>
using namespace std;

class ModularUtils {
public:
    // return (a * b) mod n, dealing with possible overflow
    static int64_t mul_long(int64_t x, int64_t y, int64_t mod) {
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
    static void ext_gcd(int64_t a, int64_t b,
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

    // find x that a*x = b mod n
    static int64_t mod_solve(int64_t a, int64_t b, int64_t n) {
        int64_t d, xp, yp;
        ext_gcd(a, n, d, xp, yp);
        if (b % d == 0) {
            int64_t x0 = (mul_long(xp, b/d, n) + n) % n;
            return x0;
        } else {
            abort();
        }
    }

    static int64_t gcd(int64_t a, int64_t b) {
        if (b == 0) return a;
        return gcd(b, a%b);
    }
};

const int MAXN = 1e6+10;
int N, P;

int64_t fac[MAXN], invfac[MAXN], pwr[MAXN];

void build() {
    fac[0] = 1;
    invfac[0] = 1;
    pwr[0] = 0;
    for (int i = 1; i <= N; i++) {
        if ((i % P) != 0) {
            fac[i] = (fac[i-1]*i) % P;
            invfac[i] = ModularUtils::mod_solve(fac[i], 1, P);
            pwr[i] = pwr[i-1];
        } else {
            int x = i;
            int p = 0;
            while ((x % P) == 0) {
                p++;
                x /= P;
            }
            fac[i] = (fac[i-1] * x) % P;
            invfac[i] = ModularUtils::mod_solve(fac[i], 1, P);
            pwr[i] = pwr[i-1] + p;
        }
    }
}

int64_t binom(int n, int m) {
    if (n < P || pwr[n] == pwr[n-m] + pwr[m]) {
        return (((fac[n]*invfac[n-m]) % P) *invfac[m]) % P;
    }
    return 0;
}


int64_t f(int n) {
    if (n <= 1) return 1;
    int k = 31 - __builtin_clz(n);
    int left = (1<<(k-1)) - 1;
    if ((n >> (k-1)) & 1) {
        left += (1 << (k-1));
    } else {
        left += (n & ((1<<(k-1)) - 1)) + 1;
    }
    int64_t ret = (((binom(n-1, left) * f(left)) % P) * f(n-1-left)) % P;
    return ret;
}

int main() {
    scanf("%d%d", &N, &P);
    build();
    int64_t ans = f(N);
    printf("%ld\n", ans);
    return 0;
}
