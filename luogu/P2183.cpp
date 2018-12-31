// https://www.luogu.org/problemnew/show/P2183
// [国家集训队]礼物

#include <bits/stdc++.h>
using namespace std;

class ExtendedLucas {
    using PII = pair<int, int>;
public:
    ExtendedLucas(int N, int M, int tot, int p): 
        N_(N), M_(M), tot_(tot), p_(p) {
        alloc();
    }

    ~ExtendedLucas() {
        dealloc();
    }

    void add(int p, int k) {
        r_[curr_] = qpow(p, k);
        auto up = cal(N_, p, k);
        auto d1 = cal(N_-M_, p, k);
        auto d2 = cal(M_, p, k);
        int kp = up.second - d1.second - d2.second;
        assert(kp >= 0);
        int &ans = c_[curr_] = 1;
        if (kp >= k) ans = 0;
        else {
            ans = 1LL * ans * up.first % r_[curr_];
            ans = 1LL * ans * inv(d1.first, r_[curr_]) % r_[curr_];
            ans = 1LL * ans * inv(d2.first, r_[curr_]) % r_[curr_];
            ans = 1LL * ans * qpow(p, kp) % r_[curr_];
        }
        curr_++;
    }

    int eval() {
        return chineseRemainder();
    }

private:

    void alloc() {
        m_ = new int[tot_]{};
        r_ = new int[tot_]{};
        c_ = new int[tot_]{};
    }

    void dealloc() {
        delete[] m_;
        delete[] r_;
        delete[] c_;
    }

    int N_, M_;
    int tot_;
    int *m_, *r_, *c_;
    int p_;
    int curr_ = 0;

    static int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a%b);
    }

    static int extgcd(int a, int b, int &x, int &y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        int d = extgcd(b, a%b, y, x);
        y -= a/b*x;
        return d;
    }

    static int inv(int q, int p) {
        assert(gcd(p, q) == 1);
        int x, y;
        extgcd(q, p, x, y);
        x = (x%p + p) % p;
        if (!x) x += p;
        return x;
    }

    static int qpow(int x, int k) {
        int ret = 1;
        while (k > 0) {
            if (k & 1) ret *= x;
            x = x*x;
            k >>= 1;
        }
        return ret;
    }

    static int qpow(int x, int k, int mod) {
        int ret = 1;
        while (k > 0) {
            if (k & 1) ret = 1LL * ret * x % mod;
            x = 1LL*x*x % mod;
            k >>= 1;
        }
        return ret;
    }

    // count the power of p in x!
    static int countPower(int x, int p) {
        if (x == 0) return 0;
        return countPower(x/p, p) + x/p;
    }

    /** calculate x! % (p^k) where p is a prime
     *  @return: pair(remainder, power of p in x!)
     */
    PII cal(int x, int p, int k) {
        if (x == 1 || x == 0) return {1, 0};
        int tmp = qpow(p, k);
        int cnt = countPower(x, p);
        PII nw = cal(x/p, p, k);
        int ret = nw.first % tmp;
        if (x >= tmp) {
            int lev = 1;
            for (int i = 1; i < tmp; i++) {
                if (i%p == 0) continue;
                lev = 1LL * lev * i % tmp;
            }
            ret = 1LL * ret * qpow(lev, x/tmp, tmp) % tmp;
        }
        for (int i = x; i >= 1; i--) {
            if (i%tmp == 0) break;
            if (i%p == 0) continue;
            ret = 1LL * ret * i % tmp;
        }
        return {ret, cnt};
    }

    int chineseRemainder() {
        for (int i = 0; i < tot_; i++) {
            m_[i] = 1;
        }
        for (int i = 0; i < tot_; i++) {
            for (int j = 0; j < tot_; j++) {
                if (i == j) continue;
                m_[i] = 1LL * m_[i] * r_[j] % p_;
            }
        }
        int ret = 0;
        for (int i = 0 ; i < tot_; i++) {
            ret = (ret + ((1LL*c_[i]*m_[i]%p_) * 1LL * inv(m_[i], r_[i])) % p_)
                % p_;
        }
        return ret;
    }
};

int P;
int N, M;
int W[6];

int solve() {
    int tot = 0;
    for (int i = 0; i < M; i++) tot += W[i];
    if (tot > N) return -1;

    int q = P;
    vector<pair<int, int>> fac;
    for (int p = 2; p <= 100000; p++) {
        if (q % p == 0) {
            int pw = 0;
            while (q % p == 0) {
                pw ++;
                q /= p;
            }
            fac.push_back({p, pw});
        }
    }

    int ret = 1;
    for (int i = 0; i < M; i++) {
        ExtendedLucas extlucas(N, W[i], fac.size(), P);
        for (auto pk: fac) {
            extlucas.add(pk.first, pk.second);
        }
        ret = 1LL * ret * extlucas.eval() % P;
        N -= W[i];
    }

    return ret;
}

int main() {
    scanf("%d", &P);
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &W[i]);
    }
    int ans = solve();
    if (ans < 0) printf("Impossible\n");
    else printf("%d\n", ans);
    return 0;
}
