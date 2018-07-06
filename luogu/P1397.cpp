// https://www.luogu.org/problemnew/show/P1397
// [NOI2013]矩阵游戏

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


const int64_t MOD = 1000000007;

int A, B, C, D;

void mod(const string &s, int64_t &np, int64_t &np1) {
    np = np1 = s[0] - '0';
    for (int i = 1; i < (int)s.length(); i++) {
        np = (np * 10 + s[i] - '0') % MOD;
        np1 = (np1 * 10 + s[i] - '0') % (MOD-1);
    }
}

int64_t mul(int64_t x, int64_t y) {
    return (x * y) % MOD;
}

int64_t add(int64_t x, int64_t y) {
    return (x + y) % MOD;
}

int64_t sub(int64_t x, int64_t y) {
    return (x + MOD - y) % MOD;
}

int64_t fast_power(int64_t x, int n) {
    if (n == 0) return 1;
    int64_t y = fast_power(x, n/2);
    y = (y * y) % MOD;
    if (n & 1) y = (y * x) % MOD;
    return y;
}

int main() {
    string n_str, m_str;
    cin >> n_str >> m_str >> A >> B >> C >> D;
    int64_t mp, mp1;
    mod(m_str, mp, mp1);

    mp1 = (mp1 + MOD - 2) % (MOD-1);
    int64_t amp = fast_power(A, mp1);

    int64_t fac = mul(C, amp);
    int64_t term_m;
    if (A > 1) {
        int64_t ainv = mod_solve(A-1, 1, MOD);
        term_m = mul(sub(amp, 1), ainv);
        term_m = mul(term_m, B);
    } else {
        term_m = mul(sub(mp, 1), B);
    }
    int64_t term = mul(term_m, C);
    term = add(term, D);

    //printf("%lld %lld\n", fac, term);

    int64_t np, np1;
    mod(n_str, np, np1);
    np1 = (np1 + MOD - 2) % (MOD-1);
    int64_t fnp = fast_power(fac, np1);
    int64_t term_n;
    if (fac > 1) {
        int64_t finv = mod_solve(fac-1, 1, MOD);
        term_n = mul(sub(fnp, 1), finv);
        term_n = mul(term_n, term);
    } else {
        term_n = mul(sub(np, 1), term);
    }
    //printf("%lld %lld\n", fnp, term_n);

    int64_t ans = mul(amp, add(fnp, term_n));
    ans = add(ans, term_m);
    printf("%lld", ans);

    return 0;
}
