// https://www.luogu.org/problemnew/show/P3200
// [HNOI2009]有趣的数列

#include <bits/stdc++.h>
using namespace std;
using Pii = pair<int, int>;

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


int N, P;

vector<Pii> factor(int p) {
    vector<Pii> ret;
    int cnt = 0;
    while ((p & 1) == 0) {
        cnt++;
        p /= 2;
    }
    if (cnt > 0) ret.push_back(make_pair(2, cnt));
    for (int x = 3; x * x <= p; x += 2) {
        cnt = 0;
        while (p % x == 0) {
            cnt++;
            p /= x;
        }
        if (cnt > 0) ret.push_back(make_pair(x, cnt));
    }
    if (p > 1) ret.push_back(make_pair(p, 1));
    return ret;
}

int64_t inv(int x, int q) {
    return mod_solve(x, 1, q);
}

int64_t mul(int64_t a, int64_t b, int64_t m) {
    return (a * b) % m;
}

int modpk(int p, int k) {
    int cnt = 0;
    for (int i = 1; i <= N; i++) {
        int x = i;
        while (x % p == 0) {
            cnt--;
            x /= p;
        }
    }
    for (int i = N+2; i <= 2*N; i++) {
        int x= i;
        while (x % p == 0) {
            cnt++;
            x /= p;
        }
    }
    assert(cnt >= 0);
    if (cnt >= k) return 0;
    int q = 1;
    for (int i = 1; i <= k - cnt; i++) {
        q *= p;
    }

    int64_t ret = 1;
    for (int i = 1; i <= N; i++) {
        int x = i;
        while (x % p == 0) x /= p;
        ret = mul(ret, inv(x, q), q);
    }
    for (int i = N+2; i <= 2*N; i++) {
        int x = i;
        while (x % p == 0) x /= p;
        ret = mul(ret, x, q);
    }

    for (int i = 1; i <= cnt; i++) {
        ret *= p;
    }
    return ret;
}

int64_t chinese_remainder(const vector<Pii> &fa,
                          const vector<int> &rmd) {
    int64_t ans = 0;
    for (int i = 0; i < (int)fa.size(); i++) {
        int p, k;
        tie(p, k) = fa[i];
        int r = rmd[i];
        int mi = 1;
        for (int j = 1; j <= k; j++) {
            mi *= p;
        }
        int Mi = P/mi;
        int64_t ti = inv(Mi, mi);
        ans += r * ti * Mi;
    }
    return ans % P;
}


int main() {
    scanf("%d%d", &N, &P);
    vector<Pii> fa = factor(P);
    vector<int> rmd;
    for (auto pr: fa) {
        rmd.push_back(modpk(pr.first, pr.second));
    }
    printf("%lld\n", chinese_remainder(fa, rmd));
    return 0;
}
