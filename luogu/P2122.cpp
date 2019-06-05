// https://www.luogu.org/problemnew/show/P2122
// 还教室

#include <bits/stdc++.h>
using namespace std;

// note it's 1-indexed
class SegmentTree {
    int N;
    int64_t *val, *lazy;
    int64_t *val2;

public:
    SegmentTree(int N_): N(N_) {
        val = new int64_t[4*N+1]{};
        lazy = new int64_t[4*N+1]{};
        val2 = new int64_t[4*N+1]{};
    }

    ~SegmentTree() {
        delete[] val;
        delete[] lazy;
        delete[] val2;
    }
    // add t to range [a, b]
    void update(int t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    // query range sum in [a, b]
    int64_t query(int a, int b) {
        return query(1, 1, N, a, b);
    }

    int64_t query2(int a, int b) {
        return query2(1, 1, N, a, b);
    }

private:
    // add t to range [a, b], current node range is [l, r]
    void update(int k, int t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            val2[k] += 2*t*val[k] + (r-l+1)*t*t;
            val[k] += t * (r-l+1);
            lazy[k] += t;
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        val[k] = val[2*k] + val[2*k+1];
        val2[k] = val2[2*k] + val2[2*k+1];
    }

    void pushDown(int k, int l, int r) {
        if (!lazy[k] || l == r) return;
        lazy[2*k] += lazy[k];
        lazy[2*k+1] += lazy[k];
        int mid = (l + r) / 2;
        int m1 = mid - l + 1;
        int m2 = r - mid;
        val2[2*k] += 2*lazy[k]*val[2*k] + m1*lazy[k]*lazy[k];
        val2[2*k+1] += 2*lazy[k]*val[2*k+1] + m2*lazy[k]*lazy[k];
        val[2*k] += m1 * lazy[k];
        val[2*k+1] += m2 * lazy[k];
        lazy[k] = 0;
    }

    // query range sum in [a, b], current node is [l, r]
    int64_t query(int k, int l, int r, int a, int b) {
        if (!k) return 0;
        if (b < l || a > r) return 0;
        pushDown(k, l, r);
        if (a <= l && r <= b) return val[k];
        int64_t sum = 0;
        int mid = (l + r) / 2;
        if (a <= mid) sum += query(2*k, l, mid, a, b);
        if (mid < b)  sum += query(2*k+1, mid+1, r, a, b);
        return sum;
    }

    int64_t query2(int k, int l, int r, int a, int b) {
        if (!k) return 0;
        if (b < l || a > r) return 0;
        pushDown(k, l, r);
        if (a <= l && r <= b) return val2[k];
        int64_t sum = 0;
        int mid = (l + r) / 2;
        if (a <= mid) sum += query2(2*k, l, mid, a, b);
        if (mid < b)  sum += query2(2*k+1, mid+1, r, a, b);
        return sum;
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
    for (int i = 1; i <= N; i++) {
        int a;
        scanf("%d", &a);
        st.update(a, i, i);
    }
    for (int i = 0; i < M; i++) {
        int op, l, r, d;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) {
            scanf("%d", &d);
            st.update(d, l, r);
        } else if (op == 2) {
            int s1 = st.query(l, r);
            int k = r - l + 1;
            if (s1 > 0) {
                int64_t g = gcd(s1, k);
                printf("%ld/%ld\n", s1/g, k/g);
            } else {
                printf("0/1\n");
            }
        } else {
            int k = r - l + 1;
            int64_t s2 = st.query2(l, r);
            int64_t s1 = st.query(l, r);
            int64_t num = 1LL*k*s2 - s1*s1;
            int64_t den = 1LL*k*k;
            if (num > 0) {
                int64_t g = gcd(num, den);
                printf("%ld/%ld\n", num/g, den/g);
            } else {
                printf("0/1\n");
            }
        }
    }

    return 0;
}
