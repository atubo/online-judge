// https://www.luogu.org/problemnew/show/P1471
// 方差

#include <bits/stdc++.h>
using namespace std;

// note it's 1-indexed
class SegmentTree {
    int N;
    double *val1, *val2, *lazy;

public:
    SegmentTree(int N_): N(N_) {
        val1 = new double[4*N+1]{};
        val2 = new double[4*N+1]{};
        lazy = new double[4*N+1]{};
    }

    ~SegmentTree() {
        delete[] val1;
        delete[] val2;
        delete[] lazy;
    }
    // add t to range [a, b]
    void update(double t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    // query range sum in [a, b]
    double query1(int a, int b) {
        return query1(1, 1, N, a, b);
    }

    double query2(int a, int b) {
        return query2(1, 1, N, a, b);
    }

    void build(double *a) {
        build(1, 1, N, a);
    }

private:
    // add t to range [a, b], current node range is [l, r]
    void update(int k, double t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            const int m = r - l + 1;
            val2[k] += 2*t*val1[k] + t*t*m;
            val1[k] += t * m;
            lazy[k] += t;
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        val1[k] = val1[2*k] + val1[2*k+1];
        val2[k] = val2[2*k] + val2[2*k+1];
    }

    void pushDown(int k, int l, int r) {
        if (lazy[k] == 0 || l == r) return;
        lazy[2*k] += lazy[k];
        lazy[2*k+1] += lazy[k];
        int mid = (l + r) / 2;
        int m1 = mid - l + 1;
        int m2 = r - mid;
        val2[2*k] += 2*lazy[k]*val1[2*k] + lazy[k]*lazy[k]*m1;
        val2[2*k+1] += 2*lazy[k]*val1[2*k+1] + lazy[k]*lazy[k]*m2;
        val1[2*k] += m1 * lazy[k];
        val1[2*k+1] += m2 * lazy[k];
        lazy[k] = 0;
    }

    // query range sum in [a, b], current node is [l, r]
    double query1(int k, int l, int r, int a, int b) {
        if (!k) return 0;
        if (b < l || a > r) return 0;
        pushDown(k, l, r);
        if (a <= l && r <= b) return val1[k];
        double sum = 0;
        int mid = (l + r) / 2;
        if (a <= mid) sum += query1(2*k, l, mid, a, b);
        if (mid < b)  sum += query1(2*k+1, mid+1, r, a, b);
        return sum;
    }

    double query2(int k, int l, int r, int a, int b) {
        if (!k) return 0;
        if (b < l || a > r) return 0;
        pushDown(k, l, r);
        if (a <= l && r <= b) return val2[k];
        double sum = 0;
        int mid = (l + r) / 2;
        if (a <= mid) sum += query2(2*k, l, mid, a, b);
        if (mid < b)  sum += query2(2*k+1, mid+1, r, a, b);
        return sum;
    }

    void build(int k, int l, int r, double *a) {
        if (l == r) {
            val1[k] = a[l];
            val2[k] = a[l]*a[l];
            return;
        }

        int mid = (l + r) / 2;
        build(2*k, l, mid, a);
        build(2*k+1, mid+1, r, a);
        val1[k] = val1[2*k] + val1[2*k+1];
        val2[k] = val2[2*k] + val2[2*k+1];
    }
};

const int MAXN = 100010;
int N, M;
double A[MAXN];

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%lf", &A[i]);
    }

    SegmentTree st(N);
    st.build(A);

    for (int i = 0; i < M; i++) {
        int t, x, y;
        double k;
        scanf("%d%d%d", &t, &x, &y);
        const int m = y - x + 1;
        if (t == 1) {
            scanf("%lf", &k);
            st.update(k, x, y);
        } else if (t == 2) {
            double ret = st.query1(x, y) / m;
            printf("%.4f\n", ret);
        } else if (t == 3) {
            double v1 = st.query1(x, y);
            double v2 = st.query2(x, y);
            double ret = (v2 - v1*v1/m)/m;
            printf("%.4f\n", ret);
        }
    }

    return 0;
}
