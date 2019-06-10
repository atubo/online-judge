// https://www.luogu.org/problemnew/show/P4588
// [TJOI2018]数学计算

#include <bits/stdc++.h>
using namespace std;

class EulerSieve {
private:
public:
    vector<bool> isPrime;
    vector<int> primes, mu, phi, sigma;

    EulerSieve(int N) {
        assert(N > 1);

        isPrime.resize(N+1, true);
        mu.resize(N+1);
        phi.resize(N+1);
        sigma.resize(N+1);

        // local variable to calculate sigma (divisor function)
        // i = pj^k * ..., and pi(i) = (1 + pj + pj^2 + ...)
        vector<int> pi(N+1);

        isPrime[0] = isPrime[1] = false;
        mu[1] = 1;
        phi[1] = 1;
        sigma[1] = 1;
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) {
                primes.push_back(i);
                mu[i] = -1;
                phi[i] = i - 1;
                sigma[i] = pi[i] = i + 1;
            }

            for (int j = 0; j < (int)primes.size(); j++) {
                int64_t t = (int64_t)i * primes[j];
                if ( t > N) break;
                isPrime[t] = false;
                if (i % primes[j] == 0) {
                    mu[t] = 0;
                    phi[t] = phi[i] * primes[j];
                    pi[t] = pi[i] * primes[j] + 1;
                    sigma[t] = sigma[i]/pi[i] * pi[t];
                    break;
                } else {
                    mu[t] = -mu[i];
                    phi[t] = phi[i] * (primes[j] - 1);
                    pi[t] = primes[j] + 1;
                    sigma[t] = sigma[primes[j]] * sigma[i];
                }
            }
        }
    }
};

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
int T;
int Q, MOD;

struct Factor {
    int p, k;
};

struct Remainder {
    int r, k;
};

int qpow(int x, int n) {
    int ret = 1;
    while (n) {
        if (n & 1) ret *= x;
        x *= x;
        n >>= 1;
    }
    return ret;
}


void solve(const EulerSieve &sieve) {
    vector<Factor> f;
    int m = MOD;
    for (int p: sieve.primes) {
        int cnt = 0;
        while (m % p == 0) {
            cnt++;
            m /= p;
        }
        if (cnt > 0) {
            f.push_back({p, cnt});
        }
    }
    if (m > 1) f.push_back({m, 1});

    vector<int> mc;
    vector<Remainder> rem;
    for (const auto &fa: f) {
       int x = qpow(fa.p, fa.k);
       mc.push_back(x);
       rem.push_back({1, 0});
    }

    math::ChineseRemainder crm(mc);

    vector<vector<Remainder>> queries;
    vector<int> ri(f.size());
    for (int i = 0; i < Q; i++) {
        int op, x;
        scanf("%d%d", &op, &x);
        int ret = 0;
        if (op == 1) {
            vector<Remainder> curr;
            for (int j = 0; j < (int)f.size(); j++) {
                const auto &fa = f[j];
                int t = x;
                int cnt = 0;
                while (t % fa.p == 0) {
                    t /= fa.p;
                    cnt++;
                }
                rem[j].r = (1LL * rem[j].r * t) % mc[j];
                rem[j].k += cnt;
                curr.push_back({t, cnt});
                if (rem[j].k >= f[j].k) ri[j] = 0;
                else {
                    ri[j] = (1LL * qpow(fa.p, rem[j].k) * rem[j].r) %
                        mc[j];
                }
            }
            queries.push_back(curr);
            ret = crm.solve(ri);
        } else {
            for (int j = 0; j < (int)f.size(); j++) {
                const auto &fa = queries[x-1][j];
                rem[j].k -= fa.k;
                rem[j].r = (1LL * rem[j].r *
                            ModularUtils::mod_solve(fa.r, 1, mc[j])) %
                    mc[j];
                if (rem[j].k >= f[j].k) ri[j] = 0;
                else {
                    ri[j] = (1LL * qpow(f[j].p, rem[j].k) * rem[j].r) %
                        mc[j];
                }
            }
            ret = crm.solve(ri);
            queries.push_back({});
        }
        printf("%d\n", ret);
    }
}
        
int main() {
    EulerSieve sieve(40000);
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &Q, &MOD);
        solve(sieve);
    }
    return 0;
}
