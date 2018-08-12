// https://www.luogu.org/problemnew/show/P2480
// [SDOI2010]古代猪文

#include <bits/stdc++.h>
using namespace std;

class BinomModuloPrime {
    // n should be less than prime
private:
    const int n_;
    const int prime_;
    int *jc_;

public:
    BinomModuloPrime(int n, int prime): n_(n), prime_(prime) {
        alloc();
        init();
    }

    ~BinomModuloPrime() {
        dealloc();
    }

    int calc(int r) const {
        if (r > n_) return 0;
        int x1 = inverse(jc_[r]);
        int x2 = mul(jc_[n_], x1);
        int x3 = inverse(jc_[n_-r]);
        return mul(x2, x3);
    }

private:
    void alloc() {
        int sz = max(n_+1, 2);
        jc_ = new int[sz]{};
    }

    void dealloc() {
        delete[] jc_;
    }

    void init() {
        jc_[0] = jc_[1] = 1;
        for (int i = 2; i <= n_; i++) {
            jc_[i] = mul(jc_[i-1], i);
        }
    }

    int inverse(int x) const {
        return qpow(x, prime_-2);
    }

    int qpow(int x, int n) const {
        int ret = 1;
        while (n) {
            if (n & 1) ret = mul(ret, x);
            x = mul(x, x);
            n >>= 1;
        }
        return ret;
    }

    int mul(int64_t a, int64_t b) const {
        return (a * b) % prime_;
    }
};

class BinomLucas {
private:
    const int prime_;
public:
    BinomLucas(int prime): prime_(prime) {}

    int lucas(int64_t a, int64_t b) const {
        if (a < prime_ && b < prime_) return calc(a, b);
        return mul(calc(a % prime_, b % prime_),
                   lucas(a / prime_, b / prime_));
    }

    int calc(int a, int b) const {
        BinomModuloPrime binom(a, prime_);
        return binom.calc(b);
    }

private:
    int mul(int64_t a, int64_t b) const {
        return (a * b) % prime_;
    }
};

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

int add(int64_t a, int64_t b, int p) {
    return (a + b) % p;
}

int mul(int64_t a, int64_t b, int p) {
    return (a * b) % p;
}

const int MOD = 999911659;
int N, G;

int qpow(int64_t x, int n) {
    int64_t ret = 1;
    while (n) {
        if (n & 1) ret = mul(ret, x, MOD);
        x = mul(x, x, MOD);
        n >>= 1;
    }
    return ret;
}

int binomSum(int n, int p) {
    int ans = 0;
    BinomLucas lucas(p);
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            ans = add(ans, lucas.lucas(n, n/i), p);
            if (i * i != n) {
                ans = add(ans, lucas.lucas(n, i), p);
            }
        }
    }
    return ans;
}


int main() {
    scanf("%d%d", &N, &G);
    vector<int> primes{2, 3, 4679, 35617};
    ChineseRemainder cr(primes);
    vector<int> rem(4);
    for (int i = 0; i < 4; i++) {
        int x = binomSum(N, primes[i]);
        rem[i] = x;
    }
    int exp = cr.solve(rem);
    if (G % MOD == 0) {
        printf("0\n");
    } else {
        printf("%d\n", qpow(G, exp));
    }
    return 0;
}
