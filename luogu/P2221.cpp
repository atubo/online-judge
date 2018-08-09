// https://www.luogu.org/problemnew/show/P2221
// [HAOI2012]高速公路

#include <bits/stdc++.h>
using namespace std;

struct Data {
    int64_t s0, s1, s2;
};

int64_t sum1(int n) {
    return 1LL*n*(n+1) / 2;
}

int64_t sum2(int n) {
    return 1LL*n*(n+1)*(2*n+1) / 6;
}

// note it's 1-indexed
class SegmentTree {
    int N;
    int64_t *val0, *val1, *val2, *lazy;

public:
    SegmentTree(int N_): N(N_) {
        val0 = new int64_t[4*N]{};
        val1 = new int64_t[4*N]{};
        val2 = new int64_t[4*N]{};
        lazy = new int64_t[4*N]{};
    }

    ~SegmentTree() {
        delete[] val0;
        delete[] val1;
        delete[] val2;
        delete[] lazy;
    }
    // add t to range [a, b]
    void update(int t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    // query range sum in [a, b]
    Data query(int a, int b) {
        return query(1, a, b, 1, N);
    }

private:
    // add t to range [a, b], current node range is [l, r]
    void update(int k, int t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            val0[k] += int64_t(r - l + 1) * t;
            val1[k] += (sum1(r) - sum1(l-1)) * t;
            val2[k] += (sum2(r) - sum2(l-1)) * t;
            lazy[k] += t;
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        val0[k] = val0[2*k] + val0[2*k+1];
        val1[k] = val1[2*k] + val1[2*k+1];
        val2[k] = val2[2*k] + val2[2*k+1];
    }

    void pushDown(int k, int l, int r) {
        if (!lazy[k] || l == r) return;
        lazy[2*k] += lazy[k];
        lazy[2*k+1] += lazy[k];
        int mid = (l + r) / 2;
        val0[2*k] += int64_t(mid - l + 1) * lazy[k];
        val0[2*k+1] += int64_t(r - mid) * lazy[k];
        val1[2*k] += (sum1(mid) - sum1(l-1)) * lazy[k];
        val1[2*k+1] += (sum1(r) - sum1(mid)) * lazy[k];
        val2[2*k] += (sum2(mid) - sum2(l-1)) * lazy[k];
        val2[2*k+1] += (sum2(r) - sum2(mid)) * lazy[k];
        lazy[k] = 0;
    }

    // query range sum in [a, b], current node is [L, R]
    Data query(int k, int a, int b, int L, int R) {
        if (!k) return Data{0ll, 0ll, 0ll};
        if (b < L || a > R) return Data{0ll, 0ll, 0ll};
        pushDown(k, L, R);
        if (a <= L && R <= b) return Data{val0[k], val1[k], val2[k]};
        int64_t s0 = 0, s1 = 0, s2 = 0;
        int mid = (L + R) / 2;
        if (a <= mid) {
            auto ret = query(2*k, a, b, L, mid);
            s0 += ret.s0;
            s1 += ret.s1;
            s2 += ret.s2;
        }
        if (mid < b) {
            auto ret = query(2*k+1, a, b, mid+1, R);
            s0 += ret.s0;
            s1 += ret.s1;
            s2 += ret.s2;
        }
        return Data{s0, s1, s2};
    }
};

int64_t gcd(int64_t a, int64_t b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    SegmentTree st(N);
    char cmd[10];
    int l, r, v;
    for (int i = 0; i < M; i++) {
        scanf("%s", cmd);
        if (cmd[0] == 'C') {
            scanf("%d%d%d", &l, &r, &v);
            st.update(v, l, r-1);
        } else {
            scanf("%d%d", &l, &r);
            auto ret = st.query(l, r-1);
            int64_t s0 = ret.s0;
            int64_t s1 = ret.s1;
            int64_t s2 = ret.s2;
            int64_t p = s1 - (l-1) * s0;
            int64_t m = r - l + 1;
            int64_t t1 = p * m;
            int64_t t2 = s2 - s0 * l * (l-1)  - (l-1) * (2*p - s0);
            int64_t t = t1 - t2;
            int64_t d = m * (m-1) / 2;
            int64_t g = gcd(t, d);
            printf("%ld/%ld\n", t/g, d/g);
        }
    }

    return 0;
}
