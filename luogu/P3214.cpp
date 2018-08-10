// https://www.luogu.org/problemnew/show/P3214
// [HNOI2011]卡农

#include <bits/stdc++.h>
using namespace std;

const int MOD = 100000007;

int64_t qpow(int64_t a, int64_t b) {
    int64_t res = 1;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

int64_t sub(int64_t a, int64_t b) {
    return (a + MOD - b) % MOD;
}

int64_t mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
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

const int MAXN = 1000010;
int N, M;
int64_t dp[MAXN];

int main() {
    scanf("%d%d", &N, &M);
    int64_t p2 = qpow(2, N);
    int64_t n2 = (p2 + MOD -1 ) % MOD;
    dp[0] = 1;
    int64_t a = n2;
    int64_t inv = 1;
    for (int i = 2; i <= M; i++) {
        dp[i] = sub(a, dp[i-1]);
        int64_t t = mul(mul(dp[i-2], i-1), sub(n2, i-2));
        dp[i] = sub(dp[i], t);
        a = mul(a, n2-i+1);
        inv = mul(inv, i);
    }
    inv = mod_solve(inv, 1, MOD);
    printf("%ld\n", mul(dp[M], inv));

    return 0;
}
