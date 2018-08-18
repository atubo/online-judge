// https://www.luogu.org/problemnew/show/P4774
// [NOI2018]屠龙勇士

#include <bits/stdc++.h>
using namespace std;

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

class ExtChineseRemainder {
private:
    int64_t b_ = 0, m_ = 1;
public:
    ExtChineseRemainder() {}

    bool add(int64_t b2, int64_t m2) {
        int64_t g, u, v;
        ModularUtils::ext_gcd(m_, m2, g, u, v);
        if (b_ % g != b2 % g) return false;
        int64_t lcm = m2 / g * m_;
        int64_t t1 = ModularUtils::mul_long(m2/g, b_, lcm);
        t1 = ModularUtils::mul_long(t1, v, lcm);
        int64_t t2 = ModularUtils::mul_long(m_/g, b2, lcm);
        t2 = ModularUtils::mul_long(t2, u, lcm);
        b_ = ((t1 + t2) % lcm + lcm) % lcm;
        m_ = lcm;
        return true;
    }

    int64_t get() const { return b_; }
    int64_t getM() const { return m_; }
};

class BIT {
public:
    // 1-indexed
    BIT(int size): N(size) {
        tree = (int64_t*)malloc((size+1) * sizeof(int64_t));
        clear();
    }

    ~BIT() {
        free(tree);
        tree = NULL;
    }

    void clear() {
        memset(tree, 0, (N+1) * sizeof(int64_t));
    }

    // add v to value at x
    void set(int x, int v) {
        while(x <= N) {
            tree[x] += v;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int64_t get(int x) const {
        int64_t res = 0;
        while(x) {
            res += tree[x];
            x -= (x & -x);
        }
        return res;
    }

    // get result for [x, y]
    int64_t get(int x, int y) const {
        return get(y) - (x > 1 ? get(x-1) : 0);
    }

    // index of first element with cumulative sum >= x
    int lowerBound(int64_t x) {
        int clz = __builtin_clz(N);
        int idx = 0, mask = 1 << (31 - clz);     // first power of 2 <= N
        while (mask) {
            int t = idx + mask;
            if (t <= N && x > tree[t]) {
                idx = t;
                x -= tree[t];
            }
            mask >>= 1;
        }
        return idx+1;
    }

    int upperBound(int64_t x) {
        int p = lowerBound(x);
        if (p <= N && get(p) == x) p = lowerBound(x+1);
        return p;
    }

private:
    int64_t* tree;
    const int N;
};


const int MAXN = 100010, MAXK = 1000010;
int T;
int N, M;
int64_t A[MAXN], P[MAXN], B[MAXN];

int main() {
    scanf("%d", &T);
    BIT ft(MAXK);
    while (T--) {
        scanf("%d%d", &N, &M);
        for (int i = 0; i < N; i++) {
            scanf("%ld", &A[i]);
        }
        for (int i = 0; i < N; i++) {
            scanf("%ld", &P[i]);
        }
        for (int i = 0; i < N; i++) {
            scanf("%ld", &B[i]);
        }
        for (int i = 0; i < M; i++) {
            int s;
            scanf("%d", &s);
            ft.set(s, 1);
        }

        ExtChineseRemainder ecr;
        bool failed = false;
        int64_t req = 0;
        for (int i = 0; i < N; i++) {
            int64_t x = ft.get(min(A[i], int64_t(MAXK)));
            int k;
            if (x == 0) k = ft.lowerBound(1);
            else k = ft.lowerBound(x);
            ft.set(k, -1);
            ft.set(B[i], 1);
            int64_t g = ModularUtils::gcd(k, P[i]);
            if (A[i] % g != 0) {
                failed = true;
                break;
            }
            int64_t r = ModularUtils::mod_solve(k/g, A[i]/g, P[i]/g);
            req = max(req, (A[i] + k - 1) / k);
            int64_t p = P[i]/g;
            bool ok = ecr.add(r, p);
            if (!ok) {
                failed = true;
                break;
            }
        }
        if (!failed) {
            int64_t ans = ecr.get();
            int64_t lcm = ecr.getM();
            int64_t q = (req - ans + lcm - 1) / lcm;
            ans += q * lcm;
            printf("%ld\n", ans);
        } else {
            printf("-1\n");
        }

        ft.clear();
    }

    return 0;
}
