// https://www.luogu.org/problem/show?pid=2054
// [AHOI2005]洗牌

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

int64_t powerOf2(int64_t x, int64_t n) {
    if (x == 0) return 1;
    if (x == 1) return 2;
    int64_t y = powerOf2(x/2, n);
    int64_t ret = (y * y) % n;
    if (x & 1) ret = (ret * 2) % n;
    return ret;
}

int main() {
    int64_t N, M, L;
    cin >> N >> M >> L;
    int64_t y = powerOf2(M, N+1);
    int64_t x = mod_solve(y, L, N+1);
    cout << x << endl;
    return 0;
}
