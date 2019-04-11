// https://www.luogu.org/problemnew/show/P2518
// [HAOI2010]计数

#include <bits/stdc++.h>
using namespace std;

class ChineseRemainder {
    // make sure m1*m2*.. fits in an integer
private:
    const int n_;
    int *m_;
    __int128_t *t_, *cap_m_;
    __int128_t m_prod_;
public:
    ChineseRemainder(const vector<int> &m): n_(m.size()) {
        alloc();
        copy(m.begin(), m.end(), m_);

        init();
    }

    ~ChineseRemainder() {
        dealloc();
    }

    __int128_t solve(const vector<int> &a) const {
        __int128_t ret = 0;
        for (int i = 0; i < n_; i++) {
            ret = add(ret, mul(mul(a[i], t_[i]), cap_m_[i]));
        }
        return ret;
    }

private:
    void alloc() {
        m_ = new int[n_]{};
        t_ = new __int128_t[n_]{};
        cap_m_ = new __int128_t[n_]{};
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
    void ext_gcd(__int128_t a, __int128_t b,
                 __int128_t &g, __int128_t &x, __int128_t &y) {
        if (b == 0) {
            g = a; x = 1; y = 0;
            return;
        }
        __int128_t dp, xp, yp;
        ext_gcd(b, a % b, dp, xp, yp);
        g = dp;
        x = yp;
        y = xp - a / b * yp;
    }

    // find x that a*x = b mod n
    __int128_t mod_solve(__int128_t a, __int128_t b, int n) {
        __int128_t d, xp, yp;
        ext_gcd(a, n, d, xp, yp);
        if (b % d == 0) {
            __int128_t x0 = (xp * (b / d) % n + n) % n;
            return x0;
        } else {
            abort();
        }
    }

    __int128_t add(__int128_t a, __int128_t b) const {
        return (a + b) % m_prod_;
    }

    __int128_t mul(__int128_t a, __int128_t b) const {
        return (a * b) % m_prod_;
    }
};

const int MAXN = 52;
const int MAXP = 65100;
int P[4] = {65003, 65011, 65027, 65029};
int N;
char S[MAXN];
int C[10];
int FAC[4][MAXN];
int INV[4][MAXP];

int64_t fac(int x) {
    int64_t res = 1;
    for (int i = 1; i <= x; i++) {
        res *= i;
    }
    return res;
}

void build() {
    for (int i = 0; i < 4; i++) {
        FAC[i][0] = 1;
        for (int j = 1; j < MAXN; j++) {
            FAC[i][j] = (1LL*FAC[i][j-1]*j) % P[i];
        }
    }

    for (int i = 0; i < 4; i++) {
        INV[i][1] = 1;
        for (int j = 2; j < P[i]; j++) {
            INV[i][j] =  (__int128_t(P[i]-P[i]/j) * INV[i][P[i]%j]) % P[i];
        }
    }
}


int64_t count(int idx) {
    int x = 0;
    for (int i = 0; i < 10; i++) x += C[i];
    int64_t res = FAC[idx][x];
    for (int i = 0; i < 10; i++) {
        res = (__int128_t(res) * INV[idx][FAC[idx][C[i]]]) % P[idx];
    }
    return res;
}

int main() {
    build();
    scanf("%s", S);
    N = strlen(S);
    for (int i = 0; i < N; i++) {
        C[S[i]-'0']++;
    }

    int64_t ans[4] = {0, 0, 0, 0};
    for (int i = 0; i < N; i++) {
        int c = S[i] - '0';
        for (int j = 0; j < c; j++) {
            if (C[j] == 0) continue;
            C[j]--;
            for (int k = 0; k < 4; k++) (ans[k] += count(k)) %= P[k];
            C[j]++;
        }
        C[c]--;
    }

    ChineseRemainder cr({P[0], P[1], P[2], P[3]});
    __int128_t res = cr.solve({int(ans[0]), int(ans[1]), int(ans[2]), int(ans[3])});
    cout << int64_t(res) << endl;

    return 0;
}
