// https://www.luogu.org/problem/show?pid=1641
// [SCOI2010]生成字符串

#include <bits/stdc++.h>
using namespace std;
typedef pair<int64_t, pair<int64_t, int64_t> > Tuple;

Tuple make_tuple(int64_t a, int64_t b, int64_t c) {
    return make_pair(a, make_pair(b, c));
}

void tie(int64_t& a, int64_t& b, int64_t& c, const Tuple& t) {
    a = t.first;
    b = t.second.first;
    c = t.second.second;
}

// (g, x, y) that a*x + b*y = g
Tuple ext_gcd(int64_t a, int64_t b) {
    if (b == 0) {
        return make_tuple(a, 1, 0);
    }
    int64_t dp, xp, yp;
    tie(dp, xp, yp, ext_gcd(b, a % b));
    return make_tuple(dp, yp, xp - a / b * yp);
}

// find x that a*x = b mod n
int64_t mod_solve(int64_t a, int64_t b, int n) {
    int64_t d, xp, yp;
    tie(d, xp, yp, ext_gcd(a, n));
    if (b % d == 0) {
        int64_t x0 = (xp * (b / d) % n + n) % n;
        return x0;
    } else {
        abort();
    }
}

const int64_t MOD = 20100403;

int64_t sub(int64_t a, int64_t b) {
    return (a + MOD - b) % MOD;
}

int64_t mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int64_t f(int n, int m) {
    int64_t ans = 1;
    for (int i = n; i >= n-m+1; i--) {
        ans = mul(ans, i);
    }
    for (int i = 1; i <= m; i++) {
        ans = mul(ans, mod_solve(i, 1, MOD));
    }
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    cout << sub(f(n+m, n), f(n+m, n+1)) << endl;
    return 0;
}
