// https://www.luogu.org/problemnew/show/CF817F
// MEX Queries

#include <bits/stdc++.h>
using namespace std;

// note it's 1-indexed
class SegmentTree {
    int N;
    int *val0, *val1, *lazy, *inv;

public:
    SegmentTree(int N_): N(N_) {
        val0 = new int[4*N]{};
        val1 = new int[4*N]{};
        lazy = new int[4*N]{};
        memset(lazy, -1, 4*N*sizeof(int));
        inv = new int[4*N]{};
        build(1, 1, N);
    }

    ~SegmentTree() {
        delete[] val0;
        delete[] val1;
        delete[] lazy;
        delete[] inv;
    }
    // set t to range [a, b]
    void update(int t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    int query() {
        return val0[1];
    }

    void flip(int a, int b) {
        flip(1, 1, N, a, b);
    }

    int query(int i) {
        return query(1, 1, N, i);
    }

    int query(int k, int l, int r, int a) {
        pushDown(k, l, r);
        if (l == r) return (val0[k] == l ? 0 : 1);
        int mid = (l + r) / 2;
        if (a <= mid) return query(2*k, l, mid, a);
        else return query(2*k+1, mid+1, r, a);
    }

private:
    void build(int k, int l, int r) {
        if (l == r) {
            val0[k] = l;
            val1[k] = INT_MAX;
            return;
        }
        int mid = (l + r) / 2;
        build(2*k, l, mid);
        build(2*k+1, mid+1, r);
        val0[k] = min(val0[2*k], val0[2*k+1]);
        val1[k] = min(val1[2*k], val1[2*k+1]);
    }

    // set t to range [a, b], current node range is [l, r]
    void update(int k, int t, int l, int r, int a, int b) {
        assert(t != -1);
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            lazy[k] = t;
            inv[k] = 0;
            eval(k, l);
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        val0[k] = min(val0[2*k], val0[2*k+1]);
        val1[k] = min(val1[2*k], val1[2*k+1]);
    }

    void flip(int k, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            if (lazy[k] != -1) {
                lazy[k] = 1 - lazy[k];
                eval(k, l);
            } else {
                inv[k] = 1 ^ inv[k];
                swap(val0[k], val1[k]);
            }
            return;
        }

        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) flip(2*k, l, mid, a, b);
        if (mid < b)  flip(2*k+1, mid+1, r, a, b);
        val0[k] = min(val0[2*k], val0[2*k+1]);
        val1[k] = min(val1[2*k], val1[2*k+1]);
    }

    void eval(int k, int l) {
        assert(lazy[k] != -1);
        if (inv[k] == lazy[k]) {
            val0[k] = l;
            val1[k] = INT_MAX;
        } else {
            val0[k] = INT_MAX;
            val1[k] = l;
        }
    }

    void merge(int k, int j, int l) {
        if (inv[k] == 0) {
            if (lazy[k] == -1) return;
            else {
                inv[j] = 0;
                lazy[j] = lazy[k];
                eval(j, l);
            }
        } else {
            if (lazy[k] == -1) {
                if (inv[j] == 0) {
                    if (lazy[j] == -1) {
                        inv[j] = 1;
                        swap(val0[j], val1[j]);
                    } else {
                        inv[j] = 0;
                        lazy[j] = 1 - lazy[j];
                        eval(j, l);
                    }
                } else {
                    if (lazy[j] == -1) {
                        inv[j] = 0;
                        swap(val0[j], val1[j]);
                    } else {
                        inv[j] = 0;
                        eval(j, l);
                    }
                }
            } else {
                assert(0);
            }
        }
    }

    void pushDown(int k, int l, int r) {
        if (l == r) return;
        int mid = (l + r) / 2;
        merge(k, 2*k, l);
        merge(k, 2*k+1, mid+1);
        inv[k] = 0;
        lazy[k] = -1;
    }
};

const int MAXN = 1e5+10;
int N;

struct Query {
    int t;
    int64_t l, r;
} Q[MAXN];

int64_t X[MAXN*4];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int t;
        int64_t l, r;
        cin >> t >> l >> r;
        Q[i] = {t, l, r};
        X[4*i] = l;
        X[4*i+1] = r;
        X[4*i+2] = l+1;
        X[4*i+3] = r+1;
    }
    X[4*N] = 1;
    sort(X, X+4*N+1);
    auto endp = unique(X, X+4*N+1);
    const int m = endp - X;
    SegmentTree st(m);

    for (int i = 0; i < N; i++) {
        int l = lower_bound(X, endp, Q[i].l) - X + 1;
        int r = lower_bound(X, endp, Q[i].r) - X + 1;
        int t = Q[i].t;
        if (t < 3) {
            st.update(2-t, l, r);
        } else {
            st.flip(l, r);
        }
        int x = st.query();
        cout << X[x-1] << endl;
    }
    return 0;
}
