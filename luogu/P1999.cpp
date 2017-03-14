// https://www.luogu.org/problem/show?pid=1999
// 高维正方体

#include <bits/stdc++.h>
using namespace std;

// (g, x, y) that a*x + b*y = g
tuple<int64_t, int64_t, int64_t> ext_gcd(int64_t a, int64_t b) {
    if (b == 0) {
        return make_tuple(a, 1, 0);
    }
    int64_t dp, xp, yp;
    tie(dp, xp, yp) = ext_gcd(b, a % b);
    return make_tuple(dp, yp, xp - a / b * yp);
}

// find x that a*x = b mod n
int64_t mod_solve(int64_t a, int64_t b, int n) {
    int64_t d, xp, yp;
    tie(d, xp, yp) = ext_gcd(a, n);
    if (b % d == 0) {
        int64_t x0 = (xp * (b / d) % n + n) % n;
        return x0;
    } else {
        abort();
    }
}

int64_t MOD = 1000000007;

int64_t mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int64_t powerOf2(int a) {
    if (a == 0) return 1;
    if (a == 1) return 2;
    int64_t y = powerOf2(a/2);
    int64_t ret = mul(y, y);
    if (a & 1) ret = mul(ret, 2);
    return ret;
}

int64_t inv(int a) {
    return mod_solve(a, 1, MOD);
}

int64_t solve(int a, int b) {
    if (a < b) return 0;

    int64_t ret = powerOf2(a-b);
    for (int i = a-b+1; i <= a; i++) {
        ret = mul(ret, i);
    }
    for (int i = 1; i <= b; i++) {
        ret = mul(ret, inv(i));
    }
    return ret;
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << solve(a, b) << endl;
    return 0;
}
