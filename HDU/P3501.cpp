// http://acm.hdu.edu.cn/showproblem.php?pid=3501
// Calculation 2

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

const int64_t MOD = 1000000007;

int64_t mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int64_t phi(int64_t a) {
    int64_t ans = 1;
    for (int p = 2; p * p <= a; p++) {
        if (a % p == 0) {
            ans *= (p-1);
            a /= p;
            while (a % p == 0) {
                a /= p;
                ans *= p;
            }
        }
    }
    if (a > 1) ans *= (a-1);
    return ans;
}

int main() {
    int64_t a;
    while (true) {
        cin >> a;
        if (a == 0) break;
        if (a > 1) {
            cout << mul(mul((a-1-phi(a)) % MOD, a % MOD), mod_solve(2, 1, MOD))  << endl;
        } else {
            cout << 0 << endl;
        }
    }
    return 0;
}
