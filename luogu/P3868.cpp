// https://www.luogu.org/problemnew/show/P3868
// [TJOI2009]猜数字

#include <bits/stdc++.h>
using namespace std;

namespace math {

class ChineseRemainder {
    // make sure m1*m2*.. fits in an integer
private:
    const int n_;
    int *m_;
    int64_t *t_, *cap_m_;
public:
    int64_t m_prod_;
    ChineseRemainder(const vector<int> &m): n_(m.size()) {
        alloc();
        copy(m.begin(), m.end(), m_);

        init();
    }

    ~ChineseRemainder() {
        dealloc();
    }

    int64_t solve(const vector<int> &a) const {
        int64_t ret = 0;
        for (int i = 0; i < n_; i++) {
            ret = add(ret, mul(mul(a[i], t_[i]), cap_m_[i]));
        }
        return ret;
    }

private:
    void alloc() {
        m_ = new int[n_]{};
        t_ = new int64_t[n_]{};
        cap_m_ = new int64_t[n_]{};
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

    int64_t add(int64_t a, int64_t b) const {
        return (a + b) % m_prod_;
    }

    int64_t mul(__int128_t a, __int128_t b) const {
        return (a * b) % m_prod_;
    }
};

}
int K;
int A[12];

int main() {
    scanf("%d", &K);
    vector<int> B(K);
    int64_t maxa = 0;
    for (int i = 0; i < K; i++) {
        scanf("%d", &A[i]);
        maxa = max(maxa, (int64_t)A[i]);
    }
    for (int i = 0; i < K; i++) {
        scanf("%d", &B[i]);
    }
    math::ChineseRemainder cr(B);
    vector<int> a(K);
    for (int i = 0; i < K; i++) {
        a[i] = (A[i]%B[i]+B[i])%B[i];
    }
    int64_t ans = cr.solve(a) % cr.m_prod_;
    printf("%ld\n", ans);
    return 0;
}
