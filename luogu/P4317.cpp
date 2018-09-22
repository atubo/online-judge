// https://www.luogu.org/problemnew/show/P4317
// 花神的数论题

#include <bits/stdc++.h>
using namespace std;

namespace math {

class ChineseRemainder {
    // make sure m1*m2*.. fits in an integer
private:
    const int n_;
    int *m_, *t_, *cap_m_;
    int m_prod_;
public:
    ChineseRemainder(const vector<int> &m): n_(m.size()) {
        alloc();
        copy(m.begin(), m.end(), m_);

        init();
    }

    ~ChineseRemainder() {
        dealloc();
    }

    int solve(const vector<int> &a) const {
        int ret = 0;
        for (int i = 0; i < n_; i++) {
            ret = add(ret, mul(mul(a[i], t_[i]), cap_m_[i]));
        }
        return ret;
    }

private:
    void alloc() {
        m_ = new int[n_]{};
        t_ = new int[n_]{};
        cap_m_ = new int[n_]{};
    }

    void dealloc() {
        delete[] m_;
        delete[] t_;
        delete[] cap_m_;
    }

    void init() {
        m_prod_ = 1;
        for (int i = 0; i < n_; i++) {
            m_prod_ *= m_[i];
        }
        for (int i = 0; i < n_; i++) {
            cap_m_[i] = m_prod_ / m_[i];
            t_[i] = mod_solve(cap_m_[i], 1, m_[i]);
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

    int add(int64_t a, int64_t b) const {
        return (a + b) % m_prod_;
    }

    int mul(int64_t a, int64_t b) const {
        return (a * b) % m_prod_;
    }
};

}
const int MOD = 10000007;
const int P[2] = {941, 10627};
math::ChineseRemainder cm({941, 10627});

int add(int64_t a, int64_t b, int m) {
    return (a + b) % m;
}

int mul(int64_t a, int64_t b, int m) {
    return (a * b) % m;
}

int qpow(int x, int n, int m) {
    int ret = 1;
    while (n) {
        if (n & 1) ret = mul(ret, x, m);
        x = mul(x, x, m);
        n >>= 1;
    }
    return ret;
}

int C[2][65][65];

void init() {
    for (int pid = 0; pid < 2; pid++) {
        C[pid][0][0] = 1;
        for (int i = 1; i <= 64; i++) {
            C[pid][i][0] = 1;
            for (int j = 1; j <= i; j++) {
                C[pid][i][j] = add(C[pid][i-1][j], C[pid][i-1][j-1],
                                   P[pid]-1);
            }
        }
    }
}

int solve(int64_t n, int base, int pid) {
    int nd = 64 - __builtin_clzll(n);
    int ans = 1;
    for (int k = 1; k <= nd-1; k++) {
        ans = mul(ans, qpow(k+base, C[pid][nd-1][k], P[pid]), P[pid]);
    }
    ans = mul(ans, base+1, P[pid]);
    return ans;
}

int solve(int64_t n, int base) {
    vector<int> r(2);
    for (int pid = 0; pid < 2; pid++) {
        r[pid] = solve(n, base, pid);
    }
    return cm.solve(r);
}

int main() {
    init();
    int64_t n;
    scanf("%ld", &n);
    vector<int> r = {1, 1};
    int base = 0;
    while (n > 0) {
        for (int pid = 0; pid < 2; pid++) {
            r[pid] = mul(r[pid], solve(n, base, pid), P[pid]);
        }
        base++;
        n &= ~(1LL << (63 - __builtin_clzll(n)));
    }
    printf("%d", cm.solve(r));
    return 0;
}
